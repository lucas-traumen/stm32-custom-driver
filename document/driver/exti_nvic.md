# EXTI & NVIC — External Interrupt / Nested Vectored Interrupt Controller

## Tổng quan

STM32F407 có hai lớp xử lý interrupt:

- **EXTI** (External Interrupt/Event Controller) — ngoại vi bên ngoài core, quản lý edge detection từ GPIO pin, RTC alarm, watchdog, v.v. Tạo request đến NVIC khi edge xảy ra.
- **NVIC** (Nested Vectored Interrupt Controller) — khối trong core Cortex-M4F, quản lý enable/disable/pending/priority của tất cả IRQ.

```
GPIO Pin ──► EXTI (edge detect + IMR/EMR) ──► NVIC (enable + priority) ──► CPU ISR
```

**Cấu trúc code project:**

| File | Vai trò |
|------|---------|
| `gpio_driver.c` (`GPIO_Init`) | Cấu hình SYSCFG EXTICR (map GPIO port → EXTI line) + EXTI edge trigger (RTSR/FTSR) + IMR khi mode = `GPIO_MODE_IT_FT/RT/RFT` |
| `exti_driver.c` | Chỉ còn IRQ-side API: dispatch (`EXTI_IRQHandling`), pending flag, bảng con trỏ callback + `EXTI_RegisterCallback()`. Không còn hàm init — cấu hình line (trigger/IMR/EXTICR) nằm hoàn toàn trong `GPIO_Init()` |
| `nvic_driver.c` | API điều khiển NVIC (DRV_NVIC_*), tránh xung đột tên với CMSIS |
| `irq_config.c` (`IRQ_Init`) | Tập trung enable + set priority cho mọi IRQ trong project |
| `stm32f4xx_it.c` | ISR handlers thật — nhận interrupt từ vector table, gọi `EXTI_IRQHandling()`. File `it.c` cũ đã bị xóa (100% dead code, tên hàm không khớp API hiện tại). |

---

## NVIC (Nested Vectored Interrupt Controller)

### Registers

| Register | Offset | Mô tả |
|----------|--------|-------|
| `NVIC->ISER[0..7]` | 0x000 | Interrupt Set-Enable Register (ghi 1 để enable) |
| `NVIC->ICER[0..7]` | 0x080 | Interrupt Clear-Enable Register (ghi 1 để disable) |
| `NVIC->ISPR[0..7]` | 0x100 | Interrupt Set-Pending Register (ghi 1 để set pending) |
| `NVIC->ICPR[0..7]` | 0x180 | Interrupt Clear-Pending Register (ghi 1 để xóa pending) |
| `NVIC->IP[0..239]` | 0x300 | Interrupt Priority Register (mỗi byte = 1 IRQ, upper 4 bits dùng) |
| `SCB->AIRCR` | 0xE000ED0C | Priority Grouping (bits [10:8]) |

Mỗi thanh ghi ISER/ICER/ISPR/ICPR có 8 bản sao 32-bit (n=0..7). Mỗi bit tương ứng 1 IRQ number:
```
IRQn = 6  → ISER[0] bit 6   (6/32 = 0, 6%32 = 6)
IRQn = 40 → ISER[1] bit 8   (40/32 = 1, 40%32 = 8)
```

### API — DRV_NVIC_*

Tất cả hàm NVIC dùng prefix `DRV_NVIC_` để tránh trùng với CMSIS `core_cm4.h` (nơi định nghĩa `NVIC_EnableIRQ`, `NVIC_SetPriority` dùng macro `#define`).

```c
void   DRV_NVIC_EnableIRQ(IRQn_Type IRQn);
void   DRV_NVIC_DisableIRQ(IRQn_Type IRQn);
void   DRV_NVIC_SetPriorityGrouping(uint32_t PriorityGroup);
uint32_t DRV_NVIC_GetPriorityGrouping(void);
DRV_NVIC_PriorityLimit_t DRV_NVIC_GetPriorityLimit(void);
bool   DRV_NVIC_SetPriority(IRQn_Type IRQn, uint8_t PreemptPriority, uint8_t SubPriority);
void   DRV_NVIC_ClearPendingIRQ(IRQn_Type IRQn);
uint32_t DRV_NVIC_GetPendingIRQ(IRQn_Type IRQn);
```

