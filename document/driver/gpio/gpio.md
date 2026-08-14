# GPIO Driver

## Tổng quan

GPIO driver nằm ở `Driver/Core/Inc/gpio_driver.h` và `Driver/Core/Src/gpio_driver.c`.
Module này đơn gọn: cấu hình pin (mode, speed, pull-up/down, output type, alternate function) và đọc/ghi pin.
Hỗ trợ interrupt mode cho external interrupt (EXTI).

Target hiện tại: **STM32F407VGTx / STM32F4 Discovery**.

---

## GPIO thanh ghi liên quan (nền tảng để hiểu code)

Đây là phần quan trọng: `GPIO_Init()` chỉ là các bước đọc/ghi các thanh ghi sau. Nắm được thanh ghi thì đọc code sẽ quen thuộc.

### `GPIOx->MODER` — Mode register (chọn chế độ pin)

2 bit cho mỗi pin (pin N: bits [2N+1:2N]):

| Giá trị | Ý nghĩa |
|--------|---------|
| 00 | Input |
| 01 | General Purpose Output |
| 10 | Alternate Function |
| 11 | Analog |

Interrupt mode (IT_FT, IT_RT, IT_RFT) cũng được coi là input mode (00), nhưng bước cấu hình EXTI thêm vào sau.

Ví dụ: PD13 dùng OUTPUT thì `MODER[27:26] = 01`.

### `GPIOx->OSPEEDR` — Speed register (tốc độ output)

2 bit cho mỗi pin:

| Giá trị | Tốc độ |
|--------|--------|
| 00 | Low speed (2 MHz) |
| 01 | Medium speed (25 MHz) |
| 10 | Fast speed (50 MHz) |
| 11 | High speed (100 MHz) |

Chỉ có ý nghĩa khi pin ở OUTPUT hoặc AF mode. Input pin thì không dùng field này.

### `GPIOx->PUPDR` — Pull-up/Pull-down register

2 bit cho mỗi pin:

| Giá trị | Ý nghĩa |
|--------|---------|
| 00 | No pull-up/pull-down |
| 01 | Pull-up |
| 10 | Pull-down |
| 11 | (không dùng) |

Dùng cho input pin. Output pin bỏ qua (set NO_PUPD).

### `GPIOx->OTYPER` — Output type register

1 bit cho mỗi pin:

| Giá trị | Ý nghĩa |
|--------|---------|
| 0 | Push-Pull (PP): output HIGH/LOW trực tiếp |
| 1 | Open-Drain (OD): output chỉ pull LOW, HIGH thông qua pull-up ngoài |

Open-drain thường dùng cho I2C/SMBus (cần pull-up ngoài).

### `GPIOx->AFRL` / `GPIOx->AFRH` — Alternate Function Low/High registers

Lựa chọn hàm phụ (UART, SPI, I2C, Timer...) cho mỗi pin.

- `AFRL` (Low): pin 0-7, 4 bit mỗi pin
- `AFRH` (High): pin 8-15, 4 bit mỗi pin

Ví dụ: PA9 chạy USART1_TX → cần AF7. Pin 9 thuộc AFRH, index 1 (9-8), nên `AFRH[7:4] = 0111 (AF7)`.

Số AF chính xác phải tra **datasheet Table "Alternate function mapping"** theo chip.

### `GPIOx->ODR` / `GPIOx->IDR` — Output/Input Data registers

**ODR (Output Data)**: Ghi giá trị 0/1 vào bit để output HIGH/LOW (chỉ khi pin ở OUTPUT mode).

**IDR (Input Data)**: Đọc trạng thái pin hiện tại (0 hoặc 1). Dùng cho input pin.

Ví dụ: `GPIOD->ODR |= (1 << 13)` → PD13 output HIGH.

### `GPIOx->BSRR` — Bit Set/Reset register (cách nhanh set/reset bit)

`BSRR` có 32 bit:
- **Bits [15:0]** — Set bits: ghi 1 để set bit tương ứng ở ODR.
- **Bits [31:16]** — Reset bits: ghi 1 để reset bit tương ứng ở ODR (bit N tương ứng với bit N+16).

Ưu điểm: không cần RMW (read-modify-write), nên an toàn với interrupt/DMA.

