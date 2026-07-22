# NVIC (Nested Vectored Interrupt Controller) Driver

## Tổng quan

NVIC driver cung cấp wrapper APIs để cấu hình interrupt controller trong STM32F407. NVIC quản lý tất cả interrupts và exceptions của Cortex-M4 core.

## Kiến trúc NVIC

```
Peripheral IRQ ──> NVIC ──> CPU
                     │
                     ├──> Priority Grouping (Preempt/Sub priority)
                     ├──> Enable/Disable IRQ
                     └──> Pending Flags
```

### Priority Levels

STM32F407 có 4-bit priority (16 levels: 0-15), được chia thành:
- **Preempt Priority**: Cho phép interrupt lồng nhau
- **Sub Priority**: Quyết định thứ tự khi nhiều interrupt cùng preempt priority xảy ra đồng thời

## Priority Grouping

NVIC cho phép phân chia 4-bit priority thành preempt và sub priority:

| Group | PRIGROUP | Preempt bits | Sub bits | Description |
|-------|----------|--------------|----------|-------------|
| 0     | 0x07     | 0            | 4        | 0 preempt, 16 sub levels |
| 1     | 0x06     | 1            | 3        | 2 preempt, 8 sub levels |
| 2     | 0x05     | 2            | 2        | 4 preempt, 4 sub levels |
| 3     | 0x04     | 3            | 1        | 8 preempt, 2 sub levels |
| 4     | 0x03     | 4            | 0        | 16 preempt, 0 sub levels |

**Lưu ý:** Số nhỏ hơn = priority cao hơn (0 là highest)

## API Functions

### `NVIC_EnableIRQ(IRQn_Type IRQn)`
Bật interrupt trong NVIC.

**Parameters:**
- `IRQn`: Interrupt number (từ enum `IRQn_Type`)

**Example:**
```c
NVIC_EnableIRQ(EXTI0_IRQn);
```

### `NVIC_DisableIRQ(IRQn_Type IRQn)`
Tắt interrupt trong NVIC.

**Parameters:**
- `IRQn`: Interrupt number

**Example:**
```c
NVIC_DisableIRQ(EXTI0_IRQn);
```

### `NVIC_SetPriorityGrouping(uint32_t PriorityGroup)`
Cấu hình priority grouping cho toàn bộ system.

**Parameters:**
- `PriorityGroup`: `NVIC_PRIORITY_GROUP_0` đến `NVIC_PRIORITY_GROUP_4`

**Example:**
```c
NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_2);  // 4 preempt, 4 sub levels
```

**Lưu ý:** Hàm này nên được gọi một lần duy nhất khi khởi tạo system.

### `NVIC_GetPriorityGrouping(void)`
Đọc priority grouping hiện tại.

**Returns:** Priority group value (3-7)

### `NVIC_SetPriority(IRQn_Type IRQn, uint8_t PreemptPriority, uint8_t SubPriority)`
Cấu hình priority cho một interrupt.

**Parameters:**
- `IRQn`: Interrupt number
- `PreemptPriority`: Preempt priority level (phạm vi phụ thuộc vào grouping)
- `SubPriority`: Sub priority level (phạm vi phụ thuộc vào grouping)

**Example:**
```c
NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_2);  // 2 preempt bits, 2 sub bits
NVIC_SetPriority(EXTI0_IRQn, 0, 0);  // Highest priority
NVIC_SetPriority(EXTI1_IRQn, 1, 0);  // Lower preempt priority
```

**Lưu ý:** Giá trị phải nằm trong phạm vi của grouping đã chọn.

### `NVIC_ClearPendingIRQ(IRQn_Type IRQn)`
Clear pending flag của interrupt.

**Parameters:**
- `IRQn`: Interrupt number

### `NVIC_GetPendingIRQ(IRQn_Type IRQn)`
Kiểm tra pending flag của interrupt.

**Parameters:**
- `IRQn`: Interrupt number

**Returns:** 1 nếu pending, 0 nếu không

## Priority Group Chi Tiết

### Group 2 (NVIC_PRIORITY_GROUP_2) - Phổ biến nhất

```
2 bits Preempt (4 levels) | 2 bits Sub (4 levels)
```

**Preempt Priority:**
- 0: Highest (có thể preempt priority 1,2,3)
- 1: Can preempt 2,3
- 2: Can preempt 3
- 3: Lowest

**Sub Priority:**
- 0-3: Chỉ quyết định thứ tự xử lý khi cùng preempt priority

**Ví dụ:**
```c
NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_2);

// EXTI0 có thể preempt EXTI1
NVIC_SetPriority(EXTI0_IRQn, 0, 0);  // Preempt=0, Sub=0
NVIC_SetPriority(EXTI1_IRQn, 1, 0);  // Preempt=1, Sub=0

// EXTI2 và EXTI3 cùng preempt priority, sub priority quyết định thứ tự
NVIC_SetPriority(EXTI2_IRQn, 2, 0);  // Preempt=2, Sub=0 (xử lý trước)
NVIC_SetPriority(EXTI3_IRQn, 2, 1);  // Preempt=2, Sub=1 (xử lý sau)
```