Đặc điểm khác so với CMSIS:
- **Input validation**: `DRV_NVIC_SetPriority()` kiểm tra PreemptPriority/SubPriority theo grouping hiện tại, trả về `false` nếu vượt range (không im lặng truncate).
- **Guard IRQn âm**: Các hàm EnableIRQ, DisableIRQ, SetPriority, ClearPendingIRQ, GetPendingIRQ kiểm tra `(int32_t)IRQn < 0` để tránh out-of-bounds khi cast `(uint8_t)IRQn` với system exception (âm).

### Priority Grouping

4 bit priority (0-15) được chia thành preemption + subpriority tùy theo `SCB->AIRCR[10:8]`:

| PriorityGroup | AIRCR[10:8] | Preempt bits | Sub bits | PreemptMax | SubMax |
|---------------|-------------|--------------|----------|------------|--------|
| GROUP_4 (0x03) | 011 | 4 | 0 | 15 | 0 |
| GROUP_3 (0x04) | 100 | 3 | 1 | 7 | 1 |
| GROUP_2 (0x05) | 101 | 2 | 2 | 3 | 3 |
| GROUP_1 (0x06) | 110 | 1 | 3 | 1 | 7 |
| GROUP_0 (0x07) | 111 | 0 | 4 | 0 | 15 |

Ví dụ với GROUP_2 (preempt 2 bit, sub 2 bit):
```
Priority byte (NVIC->IP[n]):
| Bit 7 6 | Bit 5 4 | Bit 3 2 1 0 |
| Preempt | Sub     | (unused)    |
```
- PreemptPriority chấp nhận 0-3
- SubPriority chấp nhận 0-3

### DRV_NVIC_GetPriorityLimit()

Hàm này trả về struct `DRV_NVIC_PriorityLimit_t` chứa PreemptMax và SubMax tương ứng grouping hiện tại. Dùng để kiểm tra hoặc viết validation:

```c
DRV_NVIC_PriorityLimit_t lim = DRV_NVIC_GetPriorityLimit();
// GROUP_2 → lim.PreemptMax = 3, lim.SubMax = 3
// GROUP_4 → lim.PreemptMax = 15, lim.SubMax = 0
```

`DRV_NVIC_SetPriority()` tự động gọi GetPriorityLimit() bên trong, trả về `false` nếu vượt range.

---

## EXTI (External Interrupt/Event Controller)

### Registers

| Register | Địa chỉ | Mô tả |
|----------|---------|-------|
| `EXTI->IMR` | 0x40013C00 | Interrupt Mask Register — 23 bit, mỗi bit enable 1 EXTI line cho interrupt mode |
| `EXTI->EMR` | 0x40013C04 | Event Mask Register — enable event mode (wake from sleep, không tạo IRQ) |
| `EXTI->RTSR` | 0x40013C08 | Rising Trigger Selection Register — edge lên trigger |
| `EXTI->FTSR` | 0x40013C0C | Falling Trigger Selection Register — edge xuống trigger |
| `EXTI->SWIER` | 0x40013C10 | Software Interrupt Event Register — ghi 1 để giả lập trigger từ software |
| `EXTI->PR` | 0x40013C14 | Pending Register — đọc = flag, ghi 1 = xóa |

EXTI có 23 lines:
- **EXTI0-EXTI15**: GPIO pins (EXTI0 = PA0/PB0/PC0/... tùy SYSCFG_EXTICR)
- **EXTI16**: PVD output
- **EXTI17**: RTC Alarm
- **EXTI18**: RTC Tamper/Timestamp
- **EXTI19**: RTC Wakeup
- **EXTI20**: COMP1 (comparator)
- **EXTI21**: COMP2

### EXTI driver API (IRQ-side only)

```c
void EXTI_DeInit(void);
void EXTI_IRQHandling(uint8_t EXTI_Line);
void EXTI_ClearPendingBit(uint8_t EXTI_Line);
uint8_t EXTI_GetPendingBit(uint8_t EXTI_Line);
void EXTI_RegisterCallback(uint8_t EXTI_Line, EXTI_Callback_t callback);
```