Ví dụ: 
- `GPIOD->BSRR |= (1 << 13)` → PD13 output HIGH
- `GPIOD->BSRR |= (1 << (13+16))` → PD13 output LOW

Đây là cách an toàn nhất trong ISR.

### EXTI thanh ghi (cho interrupt mode)

Khi pin ở interrupt mode (IT_FT/IT_RT/IT_RFT):

**`EXTI->FTSR`** (Falling Trigger) — Bit N = 1 → kích hoạt interrupt trên cạnh xuống (HIGH→LOW).

**`EXTI->RTSR`** (Rising Trigger) — Bit N = 1 → kích hoạt interrupt trên cạnh lên (LOW→HIGH).

**`EXTI->IMR`** (Interrupt Mask) — Bit N = 1 → cho phép interrupt line N.

**`EXTI->PR`** (Pending) — Đọc để xem interrupt nào pending, ghi 1 để xóa pending.

### SYSCFG->EXTICR — External Interrupt Config (map GPIO port → EXTI line)

4 thanh ghi EXTICR[0..3], mỗi cái 16 bit.

Mỗi pin 0-15 chỉ kích hoạt một EXTI line cùng số (pin 0 → EXTI0, pin 1 → EXTI1... pin 15 → EXTI15).

Nhưng EXTI0 có thể được kích bởi PA0, PB0, PC0... tùy theo EXTICR.

Ví dụ: `EXTICR[0] = 0xAA00` → PA1 map tới EXTI1, PA0 map tới EXTI0.

---

## Cách `GPIO_Init()` hoạt động bên trong (đọc code theo thứ tự này)

`GPIO_Init()` (`Driver/Core/Src/gpio_driver.c:72`) có 5 bước chính:

1. **Gọi `GPIO_PeriClockControl(..., ENABLE)`** — bật clock AHB1 cho port này (ví dụ GPIOD_PCLK_EN() set RCC_AHB1ENR bit 3).

2. **Cấu hình mode (MODER) và EXTI nếu cần:**
   - Nếu mode ≤ `GPIO_MODE_ANALOG` (input/output/analog): ghi MODER trực tiếp.
   - Nếu mode là `IT_FT`/`IT_RT`/`IT_RFT`: set EXTI FTSR/RTSR, cấu hình SYSCFG_EXTICR để map port, enable EXTI IMR.

3. **Cấu hình tốc độ (OSPEEDR)** — ghi speed vào OSPEEDR.

4. **Cấu hình pull (PUPDR)** — ghi pull-up/down vào PUPDR.

5. **Cấu hình output type (OTYPER)** — ghi PP/OD vào OTYPER (chỉ có ý nghĩa khi OUTPUT mode).

6. **Cấu hình alternate function (AFRL/AFRH) nếu AF mode** — tính index đúng vào AFRL hoặc AFRH.

Thứ tự bước này quan trọng vì phải set mode trước (để xác định pin đang ở chế độ nào), rồi set các field khác.

---

## Cấu trúc OOP/HAL

```c
GPIO_PinConfig_t   // Config struct - cấu hình 1 pin
GPIO_Handle_t      // Handle struct - chứa base address + config
```

### GPIO_PinConfig_t

| Field              | Ý nghĩa                        | Giá trị                                                    |
|--------------------|--------------------------------|------------------------------------------------------------|
| GPIO_PinNumber     | Số pin (0-15)                  | `GPIO_PIN_NO_0` ... `GPIO_PIN_NO_15`                       |
| GPIO_PinMode       | Chế độ pin                     | `GPIO_MODE_IN`, `OUT`, `ALTFN`, `ANALOG`, `IT_FT/RT/RFT`  |
| GPIO_PinSpeed      | Tốc độ output                  | `GPIO_SPEED_LOW`, `MEDIUM`, `FAST`, `HIGH`                 |
| GPIO_PinPuPdControl| Pull-up/Pull-down              | `GPIO_NO_PUPD`, `GPIO_PIN_PU`, `GPIO_PIN_PD`              |
| GPIO_PinOPType     | Output type                    | `GPIO_OP_TYPE_PP` (push-pull), `GPIO_OP_TYPE_OD` (open-drain) |
| GPIO_PinAltFunMode | Alternate function (AF0-AF15)  | `AF0` ... `AF15`                                           |

