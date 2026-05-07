#ifndef _EXTI_H_
#define _EXTI_H_

#include "system.h"
#include "gpio.h"



void NVIC_ICSR(IRQn_Type IRQnumber, uint8_t EnorDi);
void Driver_NVIC_SetPriorityGrouping(void);
void  Driver_NVIC_SetPriority(IRQn_Type IRQn, uint8_t PreemptPriority, uint8_t SubPriority);
void EXTI0_IRQHandling(void);
__weak void EXTI0_IRQCallback(uint8_t GPIO_PinNumber);

#endif
