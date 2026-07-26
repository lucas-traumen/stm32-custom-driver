/*
 * ILI9486 8-bit 8080 parallel LCD driver
 * Version: 1.1
 * Date:    2026-07-27
 * Changelog:
 *   1.0 (2026-07-25) - Initial driver (as ILI9488), fix BSRR pin-bitmask bug, MADCTL mirror fix
 *   1.1 (2026-07-27) - Rename ILI9488 -> ILI9486 (correct chip), remove backlight (no BL on this board),
 *                       add ILI9486_Ops_t setup-level function-pointer layer (pin_set/pin_clear/delay_ms)
 */
#include "ili9486.h"
#include <string.h>
#include <stdlib.h>

/* ===================== Forward declarations ===================== */
extern void delay_ms(uint32_t ms);  /* Provided by the application (SysTick) */

/* ===================== Physical constants ===================== */
#define ILI9486_PHYS_WIDTH     320
#define ILI9486_PHYS_HEIGHT    480

/* ===================== Global handle ===================== */
ILI9486_t lcd;

/* ===================== Low-level 8080 parallel interface ===================== */

/*
 * 8-bit 8080 write cycle (datasheet §7.1.2.1, page 28):
 *   CSX  = active low
 *   D/CX = 0 (command) or 1 (data)
 *   DB[7:0] = data byte
 *   WRX  = active-low strobe (data latched on rising edge)
 *
 * Timing (page 298):
 *   tWRL ≥ 15ns  (WR low pulse)
 *   tWRH ≥ 15ns  (WR high pulse)
 *   tWC  ≥ 66ns  (WR cycle time)
 *   tDST ≥ 10ns  (data setup before WR rising)
 *   tDHT ≥ 10ns  (data hold after WR rising)
 *
 * On STM32F4 @168 MHz, one GPIO write ≈ 2–3 HCLK ≈ 12–18ns.
 * __NOP() adds ~6ns each to keep worst-case >15ns.
 */
#define ILI9486_WR_STRB()  do {                                    \
    lcd.wr_port->BSRR = (uint32_t)(1u << lcd.wr_pin) << 16u;      \
    __NOP(); __NOP();                                              \
    lcd.wr_port->BSRR = (uint32_t)(1u << lcd.wr_pin);              \
    __NOP();                                                       \
} while (0)

#define ILI9486_SET_DATA(d)  do {                                                             \
    uint32_t _s = lcd.data_pin_offset;                                                        \
    lcd.data_port->ODR = (lcd.data_port->ODR & ~(0xFFu << _s)) | ((uint32_t)(d) << _s);        \
} while (0)

/*
 * Write one command byte (D/CX = 0), CS toggled.
 * CS/D-C toggling goes through lcd.ops (setup-level, called once per command) —
 * only the WR strobe/data-bus write stay as direct-BSRR macros for pixel throughput.
 */
static inline void ILI9486_WriteCmd(uint8_t cmd)
{
    lcd.ops.pin_clear(lcd.cs_port, lcd.cs_pin);   /* CS low */
    lcd.ops.pin_clear(lcd.dc_port, lcd.dc_pin);   /* D/C low = command */
    ILI9486_SET_DATA(cmd);                                       /* data valid */
    ILI9486_WR_STRB();                                           /* WR strobe (latch on rising edge) */
    lcd.ops.pin_set(lcd.cs_port, lcd.cs_pin);     /* CS high */
}

/* Write one data byte (D/CX = 1), CS toggled */
static inline void ILI9486_WriteData(uint8_t data)
{
    lcd.ops.pin_clear(lcd.cs_port, lcd.cs_pin);   /* CS low */
    lcd.ops.pin_set(lcd.dc_port, lcd.dc_pin);     /* D/C high = data */
    ILI9486_SET_DATA(data);                                       /* data valid */
    ILI9486_WR_STRB();                                            /* WR strobe */
    lcd.ops.pin_set(lcd.cs_port, lcd.cs_pin);     /* CS high */
}

/*
 * Stream multiple data bytes while holding CS and D/C active.
 * Used for pixel data bursts after SetAddressWindow.
 */
static inline void ILI9486_StartData(void)
{
    lcd.ops.pin_clear(lcd.cs_port, lcd.cs_pin);  /* CS low */
    lcd.ops.pin_set(lcd.dc_port, lcd.dc_pin);    /* D/C high = data */
}

