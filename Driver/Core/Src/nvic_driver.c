//#include "nvic.h"
//
//void NVIC_EnableIRQ(IRQn_Type IRQn)
//{
//    uint8_t temp1 = (uint8_t)IRQn / 32;
//    uint8_t temp2 = (uint8_t)IRQn % 32;
//    NVIC->ISER[temp1] |= (1 << temp2);
//}
//
//void NVIC_DisableIRQ(IRQn_Type IRQn)
//{
//    uint8_t temp1 = (uint8_t)IRQn / 32;
//    uint8_t temp2 = (uint8_t)IRQn % 32;
//    NVIC->ICER[temp1] |= (1 << temp2);
//}
//
//void NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
//{
//    uint32_t val = 0;
//    val = SCB->AIRCR;
//    val &= ~((0xFFFF0000) | (7 << 8));
//    val |= (0x5FA << 16) | (PriorityGroup << 8);
//    SCB->AIRCR = val;
//}
//
//uint32_t NVIC_GetPriorityGrouping(void)
//{
//    return ((SCB->AIRCR & 0x700) >> 8);
//}
//
//static void NVIC_SetPriority_Internal(IRQn_Type IRQn, uint8_t encoded_priority)
//{
//    NVIC->IP[(uint8_t)IRQn] = (encoded_priority << 4);
//}
//
//void NVIC_SetPriority(IRQn_Type IRQn, uint8_t PreemptPriority, uint8_t SubPriority)
//{
//    uint8_t prioritygroup = 0;
//    uint8_t encoded_priority = 0;
//    uint8_t sub_priority_shift = 0;
//
//    prioritygroup = NVIC_GetPriorityGrouping();
//
//    sub_priority_shift = prioritygroup - 3;
//
//    encoded_priority = (PreemptPriority << sub_priority_shift) | (SubPriority & (0x0F >> (4 - sub_priority_shift)));
//    NVIC_SetPriority_Internal(IRQn, encoded_priority);
//}
//
//void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
//{
//    uint8_t temp1 = (uint8_t)IRQn / 32;
//    uint8_t temp2 = (uint8_t)IRQn % 32;
//    NVIC->ICPR[temp1] = (1 << temp2);
//}
//
//uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
//{
//    uint8_t temp1 = (uint8_t)IRQn / 32;
//    uint8_t temp2 = (uint8_t)IRQn % 32;
//    return ((NVIC->ISPR[temp1] >> temp2) & 1);
//}
