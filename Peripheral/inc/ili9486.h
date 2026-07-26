#ifndef ILI9486_H
#define ILI9486_H

/*
 * ILI9486 8-bit 8080 parallel LCD driver
 * Version: 1.1
 * Date:    2026-07-27
 * Changelog:
 *   1.0 (2026-07-25) - Initial driver (as ILI9488), fix BSRR pin-bitmask bug, MADCTL mirror fix
 *   1.1 (2026-07-27) - Rename ILI9488 -> ILI9486 (correct chip), remove backlight (no BL on this board),
 *                       add ILI9486_Ops_t setup-level function-pointer layer (pin_set/pin_clear/delay_ms)
 */

#include <stdint.h>
#include "stm32f4xx_common.h"
#include "gpio_driver.h"
#include "fonts.h"

/*
 * Example pin mapping cho shield 3.5" ILI9486 8-bit parallel (tuỳ chỉnh theo thực tế):
 *
 *   PB0 → LCD_RS  (D/CX)
 *   PB1 → LCD_RST (RESX)
 *   PB2 → LCD_CS  (CSX)
 *   PB3 → LCD_WR  (WRX)
 *   PB4 → LCD_RD  (RDX)
 *   PD0-PD7 → DB0-DB7 (data bus 8-bit)
 *   PD13 → F_CS (Flash ngoài, không thuộc LCD)
 *
 * Cấu hình trong main.c:
 *   lcd.data_port = GPIOD;  lcd.data_pin_offset = 0;
 *   lcd.cs_port   = GPIOB;  lcd.cs_pin   = GPIO_PIN_NO_2;
 *   lcd.dc_port   = GPIOB;  lcd.dc_pin   = GPIO_PIN_NO_0;
 *   lcd.wr_port   = GPIOB;  lcd.wr_pin   = GPIO_PIN_NO_3;
 *   lcd.rd_port   = GPIOB;  lcd.rd_pin   = GPIO_PIN_NO_4;
 *   lcd.rst_port  = GPIOB;  lcd.rst_pin  = GPIO_PIN_NO_1;
 *   ILI9486_Init();
 */

/*
 * Setup-level ops — pin_set/pin_clear/delay_ms dùng cho các hàm gọi ít
 * (Reset, WriteCmd, WriteData, StartData, EndData). KHÔNG dùng cho hot path
 * ghi pixel (WR_STRB/SET_DATA vẫn giữ macro/inline trực tiếp BSRR để giữ tốc độ
 * FillScreen). Mặc định gán trong ILI9486_Init(); gọi ILI9486_SetOps() trước
 * Init() nếu muốn thay bằng driver GPIO khác hoặc mock cho test.
 */
typedef struct {
    void (*pin_set)(GPIO_TypeDef *port, uint16_t pin);    /* Set pin HIGH */
    void (*pin_clear)(GPIO_TypeDef *port, uint16_t pin);  /* Set pin LOW */
    void (*delay_ms)(uint32_t ms);
} ILI9486_Ops_t;

typedef struct {
    /*
     * Data bus GPIO port. DB[7:0] are placed at bits [data_pin_offset+7 : data_pin_offset]
     * on data_port->ODR. For speed, all 8 data pins must be on the same port and contiguous.
     * Examples:  data_pin_offset = 0 → pins 0-7   (bits [7:0])
     *            data_pin_offset = 8 → pins 8-15  (bits [15:8])
     */
    GPIO_TypeDef *data_port;
    uint8_t       data_pin_offset;  /* 0 or 8 typically */

    /* Control signals */
    GPIO_TypeDef *cs_port;      /* Chip select, active low */
    uint16_t      cs_pin;
    GPIO_TypeDef *dc_port;      /* Data/Command select (D/CX) */
    uint16_t      dc_pin;
    GPIO_TypeDef *wr_port;      /* Write strobe, active low (WRX) */
    uint16_t      wr_pin;
    GPIO_TypeDef *rd_port;      /* Read strobe, active low (RDX) */
    uint16_t      rd_pin;
    GPIO_TypeDef *rst_port;     /* Hardware reset, active low */
    uint16_t      rst_pin;

    ILI9486_Ops_t ops;          /* Setup-level pin/delay ops (see ILI9486_Ops_t) */

    uint16_t width;             /* Current logical width in pixels */
    uint16_t height;            /* Current logical height in pixels */
} ILI9486_t;

/* Global LCD handle – user sets fields before calling ILI9486_Init() */
extern ILI9486_t lcd;

/* ======================== ILI9486 Command Codes (datasheet §8.1) ======================== */
/* System commands */
#define ILI9486_CMD_NOP                  0x00
#define ILI9486_CMD_SWRESET              0x01
#define ILI9486_CMD_READ_DISP_INFO       0x0D
#define ILI9486_CMD_READ_DISP_STATUS     0x09

