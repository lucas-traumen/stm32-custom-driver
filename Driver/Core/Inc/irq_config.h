#ifndef IRQ_CONFIG_H
#define IRQ_CONFIG_H

#include "stm32f407xx.h"
#include "nvic_driver.h"

/**
 * @brief Initialize all interrupt configurations for the project
 *
 * This function sets up NVIC priority grouping and configures
 * all peripheral interrupts used in the project.
 * Call this once in main() before enabling any interrupts.
 */
void IRQ_Init(void);

#endif /* IRQ_CONFIG_H */
