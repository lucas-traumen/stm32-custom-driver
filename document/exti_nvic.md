# EXTI & NVIC (External Interrupt & Nested Vectored Interrupt Controller)

## Tổng quan

Module này xử lý interrupt cho STM32F407:

- **NVIC** (Nested Vectored Interrupt Controller): Bộ điều khiển IRQ trên core ARM Cortex-M4. Quản lý enable/disable IRQ, set priority, xử lý nested interrupt.
- **EXTI** (External Interrupt): 16 external interrupt lines (EXTI0-EXTI15) và các event chậm (EXTI16-EXTI22 từ RTC, watchdog...).

**Lưu ý cấu trúc code:**
- Phần cấu hình EXTI line (edge trigger, SYSCFG mapping, IMR) nằm trong `GPIO_Init()` khi mode là `IT_FT/RT/RFT`.
- NVIC chỉ bật/tắt IRQ, không cấu hình EXTI logic.
- `irq_config.c` + `irq_config.h` tập trung tất cả interrupt enable/priority setup một nơi (pattern centralized).

---

## NVIC thanh ghi (bộ ARMv7-M)

NVIC là bộ điều khiển tích hợp trong core, không phải ngoài core. Registers nằm ở memory map:
- `NVIC->ISER[8]` — Interrupt Set-Enable
- `NVIC->ICER[8]` — Interrupt Clear-Enable
- `NVIC->ISPR[8]` — Interrupt Set-Pending
- `NVIC->ICPR[8]` — Interrupt Clear-Pending
- `NVIC->IP[240]` — Interrupt Priority
- `SCB->AIRCR` — Application Interrupt and Reset Control (priority grouping)

### `NVIC->ISER[n]` (Set-Enable Register) — Bật IRQ

8 thanh ghi 32-bit (n=0..7), mỗi bit ứng với 1 IRQ số (0-255 cho Cortex-M4).

Ghi 1 vào bit → enable IRQ tương ứng, CPU sẽ xử lý nó khi flag pending set.

Ví dụ: enable EXTI0_IRQn (IRQn=6):
```c
NVIC->ISER[0] |= (1 << 6);  // ISER[6/32] = ISER[0], bit (6%32) = bit 6
```

### `NVIC->ICER[n]` (Clear-Enable Register) — Tắt IRQ

Tương tự ISER nhưng ghi 1 = disable IRQ.

### `NVIC->ISPR[n]` / `NVIC->ICPR[n]` (Set/Clear-Pending)

Đọc/ghi pending flag của IRQ. Ghi 1 → set pending (giả lập IRQ trigger).

Ví dụ: clear pending của EXTI0 (IRQn=6):
```c
NVIC->ICPR[0] |= (1 << 6);
```

Đọc pending:
```c
if(NVIC->ISPR[0] & (1 << 6)) { /* EXTI0 pending */ }
```

### `NVIC->IP[n]` (Interrupt Priority) — Set priority

240 byte, mỗi byte là priority của 1 IRQ. Cortex-M4 implement 4 bit ưu tiên (thấp hơn so với CPU khác).

**Cấu trúc byte priority:**
```
| Bit 7 6 5 4 | Bit 3 2 1 0 |
|  Priority   | (unused)    |
```

Chỉ dùng bits [7:4], bits [3:0] bỏ qua. Priority = 0-15 (0 cao nhất, 15 thấp nhất).

Nhưng cách thông thường là dùng **priority grouping** để chia bits thành preempt + sub-priority.

### `SCB->AIRCR` (Application Interrupt and Reset Control) — Priority Grouping

Bits [10:8] quyết định cách chia 4-bit priority thành **preempt priority** + **sub-priority**.

| AIRCR[10:8] | Preempt bits | Sub-priority bits | Ý nghĩa |
|-------------|--------------|-------------------|---------|
| 011 (3) | 4 | 0 | Chỉ preempt, không sub |
| 100 (4) | 3 | 1 | 3-bit preempt, 1-bit sub |
| **101 (5)** | **2** | **2** | 2-bit preempt, 2-bit sub |
| 110 (6) | 1 | 3 | 1-bit preempt, 3-bit sub |
| 111 (7) | 0 | 4 | Chỉ sub, không preempt |

**Ý nghĩa preempt vs sub:**
- **Preempt priority** (interrupt priority thực): IRQ có preempt thấp hơn có thể ngắt ISR đang chạy có preempt cao hơn (nested interrupt).
- **Sub-priority**: Nếu 2 IRQ có cùng preempt, IRQ nào có sub thấp hơn sẽ được ưu tiên nếu cùng pending.

Project set grouping = **5** (mặc định trong `irq_config.c`): **2-bit preempt, 2-bit sub**.