static inline void ILI9486_WriteDataByte(uint8_t data)
{
    ILI9486_SET_DATA(data);
    ILI9486_WR_STRB();
}

static inline void ILI9486_EndData(void)
{
    lcd.ops.pin_set(lcd.cs_port, lcd.cs_pin);    /* CS high */
}

/*
 * Write one pixel color to the data bus (already in StartData/EndData burst).
 * Switches between RGB565 (2 bytes) and RGB666 (3 bytes) at compile time.
 */
static inline void ILI9486_WritePixelColor(ILI9486_Color_t color)
{
#if ILI9486_PIXFMT == ILI9486_PIXFMT_RGB666
    /* 18-bit pixel: 3 writes, upper 2 bits per byte ignored by ILI9486 */
    ILI9486_WriteDataByte((uint8_t)(color >> 16));   /* R (MSB) */
    ILI9486_WriteDataByte((uint8_t)(color >> 8));    /* G */
    ILI9486_WriteDataByte((uint8_t)(color));          /* B (LSB) */
#else
    /* 16-bit pixel: 2 writes, RGB565 */
    ILI9486_WriteDataByte((uint8_t)(color >> 8));    /* Hi: R[4:0] | G[5:3] */
    ILI9486_WriteDataByte((uint8_t)(color & 0xFF));  /* Lo: G[2:0] | B[4:0] */
#endif
}

/*
 * Encode one pixel color into raw byte representation.
 * Use for pre-filling a buffer before a DMA or manual burst write.
 */
static inline void ILI9486_ColorToBytes(ILI9486_Color_t color, uint8_t *buf)
{
#if ILI9486_PIXFMT == ILI9486_PIXFMT_RGB666
    buf[0] = (uint8_t)(color >> 16);
    buf[1] = (uint8_t)(color >> 8);
    buf[2] = (uint8_t)(color);
#else
    buf[0] = (uint8_t)(color >> 8);
    buf[1] = (uint8_t)(color & 0xFF);
#endif
}

/*
 * Write (cmd, data...) pair — CS held low for data burst.
 *  - cmd: 1-byte command
 *  - data: pointer to data bytes
 *  - len:  number of data bytes
 */
static void ILI9486_WriteCmdData(uint8_t cmd, const uint8_t *data, uint16_t len)
{
    ILI9486_WriteCmd(cmd);
    ILI9486_StartData();
    for (uint16_t i = 0; i < len; i++) {
        ILI9486_WriteDataByte(data[i]);
    }
    ILI9486_EndData();
}

/* Write a 16-bit value as two bytes (big-endian), CS held low */
static inline void ILI9486_WriteData16(uint16_t val)
{
    ILI9486_StartData();
    ILI9486_WriteDataByte((uint8_t)(val >> 8));
    ILI9486_WriteDataByte((uint8_t)(val & 0xFF));
    ILI9486_EndData();
}

/* ===================== Address window ===================== */

/*
 * Set column and page address window (CASET 2Ah, PASET 2Bh).
 * All subsequent Memory Write (2Ch) fills this region.
 */
static void ILI9486_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    ILI9486_WriteCmd(ILI9486_CMD_CASET);
    ILI9486_WriteData16(x0);
    ILI9486_WriteData16(x1);

    ILI9486_WriteCmd(ILI9486_CMD_PASET);
    ILI9486_WriteData16(y0);
    ILI9486_WriteData16(y1);

    ILI9486_WriteCmd(ILI9486_CMD_RAMWR);
}

/* ===================== Setup-level ops (see ILI9486_Ops_t) ===================== */

static void ILI9486_DefaultPinSet(GPIO_TypeDef *port, uint16_t pin)
{
    port->BSRR = (uint32_t)(1u << pin);
}

static void ILI9486_DefaultPinClear(GPIO_TypeDef *port, uint16_t pin)
{
    port->BSRR = (uint32_t)(1u << pin) << 16u;
}

static const ILI9486_Ops_t ILI9486_DefaultOps = {
    .pin_set   = ILI9486_DefaultPinSet,
    .pin_clear = ILI9486_DefaultPinClear,
    .delay_ms  = delay_ms,
};

