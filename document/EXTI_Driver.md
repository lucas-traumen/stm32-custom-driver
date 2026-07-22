# EXTI (External Interrupt) Driver

## Tổng quan

EXTI driver cung cấp các API để cấu hình external interrupt lines cho STM32F407. Driver hỗ trợ 16 EXTI lines với các tùy chọn trigger và mode.

## Kiến trúc EXTI

```
GPIO Pin ──> SYSCFG ──> EXTI Line ──> NVIC
                           │
                           ├──> Rising Trigger
                           ├──> Falling Trigger
                           ├──> Interrupt Mode
                           └──> Event Mode
```

### EXTI Lines Mapping

- EXTI0-15: GPIO pins (PA0-PA15, PB0-PB15, ...)
- EXTI16: PVD output
- EXTI17: RTC Alarm event
- EXTI18: USB OTG FS Wakeup
- EXTI19: Ethernet Wakeup
- EXTI20: USB OTG HS Wakeup
- EXTI21: RTC Tamper and TimeStamp
- EXTI22: RTC Wakeup

## Structures

### `EXTI_Config_t`
```c
typedef struct {
    uint8_t EXTI_Line;              // EXTI line number (0-15)
    EXTI_Trigger_t EXTI_Trigger;    // Trigger type
    EXTI_Mode_t EXTI_Mode;          // Interrupt hoặc Event
    uint8_t EXTI_LineCmd;           // ENABLE hoặc DISABLE
} EXTI_Config_t;
```

### `EXTI_Handle_t`
```c
typedef struct {
    EXTI_Config_t EXTI_Config;
} EXTI_Handle_t;
```

## Enumerations

### `EXTI_Trigger_t`
- `EXTI_TRIGGER_RISING`: Chỉ cạnh lên
- `EXTI_TRIGGER_FALLING`: Chỉ cạnh xuống
- `EXTI_TRIGGER_RISING_FALLING`: Cả hai cạnh

### `EXTI_Mode_t`
- `EXTI_MODE_INTERRUPT`: Interrupt mode (gọi ISR)
- `EXTI_MODE_EVENT`: Event mode (không gọi ISR, dùng cho DMA/WFE)

## API Functions

### `EXTI_Init(EXTI_Handle_t *pEXTIHandle)`
Khởi tạo EXTI line với cấu hình đã cho.

**Parameters:**
- `pEXTIHandle`: Con trỏ tới EXTI handle

**Lưu ý:** Phải cấu hình GPIO mode thành `GPIO_MODE_IT_*` và SYSCFG mapping TRƯỚC khi gọi hàm này.

### `EXTI_DeInit(void)`
Reset tất cả EXTI lines về trạng thái mặc định.

### `EXTI_IRQHandling(uint8_t EXTI_Line)`
Xử lý EXTI interrupt, clear pending bit, và gọi callback tương ứng.

**Parameters:**
- `EXTI_Line`: EXTI line number (0-15)

**Lưu ý:** Hàm này được gọi từ `EXTIx_IRQHandler()` trong `stm32f4xx_it.c`.

### `EXTI_ClearPendingBit(uint8_t EXTI_Line)`
Clear pending bit của EXTI line.

**Parameters:**
- `EXTI_Line`: EXTI line number

### `EXTI_GetPendingBit(uint8_t EXTI_Line)`
Kiểm tra pending bit của EXTI line.

**Parameters:**
- `EXTI_Line`: EXTI line number

**Returns:** 1 nếu pending, 0 nếu không

## Weak Callbacks

Driver cung cấp các callback `__weak` có thể override trong application code:

```c
__weak void EXTI0_Callback(void);
__weak void EXTI1_Callback(void);
__weak void EXTI2_Callback(void);
__weak void EXTI3_Callback(void);
__weak void EXTI4_Callback(void);
__weak void EXTI9_5_Callback(uint8_t pin);    // Lines 5-9
__weak void EXTI15_10_Callback(uint8_t pin);  // Lines 10-15
```

## Interrupt Vector Table

EXTI có các IRQ handlers trong `stm32f4xx_it.c`:

