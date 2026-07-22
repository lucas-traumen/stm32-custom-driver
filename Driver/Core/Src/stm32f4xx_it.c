#include "stm32f4xx_it.h"
#include "exti.h"

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