/*
 * Override setup-level ops (pin_set/pin_clear/delay_ms) before ILI9486_Init().
 * Leaves the WR_STRB/SET_DATA pixel hot path untouched — those always hit
 * lcd.wr_port/data_port directly regardless of ops.
 */
void ILI9486_SetOps(const ILI9486_Ops_t *ops)
{
    lcd.ops = *ops;
}

/* ===================== Initialization ===================== */

/*
 * WTK ILI9486 module init sequence (VCI = 2.8V).
 *
 * Reset timing: RST high ≥1ms → low ≥10ms → high ≥120ms.
 * 8080 interface timing per datasheet pages 212-213:
 *   tWL ≥ 15ns, tWH ≥ 15ns — met by GPIO write speed.
 */
void ILI9486_Reset(void)
{
    lcd.ops.pin_set(lcd.rst_port, lcd.rst_pin);     /* RST high */
    lcd.ops.delay_ms(1);
    lcd.ops.pin_clear(lcd.rst_port, lcd.rst_pin);   /* RST low  */
    lcd.ops.delay_ms(10);
    lcd.ops.pin_set(lcd.rst_port, lcd.rst_pin);     /* RST high */
    lcd.ops.delay_ms(120);
}

void ILI9486_Init(void)
{
    if (lcd.ops.pin_set == NULL) {
        lcd.ops = ILI9486_DefaultOps;
    }

    ILI9486_Reset();

    /* ---- WTK register access / undocumented init ---- */
    ILI9486_WriteCmdData(0xF2, (uint8_t[]){0x18, 0xA3, 0x12, 0x02, 0xB2, 0x12, 0xFF, 0x10, 0x00}, 9);
    ILI9486_WriteCmdData(0xF8, (uint8_t[]){0x21, 0x04}, 2);
    ILI9486_WriteCmdData(0xF9, (uint8_t[]){0x00, 0x08}, 2);

    /* ---- Display Inversion ON (21h) ---- */
    ILI9486_WriteCmd(ILI9486_CMD_INV_ON);

    /* ---- Memory Access Control (36h) ---- */
    ILI9486_WriteCmdData(ILI9486_CMD_MADCTL, (uint8_t[]){0x08}, 1);  /* BGR */

    /* ---- Display Inversion Control (B4h) ---- */
    ILI9486_WriteCmdData(ILI9486_CMD_DISPLAY_INV_CTRL, (uint8_t[]){0x00}, 1);

    /* ---- Display Function Control (B6h) ---- */
    ILI9486_WriteCmdData(ILI9486_CMD_DISPLAY_FUNC, (uint8_t[]){0x02, 0x22}, 2);

    /* ---- Power Control 2 (C1h) ---- */
    ILI9486_WriteCmdData(ILI9486_CMD_POWER_CTRL_2, (uint8_t[]){0x41}, 1);

    /* ---- VCOM Control 1 (C5h) ---- */
    ILI9486_WriteCmdData(ILI9486_CMD_VCOM_CTRL_1, (uint8_t[]){0x00, 0x53}, 2);

    /* ---- Positive Gamma (E0h) ---- */
    ILI9486_WriteCmdData(ILI9486_CMD_PGAMCTRL,
        (uint8_t[]){0x0F, 0x10, 0x08, 0x05, 0x09, 0x05, 0x37, 0x98,
                    0x26, 0x07, 0x0F, 0x02, 0x09, 0x07, 0x00}, 15);

    /* ---- Negative Gamma (E1h) ---- */
    ILI9486_WriteCmdData(ILI9486_CMD_NGAMCTRL,
        (uint8_t[]){0x0F, 0x38, 0x36, 0x0D, 0x10, 0x08, 0x59, 0x76,
                    0x48, 0x0A, 0x16, 0x0A, 0x37, 0x2F, 0x00}, 15);

    /* ---- Interface Pixel Format (3Ah) — đồng bộ với ILI9486_PIXFMT ---- */
    {
        uint8_t pf = ILI9486_PIXFMT;
        ILI9486_WriteCmdData(ILI9486_CMD_PIXFMT, &pf, 1);
    }

    /* ---- Sleep Out (11h) + wait ---- */
    ILI9486_WriteCmd(ILI9486_CMD_SLEEP_OUT);
    delay_ms(120);

    /* ---- Display ON (29h) ---- */
    ILI9486_WriteCmd(ILI9486_CMD_DISPLAY_ON);

    /* Set logical size */
    lcd.width  = ILI9486_PHYS_WIDTH;
    lcd.height = ILI9486_PHYS_HEIGHT;
}

