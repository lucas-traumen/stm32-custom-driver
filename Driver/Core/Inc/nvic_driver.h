#ifndef _NVIC_DRIVER_H_
#define _NVIC_DRIVER_H_

#include "stm32f407xx.h"
#include "stm32f4xx_common.h"
#include <stdbool.h>

#define NVIC_PRIORITY_GROUP_0   0x07
#define NVIC_PRIORITY_GROUP_1   0x06
#define NVIC_PRIORITY_GROUP_2   0x05
#define NVIC_PRIORITY_GROUP_3   0x04
#define NVIC_PRIORITY_GROUP_4   0x03

/**
 * @brief Valid range for preemption and subpriority given current grouping
 */
typedef struct {
    uint8_t PreemptMax;   /*!< Maximum valid preemption priority (inclusive) */
    uint8_t SubMax;       /*!< Maximum valid subpriority (inclusive) */
} DRV_NVIC_PriorityLimit_t;

void DRV_NVIC_EnableIRQ(IRQn_Type IRQn);
void DRV_NVIC_DisableIRQ(IRQn_Type IRQn);
void DRV_NVIC_SetPriorityGrouping(uint32_t PriorityGroup);
uint32_t DRV_NVIC_GetPriorityGrouping(void);
DRV_NVIC_PriorityLimit_t DRV_NVIC_GetPriorityLimit(void);
bool DRV_NVIC_SetPriority(IRQn_Type IRQn, uint8_t PreemptPriority, uint8_t SubPriority);
void DRV_NVIC_SetSystemHandlerPriority(IRQn_Type IRQn, uint8_t PreemptPriority, uint8_t SubPriority);
void DRV_NVIC_ClearPendingIRQ(IRQn_Type IRQn);
uint32_t DRV_NVIC_GetPendingIRQ(IRQn_Type IRQn);

#endif
