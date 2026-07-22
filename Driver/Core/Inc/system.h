#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <stdint.h>
#include <stddef.h>
#include "stm32f407xx.h"
#include "SYSCFG.h"
#include "spi_driver.h"
#include "gpio.h"
#include "rcc.h"
#include "nvic.h"
#include "exti.h"
#include "stm32f4xx_it.h"




#define __IM     volatile const
#define _vo volatile
#define __IO volatile
#define __weak __attribute__((weak))



// Memory
#define FLASH_MEMORY_ADDRESS 0x08000000U
#define SRAM_MEMORY_ADDRESS 0x20000000


//Access
#define RESET          0
#define SET            1
#define DISABLE        RESET
#define ENABLE         SET
#define GPIO_PIN_RESET RESET
#define GPIO_PIN_SET   SET
#define FLAG_RESET     RESET
#define FLAG_SET       SET




#endif