/* ===================== Sleep control ===================== */
void ILI9486_EnterSleep(void)
{
    ILI9486_WriteCmd(ILI9486_CMD_DISPLAY_OFF);
    delay_ms(10);
    ILI9486_WriteCmd(ILI9486_CMD_SLEEP_IN);
    delay_ms(120);
}

void ILI9486_ExitSleep(void)
{
    ILI9486_WriteCmd(ILI9486_CMD_SLEEP_OUT);
    delay_ms(120);
    ILI9486_WriteCmd(ILI9486_CMD_DISPLAY_ON);
}

/* ===================== Rotation (§7.1  Memory Access Control 36h) ===================== */
void ILI9486_SetRotation(uint8_t rotation)
{
    uint8_t madctl = 0;

    switch (rotation) {
    case 0: /* Portrait */
        madctl = 0x00 | ILI9486_MADCTL_BGR;
        lcd.width  = ILI9486_PHYS_WIDTH;
        lcd.height = ILI9486_PHYS_HEIGHT;
        break;
    case 1: /* Landscape (CW 90°) */
        madctl = ILI9486_MADCTL_MV | ILI9486_MADCTL_MX | ILI9486_MADCTL_BGR;
        lcd.width  = ILI9486_PHYS_HEIGHT;
        lcd.height = ILI9486_PHYS_WIDTH;
        break;
    case 2: /* Portrait inverted (180°) */
        madctl = ILI9486_MADCTL_MX | ILI9486_MADCTL_MY | ILI9486_MADCTL_BGR;
        lcd.width  = ILI9486_PHYS_WIDTH;
        lcd.height = ILI9486_PHYS_HEIGHT;
        break;
    case 3: /* Landscape inverted (CCW 90°) */
        madctl = ILI9486_MADCTL_MX | ILI9486_MADCTL_MV | ILI9486_MADCTL_MY | ILI9486_MADCTL_BGR;
        lcd.width  = ILI9486_PHYS_HEIGHT;
        lcd.height = ILI9486_PHYS_WIDTH;
        break;
    default:
        return;
    }

    ILI9486_WriteCmdData(ILI9486_CMD_MADCTL, &madctl, 1);
}

/* ===================== Drawing primitives ===================== */

void ILI9486_DrawPixel(uint16_t x, uint16_t y, ILI9486_Color_t color)
{
    if (x >= lcd.width || y >= lcd.height) return;

    ILI9486_SetAddressWindow(x, y, x, y);
    ILI9486_StartData();
    ILI9486_WritePixelColor(color);
    ILI9486_EndData();
}

/*
 * Fill a rectangular region.
 * Streams pixel data in one burst for maximum throughput.
 */
void ILI9486_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, ILI9486_Color_t color)
{
    if (x >= lcd.width || y >= lcd.height) return;
    if (x + w > lcd.width)  w = lcd.width  - x;
    if (y + h > lcd.height) h = lcd.height - y;

    ILI9486_SetAddressWindow(x, y, x + w - 1, y + h - 1);

    uint32_t total = (uint32_t)w * h;

    ILI9486_StartData();
    for (uint32_t i = 0; i < total; i++) {
        ILI9486_WritePixelColor(color);
    }
    ILI9486_EndData();
}

void ILI9486_FillScreen(ILI9486_Color_t color)
{
    ILI9486_FillRectangle(0, 0, lcd.width, lcd.height, color);
}

/* ===================== Line (Bresenham) ===================== */
void ILI9486_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, ILI9486_Color_t color)
{
    int16_t dx = abs((int16_t)(x1 - x0)), sx = x0 < x1 ? 1 : -1;
    int16_t dy = -abs((int16_t)(y1 - y0)), sy = y0 < y1 ? 1 : -1;
    int16_t err = dx + dy, e2;

    for (;;) {
        ILI9486_DrawPixel((uint16_t)x0, (uint16_t)y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 = (uint16_t)((int16_t)x0 + sx); }
        if (e2 <= dx) { err += dx; y0 = (uint16_t)((int16_t)y0 + sy); }
    }
}

