#include "irq_config.h"

/**
 * @brief Initialize all interrupt configurations for the project
 *
 * This function centralizes all NVIC interrupt setup. When a peripheral
 * needs interrupt mode, uncomment its section below and configure priority.
 *
 * System exception priority (fixed by hardware, not configurable):
 *   Reset      : -3 (highest)
 *   NMI        : -2
 *   HardFault  : -1
 *
 * Priority notes:
 * - Lower numerical value = higher urgency.
 * - PreemptPriority decides whether one IRQ can preempt another.
 * - SubPriority only decides service order when multiple IRQs with same
 *   preempt priority are pending simultaneously.
 * - With NVIC_PRIORITY_GROUP_4: all 4 bits are preemption, subpriority is
 *   effectively unused (0).
 *
 * Priority allocation guideline (project convention, not hardware rule):
 * - 0-2  : Hard real-time / safety-critical events
 * - 3-5  : High-priority peripherals (time-sensitive EXTI, ADC, DMA with
 *          tight real-time deadlines)
 * - 6-10 : Normal peripherals (SPI, I2C, USART)
 * - 11-14: Low-priority processing (UART debug TX, background DMA)
 * - 15   : Lowest priority — typically SysTick (only increments uwTick).
 *          Keeping SysTick at 15 prevents priority inversion if code in
 *          a higher-priority ISR calls HAL_Delay().
 *
 * Important: DMA priority must be chosen by deadline, not by peripheral
 * name. A DMA complete that must swap buffers before the next ADC sample
 * arrives may need priority 4-5; a UART debug DMA can be priority 12.
 *
 * Do NOT call blocking functions (HAL_Delay, polling loops) inside ISRs.
 * ISRs should execute as briefly as possible — typically just set a flag
 * and return. Handle the actual work in main().
 */
void IRQ_Init(void)
{
    /* Set priority grouping: 4 bits preempt, 0 bits sub-priority */
    DRV_NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_4);

    /* ===== SPI Interrupts ===== */
    // Uncomment when using SPI in interrupt mode
    // DRV_NVIC_SetPriority(SPI1_IRQn, 6, 0);
    // DRV_NVIC_EnableIRQ(SPI1_IRQn);

    // DRV_NVIC_SetPriority(SPI2_IRQn, 6, 0);
    // DRV_NVIC_EnableIRQ(SPI2_IRQn);

    // DRV_NVIC_SetPriority(SPI3_IRQn, 6, 0);
    // DRV_NVIC_EnableIRQ(SPI3_IRQn);

    /* ===== I2C Interrupts ===== */
    // Uncomment when using I2C in interrupt mode
    // I2C1 Event interrupt
    // DRV_NVIC_SetPriority(I2C1_EV_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(I2C1_EV_IRQn);

    // I2C1 Error interrupt
    // DRV_NVIC_SetPriority(I2C1_ER_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(I2C1_ER_IRQn);

    // I2C2 Event interrupt
    // DRV_NVIC_SetPriority(I2C2_EV_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(I2C2_EV_IRQn);

    // I2C2 Error interrupt
    // DRV_NVIC_SetPriority(I2C2_ER_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(I2C2_ER_IRQn);

    /* ===== USART Interrupts ===== */
    // Uncomment when using USART in interrupt mode
    // DRV_NVIC_SetPriority(USART1_IRQn, 8, 0);
    // DRV_NVIC_EnableIRQ(USART1_IRQn);

    // DRV_NVIC_SetPriority(USART2_IRQn, 8, 0);
    // DRV_NVIC_EnableIRQ(USART2_IRQn);

    // DRV_NVIC_SetPriority(USART3_IRQn, 8, 0);
    // DRV_NVIC_EnableIRQ(USART3_IRQn);

    /* ===== EXTI Interrupts (GPIO external interrupts) ===== */
    // Uncomment when using GPIO interrupt mode
    // EXTI0 (PA0, PB0, PC0, etc.)
    // DRV_NVIC_SetPriority(EXTI0_IRQn, 3, 0);
    // DRV_NVIC_EnableIRQ(EXTI0_IRQn);

    // EXTI1 (PA1, PB1, PC1, etc.)
    // DRV_NVIC_SetPriority(EXTI1_IRQn, 3, 0);
    // DRV_NVIC_EnableIRQ(EXTI1_IRQn);

    // EXTI2 (PA2, PB2, PC2, etc.)
    // DRV_NVIC_SetPriority(EXTI2_IRQn, 3, 0);
    // DRV_NVIC_EnableIRQ(EXTI2_IRQn);

    // EXTI3 (PA3, PB3, PC3, etc.)
    // DRV_NVIC_SetPriority(EXTI3_IRQn, 3, 0);
    // DRV_NVIC_EnableIRQ(EXTI3_IRQn);

    // EXTI4 (PA4, PB4, PC4, etc.)
    // DRV_NVIC_SetPriority(EXTI4_IRQn, 3, 0);
    // DRV_NVIC_EnableIRQ(EXTI4_IRQn);

    // EXTI9_5 (EXTI5 to EXTI9 share one IRQ handler)
    // DRV_NVIC_SetPriority(EXTI9_5_IRQn, 3, 0);
    // DRV_NVIC_EnableIRQ(EXTI9_5_IRQn);

    // EXTI15_10 (EXTI10 to EXTI15 share one IRQ handler)
    // DRV_NVIC_SetPriority(EXTI15_10_IRQn, 3, 0);
    // DRV_NVIC_EnableIRQ(EXTI15_10_IRQn);

    /* ===== Timer Interrupts ===== */
    // Uncomment when using Timer in interrupt mode
    // DRV_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 5, 0);
    // DRV_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);

    // DRV_NVIC_SetPriority(TIM2_IRQn, 5, 0);
    // DRV_NVIC_EnableIRQ(TIM2_IRQn);

    // DRV_NVIC_SetPriority(TIM3_IRQn, 5, 0);
    // DRV_NVIC_EnableIRQ(TIM3_IRQn);

    // DRV_NVIC_SetPriority(TIM4_IRQn, 5, 0);
    // DRV_NVIC_EnableIRQ(TIM4_IRQn);

    /* ===== DMA Interrupts ===== */
    // Uncomment when using DMA
    // DMA1 Stream 0
    // DRV_NVIC_SetPriority(DMA1_Stream0_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(DMA1_Stream0_IRQn);

    // Add more DMA streams as needed
}