/* Sleep / Display */
#define ILI9486_CMD_SLEEP_IN             0x10
#define ILI9486_CMD_SLEEP_OUT            0x11
#define ILI9486_CMD_PARTIAL_ON           0x12
#define ILI9486_CMD_NORMAL_DISPLAY_ON    0x13
#define ILI9486_CMD_INV_OFF              0x20
#define ILI9486_CMD_INV_ON               0x21
#define ILI9486_CMD_DISPLAY_OFF          0x28
#define ILI9486_CMD_DISPLAY_ON           0x29

/* Memory / Addressing */
#define ILI9486_CMD_CASET                0x2A
#define ILI9486_CMD_PASET                0x2B
#define ILI9486_CMD_RAMWR                0x2C
#define ILI9486_CMD_RAMRD                0x2E
#define ILI9486_CMD_MADCTL               0x36
#define ILI9486_CMD_PIXFMT               0x3A

/* Tearing / Scrolling */
#define ILI9486_CMD_TE_OFF               0x34
#define ILI9486_CMD_TE_ON                0x35
#define ILI9486_CMD_VSCRSADD             0x37
#define ILI9486_CMD_IDLE_OFF             0x38
#define ILI9486_CMD_IDLE_ON              0x39
#define ILI9486_CMD_VSCRDEF              0x33

/* Backlight / CABC */
#define ILI9486_CMD_WRITE_BRIGHTNESS     0x51
#define ILI9486_CMD_READ_BRIGHTNESS      0x52
#define ILI9486_CMD_WRITE_CTRL_DISPLAY   0x53
#define ILI9486_CMD_READ_CTRL_DISPLAY    0x54
#define ILI9486_CMD_WRITE_CABC           0x55

/* Extended registers */
#define ILI9486_CMD_IF_MODE              0xB0
#define ILI9486_CMD_FRAME_RATE_NORMAL    0xB1
#define ILI9486_CMD_FRAME_RATE_IDLE      0xB2
#define ILI9486_CMD_FRAME_RATE_PARTIAL   0xB3
#define ILI9486_CMD_DISPLAY_INV_CTRL     0xB4
#define ILI9486_CMD_BLANKING_PORCH       0xB5
#define ILI9486_CMD_DISPLAY_FUNC         0xB6
#define ILI9486_CMD_ENTRY_MODE           0xB7

/* Power control */
#define ILI9486_CMD_POWER_CTRL_1         0xC0
#define ILI9486_CMD_POWER_CTRL_2         0xC1
#define ILI9486_CMD_POWER_CTRL_3         0xC2
#define ILI9486_CMD_POWER_CTRL_4         0xC3
#define ILI9486_CMD_POWER_CTRL_5         0xC4
#define ILI9486_CMD_VCOM_CTRL_1          0xC5

/* Gamma */
#define ILI9486_CMD_PGAMCTRL             0xE0  /* Positive gamma */
#define ILI9486_CMD_NGAMCTRL             0xE1  /* Negative gamma */

/* ID read */
#define ILI9486_CMD_READ_ID4             0xD3

/* ======================== Pixel Format (3Ah) — chọn 1 trong 2 ======================== */
/*
 * 3Ah data byte: 0 DPI[6:4] 0 DBI[2:0]
 *
 * ILI9486_PIXFMT_RGB565 (0x55) — DPI=101, DBI=101
 *   16-bit/pixel, 2 byte/pixel, uint16_t color.
 *   Hi-byte: R[4:0] | G[5:3]     (VD: 0xF8 = RED)
 *   Lo-byte: G[2:0] | B[4:0]     (VD: 0x00 = RED)
 *   65K màu, nhanh hơn, đang dùng trong driver hiện tại.
 *
 * ILI9486_PIXFMT_RGB666 (0x66) — DPI=110, DBI=110
 *   18-bit/pixel, 3 byte/pixel, cần uint32_t color (18 LSB).
 *   Byte 1: R[5:0] | G[5:4]
 *   Byte 2: G[3:0] | B[5:2]
 *   Byte 3: B[1:0] | 0
 *   262K màu, chậm hơn 50% băng thông.
 *
 * Không set 3Ah → dùng giá trị mặc định của module (thường là RGB565).
 */
#define ILI9486_PIXFMT_RGB565  0x55
#define ILI9486_PIXFMT_RGB666  0x66

/*
 * Chọn pixel format tại đây — ảnh hưởng đến dung lượng màu và số byte/pixel.
 */
#ifndef ILI9486_PIXFMT
#define ILI9486_PIXFMT  ILI9486_PIXFMT_RGB666
#endif

/* ======================== Color type & constants ======================== */
#if ILI9486_PIXFMT == ILI9486_PIXFMT_RGB666
/*
 * RGB666: 18-bit/pixel, uint32_t 0x00RRGGBB (8-bit/channel, ILI9486 lấy 6 MSB).
 *   VD: RED = 0xFF0000, GREEN = 0x00FF00
 *   3 byte/pixel trên bus, 262K màu.
 */