Không còn `EXTI_Init()` / `EXTI_Config_t` / `EXTI_Handle_t`. Lý do: line 0-15 luôn gắn với một GPIO pin, và `GPIO_Init()` đã ghi vào đúng những thanh ghi (`FTSR`/`RTSR`/`IMR`/`SYSCFG_EXTICR`) mà một `EXTI_Init()` riêng cũng sẽ ghi — giữ cả hai API dễ dẫn đến 2 nơi cấu hình cùng 1 line theo thứ tự gọi khác nhau, tùy hàm nào chạy sau sẽ "thắng". Line 16-22 (PVD, RTC, comparator) không gắn GPIO nên chưa cần init helper; nếu có use case thật, nên thêm API dành riêng cho nhóm đó (ví dụ `EXTI_ConfigNonGPIOLine()`), không tái sử dụng field kiểu GPIO.

### EXTI_IRQHandling() — Function-Pointer Callback + Trap Pattern

Driver không dùng `__weak` callback theo tên cố định nữa. Thay vào đó là **bảng 16 con trỏ hàm**, mỗi phần tử mặc định trỏ vào `EXTI_DefaultCallback()` — một hàm trap (`while(1)`):

```c
typedef void (*EXTI_Callback_t)(uint8_t line);

static void EXTI_DefaultCallback(uint8_t line)
{
    (void)line;
    while (1) {
        /* Unregistered EXTI line fired. Check EXTI_Line in the debugger. */
    }
}

static EXTI_Callback_t exti_callbacks[16] = {
    EXTI_DefaultCallback, EXTI_DefaultCallback, /* ... x16 */
};

void EXTI_IRQHandling(uint8_t EXTI_Line)
{
    if(EXTI->PR & (1 << EXTI_Line)) {
        EXTI->PR |= (1 << EXTI_Line);   // ghi 1 xóa pending
        exti_callbacks[EXTI_Line](EXTI_Line);
    }
}

void EXTI_RegisterCallback(uint8_t EXTI_Line, EXTI_Callback_t callback);
```

**Vì sao đổi từ `__weak` sang con trỏ hàm:**
- `__weak` cố định theo tên (`EXTI0_Callback`, `EXTI9_5_Callback`...) buộc phải khai báo 7 signature khác nhau, và không có cách nào detect "quên implement" ngoài việc callback chạy rỗng im lặng.
- Với bảng con trỏ hàm, **giá trị mặc định chính là hàm trap**. Nếu app enable một EXTI line nhưng quên gọi `EXTI_RegisterCallback()`, ISR sẽ rơi vào `while(1)` ngay khi interrupt đó bắn ra — debugger bắt được ngay dòng nào, không cần viết `while(1)` tay trong `it.c` cho từng interrupt.
- Khi đã đăng ký callback thật, con trỏ đổi hướng khỏi trap — đây là hành vi đúng, không phải "mất tính năng debug".

**Đăng ký callback (gọi từ code khởi tạo, không phải từ ISR):**

```c
void Button_Handler(uint8_t line)
{
    GPIO_Toggle_Pin(&hled, GPIO_PIN_NO_14);
}

EXTI_RegisterCallback(0, Button_Handler);
```

Một signature `void (*)(uint8_t line)` dùng chung cho mọi EXTI line (0-15), kể cả các line từng dùng chung handler (9_5, 15_10) — `line` cho biết chính xác line nào vừa fire.

---

## SYSCFG EXTICR — Map GPIO Port → EXTI Line

Để EXTI line N trigger từ pin PA_N, PB_N, PC_N..., phải cấu hình `SYSCFG->EXTICR[n]`.

4 thanh ghi EXTICR, mỗi thanh ghi 16 bit, quản lý 4 EXTI lines:

