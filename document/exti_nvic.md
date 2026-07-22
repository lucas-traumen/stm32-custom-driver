# EXTI & NVIC Driver

## Tổng quan

Module này xử lý:
- Cấu hình NVIC (enable/disable IRQ, set priority)
- Xử lý EXTI interrupt (pending, callback)

Lưu ý: Phần cấu hình EXTI line (edge trigger, SYSCFG mapping, IMR) nằm trong `GPIO_Init()` khi mode là `IT_FT/RT/RFT`.

## API

| Hàm                             | Mô tả                                                   |
|----------------------------------|----------------------------------------------------------|
| `NVIC_ICSR`                      | Enable/Disable IRQ number trong NVIC (ISER/ICER)         |
| `Driver_NVIC_SetPriorityGrouping`| Set AIRCR priority grouping = 5 (2-bit preempt, 2-bit sub) |
| `Driver_NVIC_SetPriority`        | Set preempt + sub priority cho 1 IRQ                     |
| `EXTI0_IRQHandling`              | Clear pending bit + gọi callback cho EXTI line 0         |
| `EXTI0_IRQCallback`              | Weak callback — user override trong application          |

## Trình tự sử dụng External Interrupt

```c
// 1. Cấu hình GPIO pin ở mode interrupt
hgpio.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;  // falling trigger
GPIO_Init(&hgpio);
// GPIO_Init tự động:
//   - Set EXTI->FTSR/RTSR
//   - Map port qua SYSCFG->EXTICR
//   - Enable EXTI->IMR

// 2. Set priority grouping (1 lần khi startup)
Driver_NVIC_SetPriorityGrouping();

// 3. Set priority cho IRQ
Driver_NVIC_SetPriority(EXTI0_IRQn, preempt, sub);

// 4. Enable IRQ trong NVIC
NVIC_ICSR(EXTI0_IRQn, ENABLE);

// 5. Override callback trong application
void EXTI0_IRQCallback(uint8_t GPIO_PinNumber)
{
    // Xử lý interrupt ở đây
    GPIO_Toggle_Pin(&hgpiod, GPIO_PIN_NO_13);
}
```

## Priority Grouping

Project set grouping = 5 (theo AIRCR bits [10:8]):

| Group | Preempt bits | Sub-priority bits |
|-------|-------------|-------------------|
| 3     | 4           | 0                 |
| 4     | 3           | 1                 |
| **5** | **2**       | **2**             |
| 6     | 1           | 3                 |
| 7     | 0           | 4                 |

STM32F4 chỉ implement 4 bit priority (bit [7:4] của IP register), nên giá trị thực tế dịch trái 4 bit.

## Debug tips

- Interrupt không trigger: kiểm tra `EXTI->IMR` bit tương ứng đã set
- Interrupt trigger nhưng handler không chạy: kiểm tra NVIC ISER đã enable đúng IRQ number
- Interrupt chạy liên tục: quên clear pending bit trong `EXTI->PR`
- IRQ number cho EXTI: EXTI0=6, EXTI1=7, EXTI2=8, EXTI3=9, EXTI4=10, EXTI9_5=23, EXTI15_10=40

## Lưu ý

- `EXTI0_IRQCallback` là `__weak` → chỉ cần định nghĩa lại trong main.c, linker tự dùng bản mới.
- Hiện tại chỉ implement cho EXTI line 0. Các line khác cần thêm handler tương tự.
