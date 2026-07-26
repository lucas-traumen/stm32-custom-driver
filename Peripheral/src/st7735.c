//#include "st7735.h"
//#include <string.h>
//#include <stdlib.h>
//#include <math.h>
////#include "timer_driver.h"
//#include "gpio_driver.h"
//
//// ==================== CONFIGURATION ====================
//#define ST7735_X_OFFSET  0
//#define ST7735_Y_OFFSET  0
//
//#define ST7735_PHYS_WIDTH   128
//#define ST7735_PHYS_HEIGHT  160
//
//#define SPI_BUFFER_SIZE     128   // Pixels per SPI transfer
//
//ST7735_Typedef tft;
//
//// ==================== LOW-LEVEL SPI ====================
//static inline void writeCMD(uint8_t cmd) {
//    GPIO_Write_Pin(tft.GPIO_portCs, tft.GPIO_Pin_Cs, GPIO_PIN_RESET);
//    GPIO_Write_Pin(tft.GPIO_portA0, tft.GPIO_Pin_A0, GPIO_PIN_RESET);
//    SPI_SendData(tft.hspi, &cmd, 1);
//    GPIO_Write_Pin(tft.GPIO_portCs, tft.GPIO_Pin_Cs, GPIO_PIN_SET);
//}
//
//static inline void writeData(uint8_t *data, uint16_t len) {
//    GPIO_Write_Pin(tft.GPIO_portCs, tft.GPIO_Pin_Cs, GPIO_PIN_RESET);
//    GPIO_Write_Pin(tft.GPIO_portA0, tft.GPIO_Pin_A0, GPIO_PIN_SET);
//    SPI_SendData(tft.hspi, data, len);
//    GPIO_Write_Pin(tft.GPIO_portCs, tft.GPIO_Pin_Cs, GPIO_PIN_SET);
//}
//
//static inline void setAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
//    x0 += ST7735_X_OFFSET;
//    x1 += ST7735_X_OFFSET;
//    y0 += ST7735_Y_OFFSET;
//    y1 += ST7735_Y_OFFSET;
//
//    writeCMD(0x2A);
//    uint8_t xdata[] = {x0 >> 8, x0 & 0xFF, x1 >> 8, x1 & 0xFF};
//    writeData(xdata, 4);
//
//    writeCMD(0x2B);
//    uint8_t ydata[] = {y0 >> 8, y0 & 0xFF, y1 >> 8, y1 & 0xFF};
//    writeData(ydata, 4);
//
//    writeCMD(0x2C);
//}
//
//// ==================== INITIALIZATION ====================
//void ST7735_Init(void) {
//    GPIO_Write_Pin(tft.GPIO_portRESET, tft.GPIO_Pin_Reset, GPIO_PIN_RESET);
//    delay_ms(20);
//    GPIO_Write_Pin(tft.GPIO_portRESET, tft.GPIO_Pin_Reset, GPIO_PIN_SET);
//    delay_ms(100);
//
//    writeCMD(0x01); delay_ms(150);
//    writeCMD(0x11); delay_ms(500);
//
//    writeCMD(0x3A);
//    uint8_t colorMode = 0x05;  // 16-bit RGB565
//    writeData(&colorMode, 1);
//
//    writeCMD(0x29);  // Display ON
//}
////void ST7735_Init(void) {
////    // 1. Hardware Reset
////    GPIO_Write_Pin(tft.GPIO_portRESET, tft.GPIO_Pin_Reset, GPIO_PIN_RESET);
////    delay_ms(20);
////    GPIO_Write_Pin(tft.GPIO_portRESET, tft.GPIO_Pin_Reset, GPIO_PIN_SET);
////    delay_ms(200);
////
////    // 2. Software Reset
////    writeCMD(0x01);
////    delay_ms(150);
////
////    // 3. MAGIC CODE (Khắc phục nhiễu)
////    writeCMD(0x11); // Sleep Out
////    delay_ms(255);
////
////    // Cài đặt tần số quét (Frame Rate)
////    writeCMD(0xB1);
////    uint8_t dataB1[] = {0x01, 0x2C, 0x2D};
////    writeData(dataB1, 3);
////
////    writeCMD(0xB2);
////    uint8_t dataB2[] = {0x01, 0x2C, 0x2D};
////    writeData(dataB2, 3);
////
////    writeCMD(0xB3);
////    uint8_t dataB3[] = {0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D};
////    writeData(dataB3, 6);
////
////    writeCMD(0xB4); // Column inversion
////    uint8_t dataB4[] = {0x07};
////    writeData(dataB4, 1);
////
////    // Cài đặt điện áp (Power Control) - QUAN TRỌNG ĐỂ HẾT NHIỄU
////    writeCMD(0xC0);
////    uint8_t dataC0[] = {0xA2, 0x02, 0x84};
////    writeData(dataC0, 3);
////
////    writeCMD(0xC1);
////    uint8_t dataC1[] = {0xC5};
////    writeData(dataC1, 1);
////
////    writeCMD(0xC2);
////    uint8_t dataC2[] = {0x0A, 0x00};
////    writeData(dataC2, 2);
////
////    writeCMD(0xC3);
////    uint8_t dataC3[] = {0x8A, 0x2A};
////    writeData(dataC3, 2);
////
////    writeCMD(0xC4);
////    uint8_t dataC4[] = {0x8A, 0xEE};
////    writeData(dataC4, 2);
////
////    writeCMD(0xC5); // VCOM
////    uint8_t dataC5[] = {0x0E};
////    writeData(dataC5, 1);
////
////    // Cài đặt Gamma (Màu sắc chuẩn)
////    writeCMD(0xE0);
////    uint8_t dataE0[] = {0x02, 0x1C, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2D, 0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10};
////    writeData(dataE0, 16);
////
////    writeCMD(0xE1);
////    uint8_t dataE1[] = {0x03, 0x1d, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2D, 0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10};
////    writeData(dataE1, 16);
////
////    // Định dạng màu 16-bit
////    writeCMD(0x3A);
////    uint8_t data3A[] = {0x05};
////    writeData(data3A, 1);
////
////    writeCMD(0x29); // Display ON
////    delay_ms(100);
////}
//
//void ST7735_Backlight_On(void) {
//    GPIO_Write_Pin(tft.GPIO_portBL, tft.GPIO_Pin_BL, GPIO_PIN_SET);
//}
//
//void ST7735_Backlight_Off(void) {
//    GPIO_Write_Pin(tft.GPIO_portBL, tft.GPIO_Pin_BL, GPIO_PIN_RESET);
//}
//
//// ==================== ROTATION (QUAN TRỌNG) ====================
//void ST7735_SetRotation(uint8_t m)
//{
//    uint8_t madctl = 0;
//
//    switch (m)
//    {
//        case 0:
//            madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MY | ST7735_MADCTL_RGB;
//            tft.width  = ST7735_PHYS_WIDTH;
//            tft.height = ST7735_PHYS_HEIGHT;
//            break;
//        case 1:
//            madctl = ST7735_MADCTL_MY | ST7735_MADCTL_MV | ST7735_MADCTL_RGB;
//            tft.width  = ST7735_PHYS_HEIGHT;
//            tft.height = ST7735_PHYS_WIDTH;
//            break;
//        case 2:
//            madctl = ST7735_MADCTL_RGB;   // 💥 gây đảo gương ở nhiều module
//            tft.width  = ST7735_PHYS_WIDTH;
//            tft.height = ST7735_PHYS_HEIGHT;
//            break;
//        case 3:
//            madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_RGB;
//            tft.width  = ST7735_PHYS_HEIGHT;
//            tft.height = ST7735_PHYS_WIDTH;
//            break;
//    }
//
//    writeCMD(0x36);
//    writeData(&madctl, 1);
//}
//
//
//// ==================== BASIC DRAWING ====================
//void ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
//    if(x >= tft.width || y >= tft.height) return;
//
//    setAddressWindow(x, y, x, y);
//    uint8_t data[] = {color >> 8, color & 0xFF};
//    writeData(data, 2);
//}
//
//void ST7735_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
//    if(x >= tft.width || y >= tft.height) return;
//    if(x + w > tft.width) w = tft.width - x;
//    if(y + h > tft.height) h = tft.height - y;
//
//    setAddressWindow(x, y, x + w - 1, y + h - 1);
//
//    uint32_t total_pixels = (uint32_t)w * h;
//    uint8_t buffer[SPI_BUFFER_SIZE * 2];
//
//    // Pre-fill buffer
//    for(uint16_t i = 0; i < SPI_BUFFER_SIZE; i++) {
//        buffer[i * 2] = color >> 8;
//        buffer[i * 2 + 1] = color & 0xFF;
//    }
//
//    GPIO_Write_Pin(tft.GPIO_portCs, tft.GPIO_Pin_Cs, GPIO_PIN_RESET);
//    GPIO_Write_Pin(tft.GPIO_portA0, tft.GPIO_Pin_A0, GPIO_PIN_SET);
//
//    while(total_pixels > 0) {
//        uint32_t chunk = (total_pixels > SPI_BUFFER_SIZE) ? SPI_BUFFER_SIZE : total_pixels;
//        SPI_SendData(tft.hspi, buffer, chunk * 2);
//        total_pixels -= chunk;
//    }
//
//    GPIO_Write_Pin(tft.GPIO_portCs, tft.GPIO_Pin_Cs, GPIO_PIN_SET);
//}
//
//void ST7735_FillScreen(uint16_t color) {
//    ST7735_FillRectangle(0, 0, tft.width, tft.height, color);
//}
//
//// ==================== LINE & CIRCLE ====================
//void ST7735_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {
//    int16_t dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
//    int16_t dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
//    int16_t err = dx + dy, e2;
//
//    while(1) {
//        ST7735_DrawPixel(x0, y0, color);
//        if(x0 == x1 && y0 == y1) break;
//        e2 = 2 * err;
//        if(e2 >= dy) { err += dy; x0 += sx; }
//        if(e2 <= dx) { err += dx; y0 += sy; }
//    }
//}
//
//void ST7735_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
//    int16_t f = 1 - r, ddF_x = 1, ddF_y = -2 * r, x = 0, y = r;
//
//    ST7735_DrawPixel(x0, y0 + r, color);
//    ST7735_DrawPixel(x0, y0 - r, color);
//    ST7735_DrawPixel(x0 + r, y0, color);
//    ST7735_DrawPixel(x0 - r, y0, color);
//
//    while(x < y) {
//        if(f >= 0) { y--; ddF_y += 2; f += ddF_y; }
//        x++; ddF_x += 2; f += ddF_x;
//
//        ST7735_DrawPixel(x0 + x, y0 + y, color);
//        ST7735_DrawPixel(x0 - x, y0 + y, color);
//        ST7735_DrawPixel(x0 + x, y0 - y, color);
//        ST7735_DrawPixel(x0 - x, y0 - y, color);
//        ST7735_DrawPixel(x0 + y, y0 + x, color);
//        ST7735_DrawPixel(x0 - y, y0 + x, color);
//        ST7735_DrawPixel(x0 + y, y0 - x, color);
//        ST7735_DrawPixel(x0 - y, y0 - x, color);
//    }
//}
//
//void ST7735_FillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
//    int16_t x = -r, y = 0, err = 2 - 2 * r;
//    do {
//        ST7735_DrawLine(x0 - x, y0 - y, x0 + x, y0 - y, color);
//        ST7735_DrawLine(x0 - x, y0 + y, x0 + x, y0 + y, color);
//        r = err;
//        if(r > y) err += ++y * 2 + 1;
//        if(r <= x || err > y) err += ++x * 2 + 1;
//    } while(x < 0);
//}
//
//// Thay thế toàn bộ hàm ST7735_DrawChar bằng hàm này
//void ST7735_DrawChar(uint16_t x, uint16_t y, char ch, FontDef *font, uint16_t color, uint16_t bg)
//{
//    if (ch < 32 || ch > 126) ch = '?';
//    uint16_t fw = font->width;
//    uint16_t fh = font->height;
//
//    for (uint16_t row = 0; row < fh; row++) {
//        uint16_t line = font->data[(ch - 32) * fh + row]; // 16-bit pattern for this row
//
//        // Dồn các bit có nghĩa xuống phía LSB: nếu font lưu left-aligned trong 16-bit
//        // dịch phải (16 - fw) vị trí để đưa fw bit về vị trí thấp
//        uint16_t bits = (uint16_t)(line >> (16 - fw));
//
//        for (uint16_t col = 0; col < fw; col++) {
//            // kiểm tra bit từ MSB của bits xuống LSB (col = 0 => leftmost)
//            uint16_t mask = 1u << (fw - 1 - col);
//            uint16_t pixel_color = (bits & mask) ? color : bg;
//            ST7735_DrawPixel(x + col, y + row, pixel_color);
//        }
//    }
//}
//
//
//
//
//void ST7735_DrawString(uint16_t x, uint16_t y, char *str, FontDef *font, uint16_t color, uint16_t bg) {
//    uint16_t cursor_x = x;
//
//    while(*str) {
//        if(*str >= 32 && *str <= 126) {
//            if(cursor_x + font->width > tft.width) break;
//            ST7735_DrawChar(cursor_x, y, *str, font, color, bg);
//            cursor_x += font->width;
//        }
//        str++;
//    }
//}
//
//// ==================== OPTIMIZED STRING ====================
//// Thay thế toàn bộ hàm ST7735_DrawStringFast bằng hàm này
//void ST7735_DrawStringFast(uint16_t x, uint16_t y, char *str, FontDef *font, uint16_t color, uint16_t bg) {
//    // Đếm số ký tự hợp lệ
//    uint16_t len = 0;
//    char *temp = str;
//    while(*temp && *temp >= 32 && *temp <= 126) { len++; temp++; }
//
//    if(len == 0) return;
//
//    uint16_t fw = font->width;
//    uint16_t fh = font->height;
//
//    uint16_t total_width = len * fw;
//    uint16_t total_height = fh;
//
//    // Kiểm tra vượt biên
//    if(x + total_width > tft.width) {
//        len = (tft.width - x) / fw;
//        total_width = len * fw;
//    }
//    if(y + total_height > tft.height) return;
//
//    // Giới hạn bộ nhớ giống như trước
//    uint16_t max_chars = (fh > 15) ? 10 : 20;
//    if(len > max_chars) {
//        // chia nhỏ và gọi lại
//        while(len > 0) {
//            uint16_t chunk_len = (len > max_chars) ? max_chars : len;
//            char chunk[21];
//            strncpy(chunk, str, chunk_len);
//            chunk[chunk_len] = '\0';
//            ST7735_DrawStringFast(x, y, chunk, font, color, bg);
//            x += chunk_len * fw;
//            str += chunk_len;
//            len -= chunk_len;
//        }
//        return;
//    }
//
//    // bộ đệm pixel (big enough)
//    static uint8_t pixel_buffer[20 * 20 * 20 * 2];
//    uint32_t buf_idx = 0;
//
//    // xây từng hàng
//    for(uint16_t row = 0; row < fh; row++) {
//        temp = str;
//        for(uint16_t ch = 0; ch < len; ch++) {
//            char c = *temp++;
//            uint32_t char_index = (c - 32) * fh;
//            uint16_t line = font->data[char_index + row];
//
//            // dồn bits về phần thấp của word
//            uint16_t bits = (uint16_t)(line >> (16 - fw));
//
//            for(uint8_t col = 0; col < fw; col++) {
//                uint16_t mask = 1u << (fw - 1 - col);
//                uint16_t pixel_color = (bits & mask) ? color : bg;
//                pixel_buffer[buf_idx++] = pixel_color >> 8;
//                pixel_buffer[buf_idx++] = pixel_color & 0xFF;
//            }
//        }
//    }
//
//    // gửi 1 lần
//    setAddressWindow(x, y, x + total_width - 1, y + total_height - 1);
//    writeData(pixel_buffer, buf_idx);
//}