| Register | EXTI lines | Bits layout |
|----------|------------|-------------|
| `EXTICR[0]` | EXTI0-EXTI3 | [3:0]=EXTI0, [7:4]=EXTI1, [11:8]=EXTI2, [15:12]=EXTI3 |
| `EXTICR[1]` | EXTI4-EXTI7 | [3:0]=EXTI4, [7:4]=EXTI5, [11:8]=EXTI6, [15:12]=EXTI7 |
| `EXTICR[2]` | EXTI8-EXTI11 | [3:0]=EXTI8, [7:4]=EXTI9, [11:8]=EXTI10, [15:12]=EXTI11 |
| `EXTICR[3]` | EXTI12-EXTI15 | [3:0]=EXTI12, [7:4]=EXTI13, [11:8]=EXTI14, [15:12]=EXTI15 |

Port code cho mỗi 4-bit field: A=0, B=1, C=2, D=3, E=4, ..., I=8.

Ví dụ: PA0 → EXTI0 (port code 0, field EXTI0 tại EXTICR[0][3:0]):
```c
SYSCFG->EXTICR[0] &= ~(0xF << 0);  // clear field
SYSCFG->EXTICR[0] |= (0 << 0);     // port A = 0
```

`GPIO_Init()` dùng read-modify-write cho field này (clear 4-bit field trước, rồi OR giá trị port code), nên cấu hình 2 EXTI lines khác nhau trong cùng EXTICR (ví dụ PA0 rồi PB1) không bị mất:
```c
SYSCFG->EXTICR[temp1] &= ~(0xF << (temp2 * 4));
SYSCFG->EXTICR[temp1] |= (portcode << (temp2 * 4));
```

---

## Cấu hình EXTI cho GPIO line (0-15)

Chỉ có **một cách**: qua `GPIO_Init()`. Khi `GPIO_PinMode = GPIO_MODE_IT_FT/RT/RFT`, `GPIO_Init()` tự động:
1. Cấu hình SYSCFG EXTICR (map port → line)
2. Cấu hình RTSR/FTSR tùy mode
3. Enable IMR cho line đó

```c
GPIO_Handle_t hbutton;
hbutton.pGPIOx = GPIOA;
hbutton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
hbutton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;  // falling edge
hbutton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
GPIO_Init(&hbutton);  // tự set EXTICR + FTSR + IMR
```

Sau đó chỉ cần cấu hình NVIC (enable IRQ), gọi `EXTI_RegisterCallback()`, và viết ISR mỏng trong `stm32f4xx_it.c` gọi `EXTI_IRQHandling()`.

**Không có `EXTI_Init()` cho line 0-15** — đã bị bỏ hẳn vì nó ghi vào cùng thanh ghi (FTSR/RTSR/IMR) mà `GPIO_Init()` cũng ghi, dẫn đến xung đột thật tùy thứ tự gọi hàm (từng xảy ra trong project: `GPIO_Init` đặt falling-edge, code init EXTI cũ đặt rising-edge cho cùng line 0 — cấu hình cuối cùng phụ thuộc ai gọi sau). Line 16-22 (không gắn GPIO) chưa có API riêng, thêm khi có use case thật.

---

## Interrupt Flow (từ pin đến callback)

```
GPIO PA0 falling edge
    │
    ▼
EXTI detect edge → EXTI->FTSR[0]=1 + EXTI->IMR[0]=1
    │
    ▼
EXTI set pending: EXTI->PR[0] = 1
    │
    ▼
NVIC pending: NVIC->ISPR[0] bit 6 = 1 (EXTI0_IRQn = 6)
    │ (nếu NVIC->ISER[0] bit 6 = 1 và priority đủ cao)
    ▼
CPU vector table → EXTI0_IRQHandler (trong stm32f4xx_it.c)
    │
    ▼
EXTI_IRQHandling(0) → đọc PR bit 0, ghi 1 xóa, gọi EXTI0_Callback()
    │
    ▼
Callback (user code trong main.c hoặc file ứng dụng)
```

---

## ISR Handlers (stm32f4xx_it.c)

Các EXTI handlers đã được implement đầy đủ:

