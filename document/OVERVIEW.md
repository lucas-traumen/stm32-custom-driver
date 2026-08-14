# STM32F407 Custom Driver - Overview

## 1. Hệ thống Driver

Custom bare-metal driver library cho STM32F407VGTx.

**Mục đích:**
- Viết driver từ đầu (không dùng ST HAL)
- Hiểu register programming
- Pattern OOP: Handle + Config struct

**Target:** STM32F407 Discovery | Cortex-M4 + FPU | HSI 16MHz

---

## 2. Kiến trúc Layer

```
Application Code (main.c)
    ↓ include
stm32f4xx_drivers.h (umbrella - optional)
    ↓ include all
┌───────────────────────────────┐
│   Driver Layer (độc lập)      │
├─ gpio_driver.h/.c             │
├─ spi_driver.h/.c              │
├─ rcc_driver.h/.c              │
├─ exti_driver.h/.c             │
└─ nvic_driver.h/.c             │
└───────────────────────────────┘
    ↓ include
┌────────────────┬──────────────────┐
│stm32f407xx.h   │stm32f4xx_common.h│
│(CMSIS)         │(ENABLE/DISABLE)  │
└────────────────┴──────────────────┘
```

**Nguyên tắc:**
- Mỗi driver độc lập (không include nhau)
- Chỉ include: stm32f407xx.h + stm32f4xx_common.h
- Source file (.c) mới include cross-driver nếu cần

---

## 3. Cách sử dụng Driver

### Pattern chuẩn (mọi peripheral)

**Bước 1: Khai báo handle**
```c
GPIO_Handle_t hgpio;        // Handle = base addr + config
```

**Bước 2: Cấu hình**
```c
hgpio.pGPIOx = GPIOD;                              // Chọn port
hgpio.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
hgpio.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
hgpio.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
hgpio.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
```

**Bước 3: Init (tự bật clock bên trong)**
```c
GPIO_Init(&hgpio);
```

**Bước 4: Sử dụng**
```c
GPIO_Write_Pin(&hgpio, GPIO_PIN_NO_13, SET);
GPIO_Toggle_Pin(&hgpio, GPIO_PIN_NO_13);
```

### Ví dụ SPI

```c
SPI_Handle_t hspi2;
hspi2.pSPIx = SPI2;
hspi2.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
hspi2.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
hspi2.SPIConfig.SPI_DFF = SPI_DFF_8bits;
// ... config khác

SPI_Init(&hspi2);                          // Init + bật clock
SPI_SSI_Config(SPI2, ENABLE);              // Set SSI nếu SSM=1
SPI_PeripheralControl(SPI2, ENABLE);       // Bật SPE

SPI_SendData(SPI2, txbuf, len);            // Gửi data
```

---

## 4. Tiến độ Driver

### Đang phát triển (WIP)
- ⚠️ **GPIO** - Init, Read/Write, Toggle, EXTI → [driver/gpio/gpio.md](driver/gpio/gpio.md)
- ⚠️ **SPI** - Master/Slave, blocking TX/RX → [driver/spi/spi.md](driver/spi/spi.md)
- ⚠️ **RCC** - Clock macros → [driver/rcc/rcc.md](driver/rcc/rcc.md)
- ⚠️ **EXTI/NVIC** - Interrupt handling → [driver/exti_nvic/exti_nvic.md](driver/exti_nvic/exti_nvic.md)
- ⚠️ **I2C** - Code skeleton (commented) → [driver/i2c/i2c.md](driver/i2c/i2c.md)
- ⚠️ **Restructure** - Đã xong naming, loại bỏ circular dependency

### Ngoại vi (Peripheral)
- ✅ **ILI9486** - LCD 3.5" 8080 parallel → [peripheral/ili9486.md](peripheral/ili9486.md)

### Kế hoạch
- **USART** - Hiện dùng direct register trong main.c
- **Timer/PWM**
- **ADC**
- **DMA**

---

## 5. Build Project

```bash
make -C Debug              # Build
make -C Debug clean        # Clean
```

**Toolchain:** GNU ARM (arm-none-eabi-gcc)  
**IDE:** STM32CubeIDE managed makefile

---

## 6. Tài liệu chi tiết

Mỗi driver/ngoại vi có file `.md` riêng, chia theo thư mục:

**`driver/`** - Driver nền (GPIO/SPI/RCC/NVIC/EXTI, style trực tiếp/register, không dùng function pointer)
- [GPIO](driver/gpio/gpio.md) - Cấu trúc, API, debug tips
- [SPI](driver/spi/spi.md) - Config, SSM/SSI, pin mapping
- [I2C](driver/i2c/i2c.md) - WIP
- [RCC](driver/rcc/rcc.md) - Clock macros
- [EXTI/NVIC](driver/exti_nvic/exti_nvic.md) - Interrupt handling

**`peripheral/`** - Ngoại vi (board/màn/sensor gắn ngoài, có thể dùng function pointer cho setup-level ops)
- [ILI9486](peripheral/ili9486.md) - LCD 3.5" 320x480, 8080 parallel

**Format:** Struct → Init sequence → API → Notes → Debug
