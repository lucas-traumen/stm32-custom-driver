# STM32F407 Custom Driver - Architecture Overview

## Giới thiệu

Custom bare-metal driver layer cho STM32F407VGTx, theo pattern OOP/HAL style.

**Đặc điểm:**
- OOP pattern: Handle struct + Config struct
- Register-level programming
- Tích hợp CMSIS-DSP

---

## 1. Cấu trúc hiện tại

### Driver organization
```
Driver/
├── CSMIS/
│   └── Device/ST/STM32F4xx/Include/
│       └── stm32f407xx.h         # CMSIS register definitions
│
└── Core/
    ├── Inc/
    │   ├── gpio.h                # ⚠️ Thiếu _driver suffix
    │   ├── spi_driver.h          # ✅ Đúng naming
    │   ├── rcc.h                 # ⚠️ Thiếu suffix + macros
    │   ├── exti.h, nvic.h        # ⚠️ Thiếu suffix
    │   ├── system.h              # ❌ Hub (circular dependency)
    │   └── stm32f4xx_it.h        # Interrupt handlers
    └── Src/
        ├── gpio.c
        ├── spi_driver.c
        ├── exti.c, nvic.c
        ├── i2c_driver.c          # ⚠️ WIP (commented)
        └── stm32f4xx_it.c
```

### Vấn đề cần fix

**1. Circular dependency:**
```
system.h ──includes──> gpio.h, spi_driver.h, rcc.h, exti.h, nvic.h
   ↑                                                              │
   └──────────────────── all include system.h ──────────────────┘
```

**2. Naming không consistent:**
- `spi_driver.h` ✅ có suffix
- `gpio.h`, `rcc.h`, `exti.h` ❌ không có

**3. Namespace pollution:**
- Include system.h → kéo theo 7+ headers
- Rebuild 1 driver → rebuild toàn bộ

---

## 2. Kiến trúc mục tiêu

### Layered architecture
```
┌─────────────────────────────────┐
│  Application                    │
│  main.c, examples/              │
└──────────────┬──────────────────┘
               │
┌──────────────▼──────────────────┐
│  Umbrella Header (optional)     │
│  stm32f4xx_drivers.h            │
└──────────────┬──────────────────┘
               │
┌──────────────▼──────────────────┐
│  Peripheral Drivers             │
│  (độc lập, không include nhau)  │
│                                 │
│  gpio_driver.h/.c               │
│  spi_driver.h/.c                │
│  rcc_driver.h/.c                │
│  exti_driver.h/.c               │
│  nvic_driver.h/.c               │
└──────────────┬──────────────────┘
               │
    ┌──────────┴─────────┐
    ▼                    ▼
┌──────────────┐  ┌─────────────────┐
│stm32f407xx.h │  │stm32f4xx_common.h│
│(CMSIS)       │  │(Custom defs)     │
│- Registers   │  │- ENABLE/DISABLE  │
│- IRQn_Type   │  │- RESET/SET       │
└──────────────┘  └─────────────────┘
```

### Naming convention
```
stm32f4xx_common.h       ← Common definitions

gpio_driver.h/.c         ← Peripheral drivers
spi_driver.h/.c          
rcc_driver.h/.c
nvic_driver.h/.c
exti_driver.h/.c
usart_driver.h/.c        ← (future)

stm32f4xx_drivers.h      ← Umbrella (optional)
```

### Dependency rules

**✅ Allowed:**
```c
// Driver header
#include "stm32f407xx.h"
#include "stm32f4xx_common.h"

// Cross-driver (minimal)
spi_driver.h → gpio_driver.h  (cần cho AF config)

// Source files
#include "rcc_driver.h"        (cần clock macros)
```

**❌ Not allowed:**
```c
#include "system.h"            // No hub
gpio_driver.h → spi_driver.h   // No circular
```

---

## 3. Driver Pattern

### OOP Style (consistent across all peripherals)

