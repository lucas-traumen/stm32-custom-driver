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
 * Do NOT call blocking functions (HAL_Delay, polling loops) inside ISRs.
 * ISRs should execute as briefly as possible — typically just set a flag
 * and return. Handle the actual work in main().
 *
 * Reference: Table 62. Vector table for STM32F405xx/07xx and STM32F415xx/17xx
 */
void IRQ_Init(void)
{
    /* Set priority grouping: 4 bits preempt, 0 bits sub-priority */
    DRV_NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_4);

    /* ===== Cortex-M4 System Exceptions (settable via SCB->SHP) ===== */
    // System exceptions use SHPR registers, not NVIC->IP.
    // Use DRV_NVIC_SetSystemHandlerPriority() for these.
    // NonMaskableInt (-14) and HardFault (-13) have FIXED priority — cannot be changed.
    //
    // Priority recommendation:
    //   MemManage / BusFault / UsageFault → 0 (highest, these are hard faults)
    //   SVCall                           → 5  (OS system call)
    //   DebugMonitor                     → 15 (lowest, debug only)
    //   PendSV                           → 15 (lowest, background context switch)
    //   SysTick                          → 15 (lowest, prevents priority inversion in HAL_Delay)

    // DRV_NVIC_SetSystemHandlerPriority(MemoryManagement_IRQn, 0, 0);
    // DRV_NVIC_SetSystemHandlerPriority(BusFault_IRQn, 0, 0);
    // DRV_NVIC_SetSystemHandlerPriority(UsageFault_IRQn, 0, 0);
    // DRV_NVIC_SetSystemHandlerPriority(SVCall_IRQn, 5, 0);
    // DRV_NVIC_SetSystemHandlerPriority(DebugMonitor_IRQn, 15, 0);
    // DRV_NVIC_SetSystemHandlerPriority(PendSV_IRQn, 15, 0);
    DRV_NVIC_SetSystemHandlerPriority(SysTick_IRQn, 15, 0);

    /* ===== Window WatchDog ===== */
    // DRV_NVIC_SetPriority(WWDG_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(WWDG_IRQn);

    /* ===== PVD (Power Voltage Detector) ===== */
    // DRV_NVIC_SetPriority(PVD_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(PVD_IRQn);

    /* ===== TAMP_STAMP (Tamper and TimeStamp) ===== */
    // DRV_NVIC_SetPriority(TAMP_STAMP_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(TAMP_STAMP_IRQn);

    /* ===== RTC_WKUP (RTC Wakeup) ===== */
    // DRV_NVIC_SetPriority(RTC_WKUP_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(RTC_WKUP_IRQn);

    /* ===== FLASH global ===== */
    // DRV_NVIC_SetPriority(FLASH_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(FLASH_IRQn);

    /* ===== RCC global ===== */
    // DRV_NVIC_SetPriority(RCC_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(RCC_IRQn);

    /* ===== EXTI Interrupts (External Interrupts) ===== */
    // EXTI Line0 (PA0..PI0)
       DRV_NVIC_SetPriority(EXTI0_IRQn, 3, 0);
       DRV_NVIC_EnableIRQ(EXTI0_IRQn);

    // EXTI Line1 (PA1..PI1)
    // DRV_NVIC_SetPriority(EXTI1_IRQn, 3, 0);
    // DRV_NVIC_EnableIRQ(EXTI1_IRQn);

    // EXTI Line2 (PA2..PI2)
    // DRV_NVIC_SetPriority(EXTI2_IRQn, 3, 0);
    // DRV_NVIC_EnableIRQ(EXTI2_IRQn);

    // EXTI Line3 (PA3..PI3)
    // DRV_NVIC_SetPriority(EXTI3_IRQn, 3, 0);
    // DRV_NVIC_EnableIRQ(EXTI3_IRQn);

    // EXTI Line4 (PA4..PI4)
    // DRV_NVIC_SetPriority(EXTI4_IRQn, 3, 0);
    // DRV_NVIC_EnableIRQ(EXTI4_IRQn);

    // EXTI Lines 5-9 (shared handler)
    // DRV_NVIC_SetPriority(EXTI9_5_IRQn, 3, 0);
    // DRV_NVIC_EnableIRQ(EXTI9_5_IRQn);

    // EXTI Lines 10-15 (shared handler)
    // DRV_NVIC_SetPriority(EXTI15_10_IRQn, 3, 0);
    // DRV_NVIC_EnableIRQ(EXTI15_10_IRQn);

    /* ===== DMA1 Interrupts ===== */
    // DMA1 Stream 0
    // DRV_NVIC_SetPriority(DMA1_Stream0_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(DMA1_Stream0_IRQn);

    // DMA1 Stream 1
    // DRV_NVIC_SetPriority(DMA1_Stream1_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(DMA1_Stream1_IRQn);

    // DMA1 Stream 2
    // DRV_NVIC_SetPriority(DMA1_Stream2_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(DMA1_Stream2_IRQn);

    // DMA1 Stream 3
    // DRV_NVIC_SetPriority(DMA1_Stream3_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(DMA1_Stream3_IRQn);

    // DMA1 Stream 4
    // DRV_NVIC_SetPriority(DMA1_Stream4_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(DMA1_Stream4_IRQn);

    // DMA1 Stream 5
    // DRV_NVIC_SetPriority(DMA1_Stream5_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

    // DMA1 Stream 6
    // DRV_NVIC_SetPriority(DMA1_Stream6_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(DMA1_Stream6_IRQn);

    // DMA1 Stream 7
    // DRV_NVIC_SetPriority(DMA1_Stream7_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(DMA1_Stream7_IRQn);

    /* ===== ADC1/2/3 global ===== */
    // DRV_NVIC_SetPriority(ADC_IRQn, 5, 0);
    // DRV_NVIC_EnableIRQ(ADC_IRQn);

    /* ===== CAN1 Interrupts ===== */
    // DRV_NVIC_SetPriority(CAN1_TX_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(CAN1_TX_IRQn);

    // DRV_NVIC_SetPriority(CAN1_RX0_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(CAN1_RX0_IRQn);

    // DRV_NVIC_SetPriority(CAN1_RX1_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(CAN1_RX1_IRQn);

    // DRV_NVIC_SetPriority(CAN1_SCE_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(CAN1_SCE_IRQn);

    /* ===== TIM1 and TIM9-11 (TIM1 break, update, trigger/commutation, capture) ===== */
    // DRV_NVIC_SetPriority(TIM1_BRK_TIM9_IRQn, 5, 0);
    // DRV_NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);

    // DRV_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 5, 0);
    // DRV_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);

    // DRV_NVIC_SetPriority(TIM1_TRG_COM_TIM11_IRQn, 5, 0);
    // DRV_NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);

    // DRV_NVIC_SetPriority(TIM1_CC_IRQn, 5, 0);
    // DRV_NVIC_EnableIRQ(TIM1_CC_IRQn);

    /* ===== TIM2..TIM5 ===== */
    // DRV_NVIC_SetPriority(TIM2_IRQn, 5, 0);
    // DRV_NVIC_EnableIRQ(TIM2_IRQn);

    // DRV_NVIC_SetPriority(TIM3_IRQn, 5, 0);
    // DRV_NVIC_EnableIRQ(TIM3_IRQn);

    // DRV_NVIC_SetPriority(TIM4_IRQn, 5, 0);
    // DRV_NVIC_EnableIRQ(TIM4_IRQn);

    // DRV_NVIC_SetPriority(TIM5_IRQn, 5, 0);
    // DRV_NVIC_EnableIRQ(TIM5_IRQn);

    /* ===== TIM6_DAC, TIM7 ===== */
    // DRV_NVIC_SetPriority(TIM6_DAC_IRQn, 5, 0);
    // DRV_NVIC_EnableIRQ(TIM6_DAC_IRQn);

    // DRV_NVIC_SetPriority(TIM7_IRQn, 5, 0);
    // DRV_NVIC_EnableIRQ(TIM7_IRQn);

    /* ===== I2C Interrupts ===== */
    // I2C1
    // DRV_NVIC_SetPriority(I2C1_EV_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(I2C1_EV_IRQn);
    // DRV_NVIC_SetPriority(I2C1_ER_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(I2C1_ER_IRQn);

    // I2C2
    // DRV_NVIC_SetPriority(I2C2_EV_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(I2C2_EV_IRQn);
    // DRV_NVIC_SetPriority(I2C2_ER_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(I2C2_ER_IRQn);

    // I2C3
    // DRV_NVIC_SetPriority(I2C3_EV_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(I2C3_EV_IRQn);
    // DRV_NVIC_SetPriority(I2C3_ER_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(I2C3_ER_IRQn);

    /* ===== SPI Interrupts ===== */
    DRV_NVIC_SetPriority(SPI1_IRQn, 6, 0);
    DRV_NVIC_EnableIRQ(SPI1_IRQn);

    DRV_NVIC_SetPriority(SPI2_IRQn, 6, 0);
    DRV_NVIC_EnableIRQ(SPI2_IRQn);

    // DRV_NVIC_SetPriority(SPI3_IRQn, 6, 0);
    // DRV_NVIC_EnableIRQ(SPI3_IRQn);

    /* ===== USART/UART Interrupts ===== */
    // DRV_NVIC_SetPriority(USART1_IRQn, 8, 0);
    // DRV_NVIC_EnableIRQ(USART1_IRQn);

    // DRV_NVIC_SetPriority(USART2_IRQn, 8, 0);
    // DRV_NVIC_EnableIRQ(USART2_IRQn);

    // DRV_NVIC_SetPriority(USART3_IRQn, 8, 0);
    // DRV_NVIC_EnableIRQ(USART3_IRQn);

    // DRV_NVIC_SetPriority(UART4_IRQn, 8, 0);
    // DRV_NVIC_EnableIRQ(UART4_IRQn);

    // DRV_NVIC_SetPriority(UART5_IRQn, 8, 0);
    // DRV_NVIC_EnableIRQ(UART5_IRQn);

    // DRV_NVIC_SetPriority(USART6_IRQn, 8, 0);
    // DRV_NVIC_EnableIRQ(USART6_IRQn);

    /* ===== RTC Alarm ===== */
    // DRV_NVIC_SetPriority(RTC_Alarm_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(RTC_Alarm_IRQn);

    /* ===== OTG_FS (USB Full Speed) ===== */
    // DRV_NVIC_SetPriority(OTG_FS_WKUP_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(OTG_FS_WKUP_IRQn);

    // DRV_NVIC_SetPriority(OTG_FS_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(OTG_FS_IRQn);

    /* ===== TIM8 and TIM12-14 ===== */
    // DRV_NVIC_SetPriority(TIM8_BRK_TIM12_IRQn, 5, 0);
    // DRV_NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn);

    // DRV_NVIC_SetPriority(TIM8_UP_TIM13_IRQn, 5, 0);
    // DRV_NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);

    // DRV_NVIC_SetPriority(TIM8_TRG_COM_TIM14_IRQn, 5, 0);
    // DRV_NVIC_EnableIRQ(TIM8_TRG_COM_TIM14_IRQn);

    // DRV_NVIC_SetPriority(TIM8_CC_IRQn, 5, 0);
    // DRV_NVIC_EnableIRQ(TIM8_CC_IRQn);

    /* ===== FSMC (Flexible Static Memory Controller) ===== */
    // DRV_NVIC_SetPriority(FSMC_IRQn, 9, 0);
    // DRV_NVIC_EnableIRQ(FSMC_IRQn);

    /* ===== SDIO ===== */
    // DRV_NVIC_SetPriority(SDIO_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(SDIO_IRQn);

    /* ===== DMA2 Interrupts (8 streams) ===== */
    // DRV_NVIC_SetPriority(DMA2_Stream0_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

    // DRV_NVIC_SetPriority(DMA2_Stream1_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(DMA2_Stream1_IRQn);

    // DRV_NVIC_SetPriority(DMA2_Stream2_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

    // DRV_NVIC_SetPriority(DMA2_Stream3_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(DMA2_Stream3_IRQn);

    // DRV_NVIC_SetPriority(DMA2_Stream4_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(DMA2_Stream4_IRQn);

    // DRV_NVIC_SetPriority(DMA2_Stream5_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(DMA2_Stream5_IRQn);

    // DRV_NVIC_SetPriority(DMA2_Stream6_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(DMA2_Stream6_IRQn);

    // DRV_NVIC_SetPriority(DMA2_Stream7_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(DMA2_Stream7_IRQn);

    /* ===== Ethernet ===== */
    // DRV_NVIC_SetPriority(ETH_IRQn, 6, 0);
    // DRV_NVIC_EnableIRQ(ETH_IRQn);

    // DRV_NVIC_SetPriority(ETH_WKUP_IRQn, 6, 0);
    // DRV_NVIC_EnableIRQ(ETH_WKUP_IRQn);

    /* ===== CAN2 Interrupts ===== */
    // DRV_NVIC_SetPriority(CAN2_TX_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(CAN2_TX_IRQn);

    // DRV_NVIC_SetPriority(CAN2_RX0_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(CAN2_RX0_IRQn);

    // DRV_NVIC_SetPriority(CAN2_RX1_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(CAN2_RX1_IRQn);

    // DRV_NVIC_SetPriority(CAN2_SCE_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(CAN2_SCE_IRQn);

    /* ===== OTG_HS (USB High Speed) ===== */
    // DRV_NVIC_SetPriority(OTG_HS_EP1_OUT_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(OTG_HS_EP1_OUT_IRQn);

    // DRV_NVIC_SetPriority(OTG_HS_EP1_IN_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(OTG_HS_EP1_IN_IRQn);

    // DRV_NVIC_SetPriority(OTG_HS_WKUP_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(OTG_HS_WKUP_IRQn);

    // DRV_NVIC_SetPriority(OTG_HS_IRQn, 7, 0);
    // DRV_NVIC_EnableIRQ(OTG_HS_IRQn);

    /* ===== DCMI (Digital Camera Interface) ===== */
    // DRV_NVIC_SetPriority(DCMI_IRQn, 8, 0);
    // DRV_NVIC_EnableIRQ(DCMI_IRQn);

    /* ===== CRYP (Cryptographic) ===== */
    // DRV_NVIC_SetPriority(CRYP_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(CRYP_IRQn);

    /* ===== HASH / RNG ===== */
    // DRV_NVIC_SetPriority(HASH_RNG_IRQn, 10, 0);
    // DRV_NVIC_EnableIRQ(HASH_RNG_IRQn);

    /* ===== FPU (Floating Point Unit) ===== */
    // DRV_NVIC_SetPriority(FPU_IRQn, 15, 0);
    // DRV_NVIC_EnableIRQ(FPU_IRQn);
}
