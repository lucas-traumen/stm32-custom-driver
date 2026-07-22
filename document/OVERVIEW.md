# STM32F407 Custom Driver - Progress Dashboard

Custom bare-metal driver cho STM32F407VGTx theo OOP/HAL pattern.

**MCU:** STM32F407VGTx | **Board:** Discovery | **CPU:** Cortex-M4 + FPU

---

## Driver Progress

### ✅ Completed Drivers

| Driver | Features | Doc |
|--------|----------|-----|
| **GPIO** | Init, Read/Write, Toggle, EXTI | [gpio.md](gpio.md) |
| **SPI** | Master/Slave, 8/16-bit, TX/RX | [spi.md](spi.md) |
| **RCC** | Clock enable/disable macros | [rcc.md](rcc.md) |
| **EXTI** | External interrupt, callback | [exti_nvic.md](exti_nvic.md) |
| **NVIC** | Priority, IRQ control | [exti_nvic.md](exti_nvic.md) |

### ⚠️ Work In Progress

| Driver | Status |
|--------|--------|
| **I2C** | Skeleton code (commented) |

### ⏳ Planned

- **USART** - High priority (hiện dùng direct register)
- **Timer/PWM** - Medium priority
- **ADC** - Medium priority
- **DMA** - Low priority (complex)

---

## Architecture

```
Application (main.c)
    ↓
Driver Layer (OOP pattern)
├─ gpio_driver.h/.c     Handle + Config struct
├─ spi_driver.h/.c      Init → Config → Enable
├─ rcc_driver.h/.c
├─ exti_driver.h/.c
└─ nvic_driver.h/.c
    ↓
┌────────────────┬──────────────────┐
stm32f407xx.h    stm32f4xx_common.h
(CMSIS)          (ENABLE/DISABLE...)
```

---

## Current Issues

| Issue | Impact | Next |
|-------|--------|------|
| Circular dependency | Rebuild toàn bộ khi sửa 1 driver | Phase 2-6 |
| Naming inconsistent | `gpio.h` vs `spi_driver.h` | Rename phase |
| No common header | Duplicate defs | Create common.h |

---

## Build

```bash
make -C Debug        # Build
make -C Debug clean  # Clean
```

**Clock:** HSI 16MHz (PLL config commented out)

---

## Restructure Status

**Phase 1: Cleanup** ✅ Done
- Xóa: led.h, SYSCFG.h, init.c, rcc.c

**Phase 2-6:** ⏳ Next session (~30k token)
- Create stm32f4xx_common.h
- Rename files → consistent naming
- Remove system.h hub
- Independent headers

---

## Quick Links

- [GPIO](gpio.md) | [SPI](spi.md) | [I2C](i2c.md) | [RCC](rcc.md) | [EXTI/NVIC](exti_nvic.md)
- [README](README.md) - Peripheral doc index
