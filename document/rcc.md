# RCC (Reset and Clock Control)

## Tổng quan

File `rcc.h` định nghĩa các macro bật/tắt/reset clock cho tất cả peripheral trong project. File `rcc.c` có code init PLL (hiện đang comment out — project đang chạy HSI 16MHz mặc định).

## Clock Macros

### GPIO (AHB1)

```c
GPIOx_PCLK_EN()     // Bật clock
GPIOx_PCLK_DI()     // Tắt clock
GPIOx_PCLK_RESET()  // Reset peripheral (set rồi clear bit trong AHB1RSTR)
```

x = A, B, C, D, E, F, G, H, I

### SPI

```c
SPI1_PCLK_EN()   // APB2 bit 12
SPI2_PCLK_EN()   // APB1 bit 14
SPI3_PCLK_EN()   // APB1 bit 15
SPIx_PCLK_RESET()
```

### I2C (chưa active)

```c
I2C1_PCLK_EN()   // APB1 bit 21
I2C2_PCLK_EN()   // APB1 bit 22
I2C3_PCLK_EN()   // APB1 bit 23
```

### Timer

```c
TIMER1_CLK_EN()  // APB2 bit 0
```

### SYSCFG

```c
SYSCFG_PCLK_EN() // APB2 bit 14 (cần cho EXTI config)
```

## PLL Init (commented out)

Khi cần clock cao hơn 16MHz (ví dụ 100MHz):

```
HSE (8MHz) → PLL: M=/8, N=x200, P=/2 → SYSCLK = 100MHz
APB1 = SYSCLK/2 = 50MHz
APB2 = SYSCLK/1 = 100MHz
Flash latency = 3 wait states
```

## Lưu ý hiện tại

- Project đang chạy HSI 16MHz (PLL init bị comment).
- USART1 BRR tính theo 16MHz → nếu bật PLL phải tính lại BRR.
- SPI baud rate cũng phụ thuộc APB clock → thay đổi clock source phải review lại tất cả peripheral config.

## Debug tips

- Peripheral không phản hồi: nguyên nhân #1 là quên bật clock → kiểm tra RCC->AHBxENR / APBxENR
- Reset macro dùng pattern `set bit; clear bit` trong do-while(0) → an toàn dùng trong if/else
- `SYSCFG_PCLK_EN()` cần gọi trước khi config EXTICR (đã được gọi trong GPIO_Init)
