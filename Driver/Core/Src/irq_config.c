#include "irq_config.h"

/**
 * @brief Initialize all interrupt configurations for the project
 *
 * This function centralizes all NVIC interrupt setup. When a peripheral
 * needs interrupt mode, uncomment its section below and configure priority.
 *
 * Priority notes:
 * - Lower number = higher priority
 * - PreemptPriority: Higher priority can interrupt lower priority ISR
 * - SubPriority: Used when two interrupts with same preempt priority occur simultaneously
 *
 * Example priority allocation:
 * - 0-2: Critical (system tick, hard fault recovery)
 * - 3-5: High priority peripherals (EXTI for urgent events)
 * - 6-10: Normal peripherals (SPI, I2C, USART)
 * - 11-15: Low priority (background tasks, DMA complete)
 */
void IRQ_Init(void)
{
    /* Set priority grouping: 4 bits preempt, 0 bits sub-priority */
    NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_4);

    /* ===== SPI Interrupts ===== */
    // Uncomment when using SPI in interrupt mode
    // NVIC_SetPriority(SPI1_IRQn, 6, 0);
    // NVIC_EnableIRQ(SPI1_IRQn);

    // NVIC_SetPriority(SPI2_IRQn, 6, 0);
    // NVIC_EnableIRQ(SPI2_IRQn);

    // NVIC_SetPriority(SPI3_IRQn, 6, 0);
    // NVIC_EnableIRQ(SPI3_IRQn);

    /* ===== I2C Interrupts ===== */
    // Uncomment when using I2C in interrupt mode
    // I2C1 Event interrupt
    // NVIC_SetPriority(I2C1_EV_IRQn, 7, 0);
    // NVIC_EnableIRQ(I2C1_EV_IRQn);

    // I2C1 Error interrupt
    // NVIC_SetPriority(I2C1_ER_IRQn, 7, 0);
    // NVIC_EnableIRQ(I2C1_ER_IRQn);

    // I2C2 Event interrupt
    // NVIC_SetPriority(I2C2_EV_IRQn, 7, 0);
    // NVIC_EnableIRQ(I2C2_EV_IRQn);

    // I2C2 Error interrupt
    // NVIC_SetPriority(I2C2_ER_IRQn, 7, 0);
    // NVIC_EnableIRQ(I2C2_ER_IRQn);

    /* ===== USART Interrupts ===== */
    // Uncomment when using USART in interrupt mode
    // NVIC_SetPriority(USART1_IRQn, 8, 0);
    // NVIC_EnableIRQ(USART1_IRQn);

    // NVIC_SetPriority(USART2_IRQn, 8, 0);
    // NVIC_EnableIRQ(USART2_IRQn);

    // NVIC_SetPriority(USART3_IRQn, 8, 0);
    // NVIC_EnableIRQ(USART3_IRQn);

    /* ===== EXTI Interrupts (GPIO external interrupts) ===== */
    // Uncomment when using GPIO interrupt mode
    // EXTI0 (PA0, PB0, PC0, etc.)
    // NVIC_SetPriority(EXTI0_IRQn, 3, 0);
    // NVIC_EnableIRQ(EXTI0_IRQn);

    // EXTI1 (PA1, PB1, PC1, etc.)
    // NVIC_SetPriority(EXTI1_IRQn, 3, 0);
    // NVIC_EnableIRQ(EXTI1_IRQn);

    // EXTI2 (PA2, PB2, PC2, etc.)
    // NVIC_SetPriority(EXTI2_IRQn, 3, 0);
    // NVIC_EnableIRQ(EXTI2_IRQn);

    // EXTI3 (PA3, PB3, PC3, etc.)
    // NVIC_SetPriority(EXTI3_IRQn, 3, 0);
    // NVIC_EnableIRQ(EXTI3_IRQn);

    // EXTI4 (PA4, PB4, PC4, etc.)
    // NVIC_SetPriority(EXTI4_IRQn, 3, 0);
    // NVIC_EnableIRQ(EXTI4_IRQn);

    // EXTI9_5 (EXTI5 to EXTI9 share one IRQ handler)
    // NVIC_SetPriority(EXTI9_5_IRQn, 3, 0);
    // NVIC_EnableIRQ(EXTI9_5_IRQn);

    // EXTI15_10 (EXTI10 to EXTI15 share one IRQ handler)
    // NVIC_SetPriority(EXTI15_10_IRQn, 3, 0);
    // NVIC_EnableIRQ(EXTI15_10_IRQn);

    /* ===== Timer Interrupts ===== */
    // Uncomment when using Timer in interrupt mode
    // NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 5, 0);
    // NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);

    // NVIC_SetPriority(TIM2_IRQn, 5, 0);
    // NVIC_EnableIRQ(TIM2_IRQn);

    // NVIC_SetPriority(TIM3_IRQn, 5, 0);
    // NVIC_EnableIRQ(TIM3_IRQn);

    // NVIC_SetPriority(TIM4_IRQn, 5, 0);
    // NVIC_EnableIRQ(TIM4_IRQn);

    /* ===== DMA Interrupts ===== */
    // Uncomment when using DMA
    // DMA1 Stream 0
    // NVIC_SetPriority(DMA1_Stream0_IRQn, 10, 0);
    // NVIC_EnableIRQ(DMA1_Stream0_IRQn);

    // Add more DMA streams as needed
}