### GPIO_Handle_t

| Field          | Ý nghĩa                  |
|----------------|--------------------------|
| pGPIOx         | Con trỏ tới GPIO port (GPIOA, GPIOB...) |
| GPIO_PinConfig | Struct config ở trên     |

---

## Ví dụ: LED output trên PD13

```c
GPIO_Handle_t hgpiod;

// Khai báo + cấu hình
hgpiod.pGPIOx = GPIOD;
hgpiod.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
hgpiod.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
hgpiod.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
hgpiod.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
hgpiod.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;

// Init (tự bật clock)
GPIO_Init(&hgpiod);

// Output HIGH
GPIO_Write_Pin(&hgpiod, GPIO_PIN_NO_13, 1);

// Output LOW
GPIO_Write_Pin(&hgpiod, GPIO_PIN_NO_13, 0);

// Toggle
GPIO_Toggle_Pin(&hgpiod, GPIO_PIN_NO_13);
```

---

## Ví dụ: UART TX trên PA9 (Alternate Function AF7)

```c
GPIO_Handle_t hgpioa;

hgpioa.pGPIOx = GPIOA;
hgpioa.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
hgpioa.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
hgpioa.GPIO_PinConfig.GPIO_PinAltFunMode = AF7;  // USART1_TX
hgpioa.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
hgpioa.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
hgpioa.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

GPIO_Init(&hgpioa);
```

UART driver sẽ phụ trách ghi dữ liệu vào thanh ghi USART, GPIO chỉ cầu nối pin vật lý tới USART logic.

---

## Ví dụ: Interrupt input trên PA0 (falling edge)

```c
GPIO_Handle_t hgpioa;

hgpioa.pGPIOx = GPIOA;
hgpioa.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
hgpioa.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;  // Falling edge trigger
hgpioa.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;  // Pull-up
hgpioa.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;

GPIO_Init(&hgpioa);  // Tự config EXTI

// Sau đó, enable NVIC cho EXTI0_IRQn (ở irq_config.c)
NVIC_SetPriority(EXTI0_IRQn, 3, 0);
NVIC_EnableIRQ(EXTI0_IRQn);
```

ISR trong stm32f4xx_it.c sẽ xử lý EXTI0_IRQHandler().

---

## Weak default init (`MX_GPIO_Init`)

`gpio_driver.c` khai báo:

```c
__weak void MX_GPIO_Init(void);
```

Định nghĩa mặc định (ở cuối file) cấu hình PC9 làm MCO2 output:

```c
__weak void MX_GPIO_Init(void)
{
    hgpioc = (GPIO_Handle_t){0};
    hgpioc.pGPIOx = GPIOC;
    hgpioc.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    hgpioc.GPIO_PinConfig.GPIO_PinAltFunMode = AF0;
    hgpioc.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
    hgpioc.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
    hgpioc.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    hgpioc.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_Init(&hgpioc);
}
```

Mục đích: `main()` chỉ cần gọi `MX_GPIO_Init()` mà không cần biết pin nào được setup.

Nếu project khác muốn cấu hình GPIO khác, chỉ cần định nghĩa lại hàm này ở file riêng — linker ưu tiên non-weak.

`hgpioc` cũng là global chung, tương tự pattern RCC.

---

## API

| Hàm                    | Mô tả                                           |
|------------------------|--------------------------------------------------|
| `GPIO_PeriClockControl`| Bật/tắt clock cho port (được gọi tự động trong Init) |
| `GPIO_Init`            | Cấu hình pin theo handle: mode, speed, pupd, optype, altfn, interrupt |
| `GPIO_DeInit`          | Reset toàn bộ port về mặc định qua RCC reset    |
| `GPIO_Write_Pin`       | Ghi HIGH/LOW qua thanh ghi BSRR (an toàn với interrupt) |
| `GPIO_Write_Port`      | Ghi giá trị 16-bit ra toàn port qua ODR         |
| `GPIO_Read_Pin`        | Đọc 1 pin từ IDR, trả về 0 hoặc 1              |
| `GPIO_Read_Port`       | Đọc toàn port từ IDR                            |
| `GPIO_Toggle_Pin`      | XOR bit tương ứng trong ODR                      |