```c
// Config struct
typedef struct {
    uint8_t Param1;
    uint8_t Param2;
    // ...
} PERIPH_Config_t;

// Handle struct
typedef struct {
    PERIPH_TypeDef *pPERIPHx;
    PERIPH_Config_t Config;
} PERIPH_Handle_t;

// API
void PERIPH_Init(PERIPH_Handle_t *pHandle);
void PERIPH_DeInit(PERIPH_TypeDef *pPERIPHx);
// ... peripheral-specific functions
```

### Init sequence (chuẩn)
```c
// 1. Declare handle
PERIPH_Handle_t hperiph;

// 2. Assign base address
hperiph.pPERIPHx = PERIPH1;

// 3. Configure
hperiph.Config.Param1 = VALUE1;
hperiph.Config.Param2 = VALUE2;

// 4. Init (auto enable clock inside)
PERIPH_Init(&hperiph);

// 5. Enable peripheral if needed
PERIPH_PeripheralControl(PERIPH1, ENABLE);
```

---

## 4. Peripheral Documentation

Mỗi peripheral có file `.md` chi tiết trong `document/`:

| Peripheral | Doc | Status |
|------------|-----|--------|
| GPIO | [gpio.md](gpio.md) | ✅ Complete |
| SPI | [spi.md](spi.md) | ✅ Complete |
| RCC | [rcc.md](rcc.md) | ✅ Complete |
| EXTI/NVIC | [exti_nvic.md](exti_nvic.md) | ✅ Complete |
| I2C | [i2c.md](i2c.md) | ⚠️ WIP |

**Format chuẩn:**
1. OOP structure (Config_t + Handle_t)
2. Init sequence (code example)
3. API table
4. Hardware notes
5. Debug tips

---

## 5. Restructure Roadmap

### Phase 1: Cleanup ✅ Done
- Xóa led.h, SYSCFG.h
- Xóa init.c, rcc.c (stub/commented)
- Xóa example_exti.c (optional)

### Phase 2: Create Common (next)
- Tạo `stm32f4xx_common.h`
- Move ENABLE/DISABLE/RESET/SET từ system.h

### Phase 3: Rename Files
```bash
gpio.h/.c      → gpio_driver.h/.c
rcc.h          → rcc_driver.h
exti.h/.c      → exti_driver.h/.c
nvic.h         → nvic_driver.h
```

### Phase 4: Update Includes
- Mỗi driver header:
  - Xóa `#include "system.h"`
  - Thêm `#include "stm32f407xx.h"`
  - Thêm `#include "stm32f4xx_common.h"`

### Phase 5: Umbrella Header
- Tạo `stm32f4xx_drivers.h`
- Include tất cả drivers

### Phase 6: Remove Hub
- Xóa `system.h`
- Update main.c

---

## 6. Build & Tools

**MCU:** STM32F407VGTx (Cortex-M4 + FPU)  
**Board:** STM32F407 Discovery  
**Clock:** HSI 16MHz (PLL commented)  
**Toolchain:** GNU ARM (arm-none-eabi-gcc)  
**IDE:** STM32CubeIDE

**Build commands:**
```bash
make -C Debug
make -C Debug clean
```

---

## 7. Project Goals

### Completed
- [x] GPIO driver + doc
- [x] SPI driver + doc
- [x] RCC clock macros + doc
- [x] EXTI/NVIC driver + doc
- [x] Documentation system
- [x] Workflow rules (internal)

### In Progress
- [ ] Restructure driver layer
- [ ] I2C driver (code đang comment)

### Future
- [ ] USART driver (hiện dùng direct register)
- [ ] Timer/PWM driver
- [ ] ADC driver
- [ ] DMA integration

---

## Quick Links

- [GPIO Driver](gpio.md)
- [SPI Driver](spi.md)
- [I2C Driver](i2c.md) (WIP)
- [RCC/Clock](rcc.md)
- [EXTI/NVIC](exti_nvic.md)
