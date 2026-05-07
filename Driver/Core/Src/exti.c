#include "exti.h"


void NVIC_ICSR(IRQn_Type IRQnumber, uint8_t EnorDi) // 0-255 
{
    uint8_t temp1=(uint8_t)IRQnumber/32;
    uint8_t temp2=(uint8_t)IRQnumber%32;
    if(EnorDi == ENABLE)
    {
        NVIC->ISER[temp1] |=(1<<temp2);
    }else{
         NVIC->ICER[temp1] |=(1<<temp2);
    }
}
void Driver_NVIC_SetPriorityGrouping()
{
    uint32_t val = 0;
    val = SCB->AIRCR; 
    val &= ~((0xFFFF0000) | (7 << 8)); 
    val |= (0x5FA << 16) | (5 << 8);
    
    SCB->AIRCR = val;
}
static uint8_t  Driver_NVIC_GetPriorityGrouping()
{
    // Đọc bit [10:8] của thanh ghi AIRCR
    // 0x700 là mặt nạ lấy 3 bit đó (Binary: 111 0000 0000)
    // Dịch phải 8 để lấy giá trị thực (3, 4, 5, 6, 7)
    return ((SCB->AIRCR & 0x700) >> 8);
}
static void SetPriority(IRQn_Type IRQn, uint8_t encoded_priority)
{
    NVIC->IP[(uint8_t)IRQn] =(encoded_priority<<4);
}
void  Driver_NVIC_SetPriority(IRQn_Type IRQn, uint8_t PreemptPriority, uint8_t SubPriority)
{
    uint8_t prioritygroup = 0;
    uint8_t encoded_priority = 0;
    uint8_t sub_priority_shift = 0;

    prioritygroup =  Driver_NVIC_GetPriorityGrouping();

    // 2. Tính toán số bit cần dịch dựa trên Group
    // Công thức thực nghiệm cho STM32F4 (4 bit priority):
    // Group 3 (4 Pre, 0 Sub) -> Shift = 0
    // Group 4 (3 Pre, 1 Sub) -> Shift = 1
    // Group 5 (2 Pre, 2 Sub) -> Shift = 2
    // Group 6 (1 Pre, 3 Sub) -> Shift = 3
    // Group 7 (0 Pre, 4 Sub) -> Shift = 4
    
    // => Công thức: Shift = Group - 3
    sub_priority_shift = prioritygroup - 3;

    // 3. Gộp 2 số lại thành 1 số (Encoded)
    // Nguyên lý: Đẩy Preempt sang trái, nhét Sub vào bên phải
    encoded_priority = (PreemptPriority << sub_priority_shift) | (SubPriority & (0x0F >> (4 - sub_priority_shift)));
    SetPriority(IRQn, encoded_priority);
}
void EXTI0_IRQHandling()
{
    if((EXTI->PR>>GPIO_PIN_NO_0)&1)
    {
        EXTI->PR |=(1<<GPIO_PIN_NO_0);
       
        EXTI0_IRQCallback(GPIO_PIN_NO_0);
         
    }
}
__weak void EXTI0_IRQCallback(uint8_t GPIO_PinNumber)
{
    if(GPIO_PinNumber == GPIO_PIN_NO_0)
    {
        
    }
}