---

## Interrupt mode chi tiết

Khi `GPIO_PinMode` là `IT_FT`, `IT_RT`, hoặc `IT_RFT`:

1. `GPIO_Init` tự cấu hình EXTI:
   - Set FTSR (falling) hoặc RTSR (rising) hoặc cả hai.
   - Tính index EXTICR đúng, map port code vào SYSCFG_EXTICR.
   - Set EXTI->IMR để enable interrupt line.

2. Sau Init, hãy gọi NVIC để enable IRQ trong **irq_config.c**:

```c
NVIC_SetPriority(EXTI0_IRQn, preempt, sub);
NVIC_EnableIRQ(EXTI0_IRQn);
```

3. ISR (trong stm32f4xx_it.c):

```c
void EXTI0_IRQHandler(void)
{
    // Xóa pending flag (thường do EXTI->PR |= 1 hoặc bằng cách khác)
    if(EXTI->PR & (1 << 0))
    {
        EXTI->PR |= (1 << 0);  // Xóa pending
        // Xử lý sự kiện
    }
}
```

---

## Ví dụ complete: Button interrupt trên PA0, LED toggle trên PD13

```c
// IRQ config (irq_config.c)
void IRQ_Init(void)
{
    NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_4);
    NVIC_SetPriority(EXTI0_IRQn, 3, 0);
    NVIC_EnableIRQ(EXTI0_IRQn);
}

// GPIO init (override MX_GPIO_Init)
void MX_GPIO_Init(void)
{
    // Button PA0 interrupt
    GPIO_Handle_t hpa0;
    hpa0.pGPIOx = GPIOA;
    hpa0.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    hpa0.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
    hpa0.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    GPIO_Init(&hpa0);

    // LED PD13 output
    GPIO_Handle_t hpd13;
    hpd13.pGPIOx = GPIOD;
    hpd13.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    hpd13.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    hpd13.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    hpd13.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
    GPIO_Init(&hpd13);
}

// ISR (stm32f4xx_it.c)
void EXTI0_IRQHandler(void)
{
    if(EXTI->PR & (1 << 0))
    {
        EXTI->PR |= (1 << 0);
        
        // Toggle LED
        GPIO_Handle_t hpd13;
        hpd13.pGPIOx = GPIOD;
        GPIO_Toggle_Pin(&hpd13, GPIO_PIN_NO_13);
    }
}

// main.c
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

## Common mistakes & debug tips

- **Pin không output / không input:**
  - Kiểm tra clock đã bật: `RCC->AHB1ENR` bit cho port có set không?
  - Kiểm tra MODER đúng mode không (OUTPUT=01, INPUT=00)?

- **Alternate function không hoạt động:**
  - AF number sai? Tra datasheet Table "Alternate function mapping".
  - Pin có cấu hình AF mode không? MODER phải = 10.
  - AFRL/AFRH index tính đúng không? (pin 0-7 → AFRL, pin 8-15 → AFRH).

- **Interrupt không kích hoạt:**
  - EXTI IMR có set không? (EXTI->IMR bit N = 1).
  - EXTICR map port đúng không?
  - NVIC có enable IRQ không? (NVIC_EnableIRQ).
  - ISR xóa pending flag không? (EXTI->PR |= 1 << N).

- **LED trên Discovery board:**
  - **PD12** (green), **PD13** (orange), **PD14** (red), **PD15** (blue).
  - Cấu hình OUTPUT PP, speed HIGH, no-pull.

- **Thay đổi MODER giữa chương trình:**
  - Dùng RMW (read-modify-write) cẩn thận để không làm hỏng pin khác cùng port.
  - Hoặc dùng `GPIO_DeInit()` reset toàn port (quá mạnh, xóa cả pin khác).

- **Pin đã bật output mà không thấy thay đổi:**
  - Kiểm tra ODR/BSRR có ghi đúng giá trị không?
  - LED có bị đảo chiều (cathode ở HIGH)? Thử viết 0 thay vì 1.
  - Oscilloscope/multimeter đo pin thực tế có thay đổi không? (phần cứng có thể bị lỗi).