## Interrupt Nesting

**Preempt Priority cho phép lồng interrupt:**

```c
// Cấu hình
NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_2);
NVIC_SetPriority(TIM2_IRQn, 1, 0);    // Lower preempt
NVIC_SetPriority(EXTI0_IRQn, 0, 0);   // Higher preempt

// Runtime:
TIM2_IRQHandler() is running...
    |
    ├──> EXTI0 triggered
    |
    ├──> CPU preempts TIM2, jumps to EXTI0_IRQHandler()
    |
    └──> EXTI0_IRQHandler() completes, returns to TIM2_IRQHandler()
```

**Sub Priority KHÔNG cho phép lồng:**

```c
NVIC_SetPriority(EXTI1_IRQn, 1, 0);
NVIC_SetPriority(EXTI2_IRQn, 1, 1);

// EXTI1 đang chạy, EXTI2 trigger -> EXTI2 phải đợi (cùng preempt priority)
```

## Ví dụ sử dụng

### Cấu hình cơ bản cho EXTI

```c
void NVIC_EXTI_Config(void)
{
    // 1. Set priority grouping (gọi 1 lần duy nhất)
    NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_2);
    
    // 2. Cấu hình priority cho EXTI0
    NVIC_SetPriority(EXTI0_IRQn, 0, 0);  // Highest priority
    
    // 3. Enable interrupt
    NVIC_EnableIRQ(EXTI0_IRQn);
}
```

### Cấu hình nhiều interrupt với priority khác nhau

```c
void System_NVIC_Config(void)
{
    NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_2);
    
    // Critical interrupts - Preempt priority 0
    NVIC_SetPriority(EXTI0_IRQn, 0, 0);
    NVIC_EnableIRQ(EXTI0_IRQn);
    
    // Important interrupts - Preempt priority 1
    NVIC_SetPriority(USART1_IRQn, 1, 0);
    NVIC_SetPriority(TIM2_IRQn, 1, 1);
    NVIC_EnableIRQ(USART1_IRQn);
    NVIC_EnableIRQ(TIM2_IRQn);
    
    // Normal interrupts - Preempt priority 2
    NVIC_SetPriority(SPI1_IRQn, 2, 0);
    NVIC_EnableIRQ(SPI1_IRQn);
}
```

### Tạm thời disable/enable interrupt

```c
void Critical_Section_Example(void)
{
    // Disable interrupt trước critical section
    NVIC_DisableIRQ(TIM2_IRQn);
    
    // Critical code here
    shared_variable++;
    
    // Enable lại interrupt
    NVIC_EnableIRQ(TIM2_IRQn);
}
```

## Common IRQ Numbers (IRQn_Type)

```c
EXTI0_IRQn                = 6,
EXTI1_IRQn                = 7,
EXTI2_IRQn                = 8,
EXTI3_IRQn                = 9,
EXTI4_IRQn                = 10,
DMA1_Stream0_IRQn         = 11,
TIM1_BRK_TIM9_IRQn        = 24,
TIM1_UP_TIM10_IRQn        = 25,
TIM2_IRQn                 = 28,
USART1_IRQn               = 37,
USART2_IRQn               = 38,
SPI1_IRQn                 = 35,
SPI2_IRQn                 = 36,
EXTI9_5_IRQn              = 23,
EXTI15_10_IRQn            = 40,
```

## Lưu ý quan trọng

1. **Priority Grouping phải được set trước khi set priority:** Nếu thay đổi grouping sau khi set priority, priority values sẽ bị sai
2. **Số nhỏ hơn = priority cao hơn:** Priority 0 là highest, 15 là lowest
3. **Preempt priority cho phép lồng nhau, Sub priority không**
4. **Disable global interrupts:** Dùng `__disable_irq()` và `__enable_irq()` (CMSIS) cho critical sections rất ngắn
5. **NVIC registers are 32-bit aligned:** Driver tự động xử lý alignment

## Best Practices

1. **Chọn grouping phù hợp:**
   - Group 2 (4 preempt, 4 sub) là lựa chọn phổ biến và cân bằng
   - Group 4 (16 preempt, 0 sub) nếu cần nhiều interrupt levels và lồng sâu

2. **Sử dụng preempt priority hợp lý:**
   - Critical/Real-time: Priority 0-1
   - Important: Priority 2-3
   - Normal: Priority 4+

3. **Sub priority cho thứ tự xử lý:**
   - Khi nhiều interrupt cùng mức preempt xảy ra cùng lúc
   - UART RX (sub=0) xử lý trước UART TX (sub=1)

4. **Keep ISR short:**
   - Interrupt handler nên ngắn gọn
   - Set flag và xử lý trong main loop nếu có thể