```c
// EXTI line riêng lẻ — gọi thẳng EXTI_IRQHandling với line tương ứng
void EXTI0_IRQHandler(void)  { EXTI_IRQHandling(0); }
void EXTI1_IRQHandler(void)  { EXTI_IRQHandling(1); }
void EXTI2_IRQHandler(void)  { EXTI_IRQHandling(2); }
void EXTI3_IRQHandler(void)  { EXTI_IRQHandling(3); }
void EXTI4_IRQHandler(void)  { EXTI_IRQHandling(4); }

// EXTI5-9 chung 1 handler — kiểm tra pending từng line
void EXTI9_5_IRQHandler(void) {
    if(EXTI_GetPendingBit(5)) EXTI_IRQHandling(5);
    if(EXTI_GetPendingBit(6)) EXTI_IRQHandling(6);
    // ... 7, 8, 9
}

// EXTI10-15 chung 1 handler
void EXTI15_10_IRQHandler(void) {
    if(EXTI_GetPendingBit(10)) EXTI_IRQHandling(10);
    // ... 11, 12, 13, 14, 15
}
```

Handlers đã được khai báo trong `stm32f4xx_it.h` và vector table (startup file).

---

## IRQ_Init() — Centralized NVIC Config

File `irq_config.c` tập trung tất cả NVIC enable + priority setup. `main()` chỉ gọi `IRQ_Init()` một lần:

```c
void IRQ_Init(void)
{
    /* Grouping: 4 bits preempt, 0 bits sub */
    DRV_NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_4);

    /* ===== EXTI ===== */
    // DRV_NVIC_SetPriority(EXTI0_IRQn, 3, 0);
    // DRV_NVIC_EnableIRQ(EXTI0_IRQn);
    // DRV_NVIC_SetPriority(EXTI9_5_IRQn, 3, 0);
    // DRV_NVIC_EnableIRQ(EXTI9_5_IRQn);

    /* ===== SPI, I2C, USART, Timer, DMA ===== */
    // ... uncomment khi cần
}
```

**Priority allocation convention:**

| Range | Dành cho |
|-------|----------|
| 0-2 | Hard real-time / safety-critical |
| 3-5 | High-priority EXTI, ADC, DMA tight deadline |
| 6-10 | Normal peripherals (SPI, I2C, USART) |
| 11-14 | Low priority (debug UART, background DMA) |
| **15** | **SysTick** (chỉ increment uwTick) |

**Tại sao SysTick priority nên là 15:** Nếu code trong ISR khác gọi `HAL_Delay()` (polling `uwTick`), và SysTick priority thấp hơn ISR đó, thì `uwTick` không bao giờ tăng → delay treo vĩnh viễn (priority inversion). Đặt SysTick priority **cao nhất về số** (15 = thấp nhất về độ ưu tiên) — tức là bất kỳ ISR nào cũng có thể preempt SysTick, và `uwTick` vẫn tăng đều.

---

## Ví dụ hoàn chỉnh: PA0 button interrupt toggle LED PD14

```c
// 1. GPIO config (falling edge, pull-up)
GPIO_Handle_t hbutton;
hbutton.pGPIOx = GPIOA;
hbutton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
hbutton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
hbutton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
GPIO_Init(&hbutton);

// 2. NVIC config
DRV_NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_4);
DRV_NVIC_SetPriority(EXTI0_IRQn, 3, 0);   // trả về true/false
DRV_NVIC_EnableIRQ(EXTI0_IRQn);

// 3. ISR — đã có trong stm32f4xx_it.c, gọi EXTI_IRQHandling(0)

// 4. Callback (trong file ứng dụng) + đăng ký
void Button_Handler(uint8_t line)
{
    // Debounce đơn giản
    for(volatile uint32_t i = 0; i < 50000; i++);
    if(GPIO_Read_Pin(&hbutton, GPIO_PIN_NO_0) == 0) {
        GPIO_Toggle_Pin(&hled, GPIO_PIN_NO_14);
    }
}

// 5. main()
int main(void)
{
    SystemClock_Config();
    MX_GPIO_Init();      // cấu hình tất cả GPIO (button + LED)
    IRQ_Init();          // enable NVIC cho EXTI0
    EXTI_RegisterCallback(0, Button_Handler);  // BẮT BUỘC, thiếu bước này line 0 sẽ trap

    while(1) {
        // main loop — ISR xử lý button
    }
}
```

