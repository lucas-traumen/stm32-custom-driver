#include "stm32f4xx_it.h"
#include "exti_driver.h"
#include "spi_driver.h"

volatile uint32_t uwTick;  /* 1ms counter for delay_ms */

void delay_ms(uint32_t ms)
{
    uint32_t start = uwTick;
    while ((uwTick - start) < ms);
}

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
    while(1)
    {
    }
}

void MemManage_Handler(void)
{
    while(1)
    {
    }
}

void BusFault_Handler(void)
{
    while(1)
    {
    }
}

void UsageFault_Handler(void)
{
    while(1)
    {
    }
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
    uwTick++;
}

void EXTI0_IRQHandler(void)
{
    EXTI_IRQHandling(0);
}

void EXTI1_IRQHandler(void)
{
    EXTI_IRQHandling(1);
}

void EXTI2_IRQHandler(void)
{
    EXTI_IRQHandling(2);
}

void EXTI3_IRQHandler(void)
{
    EXTI_IRQHandling(3);
}

void EXTI4_IRQHandler(void)
{
    EXTI_IRQHandling(4);
}

void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetPendingBit(5)) {
        EXTI_IRQHandling(5);
    }
    if(EXTI_GetPendingBit(6)) {
        EXTI_IRQHandling(6);
    }
    if(EXTI_GetPendingBit(7)) {
        EXTI_IRQHandling(7);
    }
    if(EXTI_GetPendingBit(8)) {
        EXTI_IRQHandling(8);
    }
    if(EXTI_GetPendingBit(9)) {
        EXTI_IRQHandling(9);
    }
}

void EXTI15_10_IRQHandler(void)
{
    if(EXTI_GetPendingBit(10)) {
        EXTI_IRQHandling(10);
    }
    if(EXTI_GetPendingBit(11)) {
        EXTI_IRQHandling(11);
    }
    if(EXTI_GetPendingBit(12)) {
        EXTI_IRQHandling(12);
    }
    if(EXTI_GetPendingBit(13)) {
        EXTI_IRQHandling(13);
    }
    if(EXTI_GetPendingBit(14)) {
        EXTI_IRQHandling(14);
    }
    if(EXTI_GetPendingBit(15)) {
        EXTI_IRQHandling(15);
    }
}

/**
 * @brief SPI1/2/3 global interrupt stub
 *
 * spi_driver.c currently only supports blocking SPI_SendData()/SPI_ReceiveData();
 * there is no SPI_IRQHandling() or callback registration yet. If SPI interrupt
 * mode is enabled in irq_config.c before that logic exists, trapping here makes
 * the gap visible immediately instead of an unexplained hang.
 *
 * Replace the while(1) with a call into the SPI driver's IRQ handling function
 * once it exists (mirror the EXTI_IRQHandling()/EXTI_RegisterCallback() pattern).
 */
/*
 * SPI ISR: chuyển tiếp vào SPI_IRQHandling() của driver, truyền handle tương ứng.
 * hspi1 định nghĩa ở main.c (extern trong spi_driver.h). Thêm hspi2/hspi3 tương tự
 * khi dùng đến các instance đó.
 */
void SPI1_IRQHandler(void)
{
    SPI_IRQHandling(&hspi1);
}

void SPI2_IRQHandler(void)
{
    SPI_IRQHandling(&hspi2);
}

void SPI3_IRQHandler(void)
{
    while (1) {
        /* SPI3 chưa có handle được khai báo. Khai báo hspi3 rồi gọi SPI_IRQHandling(&hspi3). */
    }
}
