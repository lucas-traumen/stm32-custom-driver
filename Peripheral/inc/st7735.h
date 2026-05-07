#ifndef __ST7735_H__
#define __ST7735_H__


#include <stdint.h>
#include "fonts.h"
#include "system.h"
#include "spi_driver.h"


// Font struct is defined in fonts.h, so it's removed from here to prevent re-declaration error.

// TFT struct
typedef struct {
	SPI_Handle_t *hspi;
    GPIO_TypeDef *GPIO_portCs;
    uint16_t GPIO_Pin_Cs;
    GPIO_TypeDef *GPIO_portA0;
    uint16_t GPIO_Pin_A0;
    GPIO_TypeDef *GPIO_portRESET;
    uint16_t GPIO_Pin_Reset;
    GPIO_TypeDef *GPIO_portBL;
    uint16_t GPIO_Pin_BL;
    uint16_t width;
    uint16_t height;
} ST7735_Typedef;

// Colors
#define	ST7735_BLACK     0x0000
#define	ST7735_BLUE      0x001F
#define	ST7735_RED       0xF800
#define	ST7735_GREEN     0x07E0
#define ST7735_CYAN      0x07FF
#define ST7735_MAGENTA   0xF81F
#define ST7735_YELLOW    0xFFE0
#define ST7735_WHITE     0xFFFF
#define ST7735_DARKCYAN  0x0451
#define ST7735_ORANGE 	 0xFD20
#define ST7735_LIGHTGREY 0xD69A
#define ST7735_DARKGREEN 0x03E0
#define ST7735_DARKGREY  0x7BEF
#define COLOR_BLUE       ST7735_BLUE
#define COLOR_DARK_GRAY  ST7735_DARKGREY

// MADCTL Bits
#define ST7735_MADCTL    0x36
#define ST7735_MADCTL_MY  0x80
#define ST7735_MADCTL_MX  0x40
#define ST7735_MADCTL_MV  0x20
#define ST7735_MADCTL_ML  0x10
#define ST7735_MADCTL_RGB 0x00
#define ST7735_MADCTL_BGR 0x08
#define ST7735_MADCTL_MH  0x04

extern ST7735_Typedef tft;

// Functions
void ST7735_Init(void);
void ST7735_Backlight_On(void);
void ST7735_Backlight_Off(void);
void ST7735_SetRotation(uint8_t rotation);

void ST7735_FillScreen(uint16_t color);
void ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ST7735_DrawLine(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t color);
void ST7735_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void ST7735_DrawCircle(int16_t x0,int16_t y0,int16_t r,uint16_t color);
void ST7735_FillCircle(int16_t x0,int16_t y0,int16_t r,uint16_t color);

// S?A L?I: B? `const` d? tuong th�ch v?i c�ch khai b�o font trong fonts.h
void ST7735_DrawChar(uint16_t x, uint16_t y, char c, FontDef *font, uint16_t color, uint16_t bg);
void ST7735_DrawString(uint16_t x, uint16_t y, char *str, FontDef *font, uint16_t color, uint16_t bg);
void ST7735_DrawStringFast(uint16_t x, uint16_t y, char *str, FontDef *font, uint16_t color, uint16_t bg) ;
#endif

