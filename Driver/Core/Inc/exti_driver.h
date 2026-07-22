#ifndef _EXTI_H_
#define _EXTI_H_

#include "system.h"

typedef enum {
    EXTI_TRIGGER_RISING = 0,
    EXTI_TRIGGER_FALLING,
    EXTI_TRIGGER_RISING_FALLING
} EXTI_Trigger_t;

typedef enum {
    EXTI_MODE_INTERRUPT = 0,
    EXTI_MODE_EVENT
} EXTI_Mode_t;

typedef struct {
    uint8_t EXTI_Line;
    EXTI_Trigger_t EXTI_Trigger;
    EXTI_Mode_t EXTI_Mode;
    uint8_t EXTI_LineCmd;
} EXTI_Config_t;

typedef struct {
    EXTI_Config_t EXTI_Config;
} EXTI_Handle_t;

void EXTI_Init(EXTI_Handle_t *pEXTIHandle);
void EXTI_DeInit(void);
void EXTI_IRQHandling(uint8_t EXTI_Line);
void EXTI_ClearPendingBit(uint8_t EXTI_Line);
uint8_t EXTI_GetPendingBit(uint8_t EXTI_Line);

__weak void EXTI0_Callback(void);
__weak void EXTI1_Callback(void);
__weak void EXTI2_Callback(void);
__weak void EXTI3_Callback(void);
__weak void EXTI4_Callback(void);
__weak void EXTI9_5_Callback(uint8_t pin);
__weak void EXTI15_10_Callback(uint8_t pin);

#endif