---

## IRQn mapping (EXTI lines trên STM32F407)

| EXTI Line | IRQn enum | IRQn number | Vector table index | Ghi chú |
|-----------|-----------|-------------|-------------------|---------|
| 0 | `EXTI0_IRQn` | 6 | 16+6 | PA0..PI0 |
| 1 | `EXTI1_IRQn` | 7 | 16+7 | PA1..PI1 |
| 2 | `EXTI2_IRQn` | 8 | 16+8 | PA2..PI2 |
| 3 | `EXTI3_IRQn` | 9 | 16+9 | PA3..PI3 |
| 4 | `EXTI4_IRQn` | 10 | 16+10 | PA4..PI4 |
| 5-9 | `EXTI9_5_IRQn` | 23 | 16+23 | Chung 1 handler, phân biệt bằng pending |
| 10-15 | `EXTI15_10_IRQn` | 40 | 16+40 | Chung 1 handler |

Tổng cộng STM32F407 có 98 vector ngắt (IRQn từ -14 đến 81). System exception chiếm -14 đến -1, device IRQ từ 0 đến 81.

---

## Debug tips

| Vấn đề | Nguyên nhân | Cách kiểm tra |
|--------|-------------|---------------|
| Interrupt không trigger | EXTI->IMR chưa set | `EXTI->IMR & (1 << line)` |
| | SYSCFG EXTICR sai port | `SYSCFG->EXTICR[n]` — đọc 4-bit field |
| | NVIC chưa enable | `NVIC->ISER[IRQn/32] & (1 << (IRQn%32))` |
| Handler không chạy dù pending | NVIC priority cao hơn ISR đang chạy | Kiểm tra preempt priority |
| Interrupt loop vô hạn | Quên xóa pending flag | `EXTI->PR \|= (1 << line)` trong ISR |
| Chương trình treo (while(1) im lặng) sau khi enable 1 EXTI line | Quên gọi `EXTI_RegisterCallback()` cho line đó | Đây là trap có chủ đích của `EXTI_DefaultCallback()`. Xem giá trị `EXTI_Line`/PC trong debugger để biết line nào chưa đăng ký, rồi gọi `EXTI_RegisterCallback()` cho line đó trước khi enable NVIC |
| Priority không đúng | Grouping chưa set hoặc set sai | `SCB->AIRCR & 0x700` |
| DRV_NVIC_SetPriority trả về false | PreemptPriority/SubPriority vượt range cho grouping hiện tại | Gọi `DRV_NVIC_GetPriorityLimit()` trước để tra cứu |

## Ghi chép quan trọng

- **System exception priority cố định**: Reset = -3 (cao nhất), NMI = -2, HardFault = -1. Không thể thay đổi.
- **EXTI pending**: ghi **1** để xóa (`EXTI->PR |= (1 << line)`), không phải ghi 0.
- **NVIC->IP priority**: lưu ở upper 4 bits, lower 4 bits RAZ/WI. Phải shift: `NVIC->IP[n] = priority << 4`.
- **IMR vs EMR**: IMR cho phép IRQ đến NVIC; EMR cho phép event (wake from sleep, không tạo IRQ). Có thể bật cả 2 cùng lúc.
- **DRV_NVIC_SetPriority**: trả về `bool` — luôn kiểm tra return value khi debug priority issue.
- **SYSCFG clock**: phải bật clock cho SYSCFG trước khi ghi EXTICR (`SYSCFG_PCLK_EN()`). `GPIO_Init()` đã làm việc này.
- **Thứ tự bắt buộc**: `EXTI_RegisterCallback()` phải gọi **trước** khi `DRV_NVIC_EnableIRQ()` cho line đó — nếu enable trước, một interrupt bắn ra giữa lúc đó sẽ rơi vào trap dù bạn sắp đăng ký callback.
- **`it.c` đã bị xóa**: là code chết (toàn bộ comment, tên hàm không khớp API hiện tại). ISR thật nằm ở `stm32f4xx_it.c/h`, không có `it.h` riêng.