- `EXTI0_IRQHandler()` → `EXTI_IRQHandling(0)` → `EXTI0_Callback()`
- `EXTI1_IRQHandler()` → `EXTI_IRQHandling(1)` → `EXTI1_Callback()`
- `EXTI2_IRQHandler()` → `EXTI_IRQHandling(2)` → `EXTI2_Callback()`
- `EXTI3_IRQHandler()` → `EXTI_IRQHandling(3)` → `EXTI3_Callback()`
- `EXTI4_IRQHandler()` → `EXTI_IRQHandling(4)` → `EXTI4_Callback()`
- `EXTI9_5_IRQHandler()` → `EXTI_IRQHandling(5-9)` → `EXTI9_5_Callback(pin)`
- `EXTI15_10_IRQHandler()` → `EXTI_IRQHandling(10-15)` → `EXTI15_10_Callback(pin)`

## Ví dụ sử dụng

### Cấu hình EXTI0 cho nút nhấn PA0

```c
EXTI_Handle_t hexti0;
GPIO_Handle_t hgpioa_button;

void EXTI0_Button_Init(void)
{
    // 1. Cấu hình GPIO PA0 cho interrupt
    hgpioa_button.pGPIOx = GPIOA;
    hgpioa_button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    hgpioa_button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;  // Falling edge
    hgpioa_button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_Init(&hgpioa_button);

    // 2. Enable SYSCFG clock và map PA0 tới EXTI0
    SYSCFG_PCLK_EN();
    SYSCFG->EXTICR[0] &= ~(0xF << 0);  // Clear bits
    SYSCFG->EXTICR[0] |= (0 << 0);     // 0 = GPIOA

    // 3. Cấu hình EXTI line
    hexti0.EXTI_Config.EXTI_Line = 0;
    hexti0.EXTI_Config.EXTI_Trigger = EXTI_TRIGGER_FALLING;
    hexti0.EXTI_Config.EXTI_Mode = EXTI_MODE_INTERRUPT;
    hexti0.EXTI_Config.EXTI_LineCmd = ENABLE;
    EXTI_Init(&hexti0);

    // 4. Cấu hình NVIC
    NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_2);
    NVIC_SetPriority(EXTI0_IRQn, 0, 0);
    NVIC_EnableIRQ(EXTI0_IRQn);
}

// 5. Implement callback trong application code
void EXTI0_Callback(void)
{
    // Debounce delay
    for(volatile uint32_t i = 0; i < 50000; i++);
    
    if(GPIO_Read_Pin(GPIOA, GPIO_PIN_NO_0) == 0) {
        // Button pressed action
        GPIO_Toggle_Pin(&hgpiod_led, GPIO_PIN_NO_14);
    }
}
```

## SYSCFG External Interrupt Configuration

SYSCFG được dùng để map GPIO port tới EXTI line:

```c
SYSCFG->EXTICR[0]  // EXTI0-3
SYSCFG->EXTICR[1]  // EXTI4-7
SYSCFG->EXTICR[2]  // EXTI8-11
SYSCFG->EXTICR[3]  // EXTI12-15
```

**Mapping values:**
- 0x0: GPIOA
- 0x1: GPIOB
- 0x2: GPIOC
- 0x3: GPIOD
- 0x4: GPIOE
- 0x5: GPIOF
- 0x6: GPIOG
- 0x7: GPIOH
- 0x8: GPIOI

**Ví dụ:** Map PB5 tới EXTI5:
```c
SYSCFG->EXTICR[1] &= ~(0xF << 4);  // Clear EXTI5 bits
SYSCFG->EXTICR[1] |= (1 << 4);     // 1 = GPIOB
```

## Lưu ý

1. **SYSCFG clock phải được bật** trước khi cấu hình EXTICR
2. **GPIO mode phải là `GPIO_MODE_IT_*`** để trigger interrupt
3. **Pending bit phải được clear** trong ISR bằng cách ghi 1 vào PR register
4. Chỉ có một GPIO port có thể map tới một EXTI line tại một thời điểm
5. EXTI9_5 và EXTI15_10 chia sẻ chung IRQ vector, cần check pending bit để xác định line nào gây ra interrupt
