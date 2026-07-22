#ifndef _NVIC_DRIVER_H_
#define _NVIC_DRIVER_H_

#include "stm32f407xx.h"
#include "stm32f4xx_common.h"

#define NVIC_PRIORITY_GROUP_0   0x07
#define NVIC_PRIORITY_GROUP_1   0x06
#define NVIC_PRIORITY_GROUP_2   0x05
#define NVIC_PRIORITY_GROUP_3   0x04
#define NVIC_PRIORITY_GROUP_4   0x03

void NVIC_EnableIRQ(IRQn_Type IRQn);
void NVIC_DisableIRQ(IRQn_Type IRQn);
void NVIC_SetPriorityGrouping(uint32_t PriorityGroup);
uint32_t NVIC_GetPriorityGrouping(void);
void NVIC_SetPriority(IRQn_Type IRQn, uint8_t PreemptPriority, uint8_t SubPriority);
void NVIC_ClearPendingIRQ(IRQn_Type IRQn);
uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn);

#endif
