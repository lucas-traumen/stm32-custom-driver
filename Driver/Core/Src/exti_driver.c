#include "exti_driver.h"

void EXTI_Init(EXTI_Handle_t *pEXTIHandle)
{
    uint8_t line = pEXTIHandle->EXTI_Config.EXTI_Line;

    if(pEXTIHandle->EXTI_Config.EXTI_Mode == EXTI_MODE_INTERRUPT) {
        EXTI->IMR |= (1 << line);
        EXTI->EMR &= ~(1 << line);
    } else {
        EXTI->EMR |= (1 << line);
        EXTI->IMR &= ~(1 << line);
    }

    if(pEXTIHandle->EXTI_Config.EXTI_Trigger == EXTI_TRIGGER_RISING) {
        EXTI->RTSR |= (1 << line);
        EXTI->FTSR &= ~(1 << line);
    } else if(pEXTIHandle->EXTI_Config.EXTI_Trigger == EXTI_TRIGGER_FALLING) {
        EXTI->FTSR |= (1 << line);
        EXTI->RTSR &= ~(1 << line);
    } else if(pEXTIHandle->EXTI_Config.EXTI_Trigger == EXTI_TRIGGER_RISING_FALLING) {
        EXTI->RTSR |= (1 << line);
        EXTI->FTSR |= (1 << line);
    }

    if(pEXTIHandle->EXTI_Config.EXTI_LineCmd == ENABLE) {
        EXTI->IMR |= (1 << line);
    } else {
        EXTI->IMR &= ~(1 << line);
    }
}

void EXTI_DeInit(void)
{
    EXTI->IMR = 0x00000000;
    EXTI->EMR = 0x00000000;
    EXTI->RTSR = 0x00000000;
    EXTI->FTSR = 0x00000000;
    EXTI->PR = 0xFFFFFFFF;
}

void EXTI_IRQHandling(uint8_t EXTI_Line)
{
    if(EXTI->PR & (1 << EXTI_Line)) {
        EXTI->PR |= (1 << EXTI_Line);

        switch(EXTI_Line) {
            case 0:
                EXTI0_Callback();
                break;
            case 1:
                EXTI1_Callback();
                break;
            case 2:
                EXTI2_Callback();
                break;
            case 3:
                EXTI3_Callback();
                break;
            case 4:
                EXTI4_Callback();
                break;
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                EXTI9_5_Callback(EXTI_Line);
                break;
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
                EXTI15_10_Callback(EXTI_Line);
                break;
        }
    }
}

void EXTI_ClearPendingBit(uint8_t EXTI_Line)
{
    EXTI->PR |= (1 << EXTI_Line);
}

uint8_t EXTI_GetPendingBit(uint8_t EXTI_Line)
{
    return ((EXTI->PR >> EXTI_Line) & 1);
}

__weak void EXTI0_Callback(void)
{
}

__weak void EXTI1_Callback(void)
{
}

__weak void EXTI2_Callback(void)
{
}

__weak void EXTI3_Callback(void)
{
}

__weak void EXTI4_Callback(void)
{
}

__weak void EXTI9_5_Callback(uint8_t pin)
{
}

__weak void EXTI15_10_Callback(uint8_t pin)
{
}