typedef uint32_t ILI9486_Color_t;

#define ILI9486_BLACK       0x000000
#define ILI9486_BLUE        0x0000FF
#define ILI9486_RED         0xFF0000
#define ILI9486_GREEN       0x00FF00
#define ILI9486_CYAN        0x00FFFF
#define ILI9486_MAGENTA     0xFF00FF
#define ILI9486_YELLOW      0xFFFF00
#define ILI9486_WHITE       0xFFFFFF
#define ILI9486_ORANGE      0xFFA500
#define ILI9486_LIGHTGREY   0xD3D3D3
#define ILI9486_DARKGREEN   0x006400
#define ILI9486_DARKCYAN    0x008B8B
#define ILI9486_DARKGREY    0x444444

/* Tạo ILI9486_Color_t từ 3 kênh 8-bit R, G, B */
#define ILI9486_COLOR(r, g, b)  (((uint32_t)(r) << 16) | ((uint32_t)(g) << 8) | (uint32_t)(b))

/* Chuyển RGB565 value → RGB666 gần đúng (mất thông tin, 5-bit→8-bit) */
#define ILI9486_FROM_RGB565(c)  ILI9486_COLOR(                          \
    ((((c) >> 11) & 0x1F) * 255 + 15) / 31,  /* R 5-bit → 8-bit */     \
    ((((c) >> 5)  & 0x3F) * 255 + 31) / 63,  /* G 6-bit → 8-bit */     \
    (((c) & 0x1F)         * 255 + 15) / 31)  /* B 5-bit → 8-bit */     \

#else
/*
 * RGB565: 16-bit/pixel, uint16_t.
 *   Hi-byte: R[4:0] | G[5:3]
 *   Lo-byte: G[2:0] | B[4:0]
 *   2 byte/pixel trên bus, 65K màu.
 */
typedef uint16_t ILI9486_Color_t;

#define ILI9486_BLACK       0x0000
#define ILI9486_BLUE        0x001F
#define ILI9486_RED         0xF800
#define ILI9486_GREEN       0x07E0
#define ILI9486_CYAN        0x07FF
#define ILI9486_MAGENTA     0xF81F
#define ILI9486_YELLOW      0xFFE0
#define ILI9486_WHITE       0xFFFF
#define ILI9486_ORANGE      0xFD20
#define ILI9486_LIGHTGREY   0xD69A
#define ILI9486_DARKGREEN   0x03E0
#define ILI9486_DARKCYAN    0x0451
#define ILI9486_DARKGREY    0x7BEF

#define ILI9486_COLOR(r, g, b)  ((uint16_t)(((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | ((b) >> 3))
#define ILI9486_FROM_RGB565(c)  (c)

#endif

/*
 * Số byte/pixel trên bus 8-bit — dùng để tính kích thước bộ đệm.
 * RGB565 = 2, RGB666 = 3.
 */
#if ILI9486_PIXFMT == ILI9486_PIXFMT_RGB666
#define ILI9486_BYTES_PER_PIXEL  3
#else
#define ILI9486_BYTES_PER_PIXEL  2
#endif

/* ======================== MADCTL (36h) bits ======================== */
#define ILI9486_MADCTL_MY   0x80  /* Page address order */
#define ILI9486_MADCTL_MX   0x40  /* Column address order */
#define ILI9486_MADCTL_MV   0x20  /* Page/Column exchange */
#define ILI9486_MADCTL_ML   0x10  /* Vertical refresh order (LCD) */
#define ILI9486_MADCTL_BGR  0x08  /* RGB/BGR order */
#define ILI9486_MADCTL_MH   0x04  /* Horizontal refresh order (LCD) */

/* ======================== Function prototypes ======================== */
void ILI9486_SetOps(const ILI9486_Ops_t *ops);
void ILI9486_Reset(void);
void ILI9486_Init(void);
void ILI9486_SetRotation(uint8_t rotation);

void ILI9486_EnterSleep(void);
void ILI9486_ExitSleep(void);

void ILI9486_FillScreen(ILI9486_Color_t color);
void ILI9486_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, ILI9486_Color_t color);
void ILI9486_DrawPixel(uint16_t x, uint16_t y, ILI9486_Color_t color);
void ILI9486_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, ILI9486_Color_t color);

void ILI9486_DrawChar(uint16_t x, uint16_t y, char c, FontDef *font, ILI9486_Color_t color, ILI9486_Color_t bg);
void ILI9486_DrawString(uint16_t x, uint16_t y, char *str, FontDef *font, ILI9486_Color_t color, ILI9486_Color_t bg);
void ILI9486_DrawStringFast(uint16_t x, uint16_t y, char *str, FontDef *font, ILI9486_Color_t color, ILI9486_Color_t bg);

#endif /* ILI9486_H */