Encoding 4-bit priority khi grouping=5:
```
| Bit 7 6 | Bit 5 4 | Bit 3 2 1 0 |
| Preempt | Sub     | (unused)    |
```

Ví dụ: preempt=1, sub=2:
```c
encoded = (1 << 2) | (2 << 0) = 0b0110 = 6
IP[IRQn] = 6 << 4 = 0x60
```

---

## EXTI thanh ghi (External Interrupt Controller)

EXTI là bộ điều khiển interrupt bên ngoài core (ngoài NVIC), xử lý GPIO edge trigger và RTC/watchdog events.

### `EXTI->IMR` (Interrupt Mask Register) — Enable interrupt line

16 bit (Interrupt mode), mỗi bit ứng với 1 EXTI line (0-15).

Bit N = 1 → EXTI line N có thể tạo interrupt khi condition match.

Bit N = 0 → interrupt từ line N bị khóa (nhưng event có thể vẫn generate nếu EMR=1).

### `EXTI->EMR` (Event Mask Register) — Enable event line

Tương tự IMR nhưng cho event mode (không generate IRQ, chỉ event → có thể wake from sleep).

### `EXTI->RTSR` (Rising Trigger Selection) — Enable rising edge

Bit N = 1 → trigger interrupt/event trên cạnh lên (LOW→HIGH).

### `EXTI->FTSR` (Falling Trigger Selection) — Enable falling edge

Bit N = 1 → trigger interrupt/event trên cạnh xuống (HIGH→LOW).

### `EXTI->PR` (Pending Register) — Pending & Clear flag

Đọc: bit N = 1 → EXTI line N pending (flag set khi edge detected).

Ghi: ghi 1 vào bit → xóa pending flag (phải làm trong ISR để tránh trigger lại).

### `EXTI->SWIER` (Software Interrupt Event Register) — Trigger từ software

Ghi 1 vào bit → giả lập interrupt/event từ line đó (dùng để test).

---

## SYSCFG->EXTICR — Map GPIO port → EXTI line

4 thanh ghi EXTICR[0..3] (mỗi cái 16 bit).

Mỗi pin 0-15 có 1 EXTI line cùng số (pin 0 → EXTI0, pin 1 → EXTI1...).

Nhưng EXTI0 có thể được trigger bởi **PA0, PB0, PC0...** tùy cấu hình EXTICR.

**Cấu trúc EXTICR[n]:**
```
EXTICR[0]: Pin 0-3   (line EXTI0-EXTI3)
EXTICR[1]: Pin 4-7   (line EXTI4-EXTI7)
EXTICR[2]: Pin 8-11  (line EXTI8-EXTI11)
EXTICR[3]: Pin 12-15 (line EXTI12-EXTI15)
```

Mỗi pin chiếm 4 bit: port code (0=A, 1=B, 2=C, 3=D...).

Ví dụ: PA1 → EXTI1:
```c
EXTICR[0] = (EXTICR[0] & ~(0xF << 4)) | (0 << 4);  // EXTICR[0][7:4] = port A
```

---

## Cách interrupt trigger (flow khi pin được edge)

1. Pin PA0 thay đổi từ HIGH→LOW (falling edge).
2. EXTI controller detect → set EXTI->PR[0] = 1 (pending).
3. Nếu `EXTI->FTSR[0] = 1` (falling trigger enabled) + `EXTI->IMR[0] = 1` (interrupt enabled):
   → EXTI tạo pending request tới NVIC cho EXTI0_IRQn (IRQn=6).
4. NVIC nếu `ISER[0] bit 6 = 1` (enabled) → lấy EXTI0_IRQHandler từ vector table.
5. CPU jump tới ISR (stm32f4xx_it.c: EXTI0_IRQHandler).
6. ISR phải xóa pending: `EXTI->PR[0] = 1` (ghi 1 xóa, không phải ghi 0).

---

## NVIC Priority Encoding (khi grouping = 5)

Khi set priority cho IRQ, phải encode preempt + sub thành 4-bit value rồi shift left 4 bit:

```c
// Grouping = 5: preempt=2 bit, sub=2 bit
uint8_t prioritygroup = 5;
uint8_t preempt = 1;
uint8_t sub = 2;

uint8_t sub_priority_shift = prioritygroup - 3;  // 5 - 3 = 2
uint8_t encoded = (preempt << sub_priority_shift) | (sub & (0x0F >> (4 - sub_priority_shift)));
// = (1 << 2) | (2 & (0x0F >> 2)) = 4 | 2 = 6

NVIC->IP[6] = (encoded << 4);  // = 0x60
```

Sau này thường dùng hàm `NVIC_SetPriority()` để tự động encode.

