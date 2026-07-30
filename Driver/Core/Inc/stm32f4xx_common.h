#ifndef STM32F4XX_COMMON_H
#define STM32F4XX_COMMON_H

#include <stdint.h>
#include <stddef.h>

/* Type qualifiers */
#define __IM     volatile const      /* Read-only */
#define __IO     volatile           /* Read-write */
#define __weak   __attribute__((weak))

/* Common value definitions */
#define RESET          0
#define SET            1
#define DISABLE        RESET
#define ENABLE         SET
#define GPIO_PIN_RESET RESET
#define GPIO_PIN_SET   SET
#define FLAG_RESET     RESET
#define FLAG_SET       SET

/* Common driver status codes, returned by all peripheral APIs */
typedef enum {
    STATUS_OK      = 0,
    STATUS_ERROR   = 1,
    STATUS_TIMEOUT = 2,
    STATUS_BUSY    = 3
} DriverStatus_t;

/* Memory base addresses (optional - for reference) */
#define FLASH_BASE_ADDRESS 0x08000000U
#define SRAM_BASE_ADDRESS  0x20000000U

#endif /* STM32F4XX_COMMON_H */