/* ===================== Text ===================== */

void ILI9486_DrawChar(uint16_t x, uint16_t y, char ch, FontDef *font,
                      ILI9486_Color_t color, ILI9486_Color_t bg)
{
    if (ch < 32 || ch > 126) ch = '?';

    uint16_t fw = font->width;
    uint16_t fh = font->height;

    for (uint16_t row = 0; row < fh; row++) {
        uint16_t line = font->data[(ch - 32) * fh + row];
        uint16_t bits = (uint16_t)(line >> (16 - fw));

        for (uint16_t col = 0; col < fw; col++) {
            uint16_t mask = 1u << (fw - 1 - col);
            ILI9486_Color_t pixel = (bits & mask) ? color : bg;
            ILI9486_DrawPixel(x + col, y + row, pixel);
        }
    }
}

void ILI9486_DrawString(uint16_t x, uint16_t y, char *str, FontDef *font,
                        ILI9486_Color_t color, ILI9486_Color_t bg)
{
    uint16_t cursor_x = x;

    while (*str) {
        if (*str >= 32 && *str <= 126) {
            if (cursor_x + font->width > lcd.width) break;
            ILI9486_DrawChar(cursor_x, y, *str, font, color, bg);
            cursor_x += font->width;
        }
        str++;
    }
}

/* ===================== Optimised string (single burst) ===================== */

void ILI9486_DrawStringFast(uint16_t x, uint16_t y, char *str, FontDef *font,
                            ILI9486_Color_t color, ILI9486_Color_t bg)
{
    /* Count valid characters */
    uint16_t len = 0;
    char *tmp = str;
    while (*tmp && *tmp >= 32 && *tmp <= 126) { len++; tmp++; }
    if (len == 0) return;

    uint16_t fw = font->width;
    uint16_t fh = font->height;
    uint16_t tw = len * fw;

    /* Clamp */
    if (x + tw > lcd.width)  { len = (lcd.width - x) / fw; tw = len * fw; }
    if (y + fh > lcd.height) return;

    /* Chunking limit – keep stack usage low */
#define FAST_CHUNK_MAX 20
#define MAX_PIXELS     (FAST_CHUNK_MAX * 20)  /* max_chars * max_font_height */
    if (len > FAST_CHUNK_MAX) {
        while (len > 0) {
            uint16_t chunk = len > FAST_CHUNK_MAX ? FAST_CHUNK_MAX : len;
            char buf[FAST_CHUNK_MAX + 1];
            strncpy(buf, str, chunk);
            buf[chunk] = '\0';
            ILI9486_DrawStringFast(x, y, buf, font, color, bg);
            x += chunk * fw;
            str += chunk;
            len -= chunk;
        }
        return;
    }

    /* Build pixel buffer in BSS — size scales with pixel format */
    static uint8_t pixel_buf[MAX_PIXELS * ILI9486_BYTES_PER_PIXEL];
    uint32_t idx = 0;

    for (uint16_t row = 0; row < fh; row++) {
        tmp = str;
        for (uint16_t ci = 0; ci < len; ci++) {
            char c = *tmp++;
            uint16_t line = font->data[(c - 32) * fh + row];
            uint16_t bits = (uint16_t)(line >> (16 - fw));

            for (uint16_t col = 0; col < fw; col++) {
                ILI9486_Color_t p = (bits & (1u << (fw - 1 - col))) ? color : bg;
#if ILI9486_PIXFMT == ILI9486_PIXFMT_RGB666
                pixel_buf[idx++] = (uint8_t)(p >> 16);
                pixel_buf[idx++] = (uint8_t)(p >> 8);
                pixel_buf[idx++] = (uint8_t)(p);
#else
                pixel_buf[idx++] = (uint8_t)(p >> 8);
                pixel_buf[idx++] = (uint8_t)(p & 0xFF);
#endif
            }
        }
    }

    ILI9486_SetAddressWindow(x, y, x + tw - 1, y + fh - 1);
    ILI9486_StartData();
    for (uint32_t i = 0; i < idx; i++) {
        ILI9486_WriteDataByte(pixel_buf[i]);
    }
    ILI9486_EndData();
}