---

## Weak pattern — IRQ_Init() tập trung config

File `irq_config.c/h` định nghĩa:

```c
void IRQ_Init(void)
{
    NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_4);

    /* Enable/set priority cho các IRQ cần dùng */
    NVIC_SetPriority(EXTI0_IRQn, preempt, sub);
    NVIC_EnableIRQ(EXTI0_IRQn);

    // Khác EXTI1, EXTI2...
}
```

`main()` chỉ cần gọi `IRQ_Init()` 1 lần → toàn bộ interrupt config xong.

**Lợi ích:**
- Tất cả IRQ config tập trung 1 chỗ, dễ review/modify.
- main() sạch, chỉ gọi init.
- Ứng với pattern IRQ_Init() của bộ Learning Module từ Udemy.

---

## Ví dụ: Button interrupt PA0 (falling edge) + LED toggle PD13

### 1. GPIO config (MX_GPIO_Init in gpio_driver.c)
```c
GPIO_Handle_t hpa0;
hpa0.pGPIOx = GPIOA;
hpa0.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
hpa0.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;  // Falling edge
hpa0.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
GPIO_Init(&hpa0);  // Tự set EXTI FTSR + IMR + EXTICR
```

### 2. Interrupt config (irq_config.c)
```c
void IRQ_Init(void)
{
    NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_4);
    NVIC_SetPriority(EXTI0_IRQn, 3, 0);  // preempt=3, sub=0
    NVIC_EnableIRQ(EXTI0_IRQn);
}
```

### 3. ISR (stm32f4xx_it.c)
```c
void EXTI0_IRQHandler(void)
{
    // Xóa pending flag
    EXTI->PR |= (1 << 0);

    // Toggle LED
    GPIO_Handle_t hpd13;
    hpd13.pGPIOx = GPIOD;
    GPIO_Toggle_Pin(&hpd13, GPIO_PIN_NO_13);
}
```

### 4. main.c
```c
int main(void)
{
    SystemClock_Config();
    MX_GPIO_Init();
    MX_MCO2_Init();
    IRQ_Init();

    while(1) {
        // Chỉ chờ interrupt
    }
}
```

---

## Debug tips

| Vấn đề | Nguyên nhân | Giải pháp |
|-------|-----------|----------|
| Interrupt không trigger | EXTI->IMR bit chưa set | Kiểm tra GPIO_Init() đã gọi với mode IT_* không |
| | EXTI->RTSR/FTSR chưa set | Lại là GPIO_Init() |
| | SYSCFG->EXTICR map sai port | GPIO_Init() tự set, kiểm tra port code đúng |
| Interrupt pending mà handler không chạy | NVIC ISER chưa enable | Kiểm tra NVIC_EnableIRQ() đã gọi không |
| | IRQn số sai | Dùng enum từ stm32f407xx.h, ví dụ EXTI0_IRQn=6 |
| Interrupt chạy liên tục (loop) | Quên xóa pending trong ISR | `EXTI->PR \|= (1 << N)` trong handler |
| Nested interrupt (ISR bị ngắt) | Preempt priority của ISR cao hơn khác | Lower preempt = higher priority (thấp hơn = ưu tiên cao hơn) |
| Priority không hoạt động | Grouping chưa set | Gọi `NVIC_SetPriorityGrouping()` trước khi set priority |

---

## IRQn mapping (EXTI lines)

| EXTI Line | IRQn Name | IRQn Number | Chứa pin |
|-----------|-----------|-------------|---------|
| 0 | EXTI0_IRQn | 6 | PA0, PB0, PC0... |
| 1 | EXTI1_IRQn | 7 | PA1, PB1, PC1... |
| 2 | EXTI2_IRQn | 8 | PA2, PB2, PC2... |
| 3 | EXTI3_IRQn | 9 | PA3, PB3, PC3... |
| 4 | EXTI4_IRQn | 10 | PA4, PB4, PC4... |
| 5-9 | EXTI9_5_IRQn | 23 | PA5-PA9, PB5-PB9... (chung 1 handler) |
| 10-15 | EXTI15_10_IRQn | 40 | PA10-PA15, PB10-PB15... (chung 1 handler) |

---

## Lưu ý

- Chỉ implement EXTI0 ISR mặc định. Các line khác (EXTI1-4, EXTI9_5, EXTI15_10) cần thêm handler tương tự.
- `EXTI0_IRQCallback` là `__weak` → user override trong main.c mà không sửa driver.
- Interrupt pending phải xóa bằng ghi 1 (counter-intuitive), không phải ghi 0.
- NVIC priority thực tế dịch trái 4 bit vào byte, nên phải `NVIC->IP[n] = priority << 4`.
