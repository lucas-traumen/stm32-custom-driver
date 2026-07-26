# RCC (Reset and Clock Control)

## Tổng quan

RCC driver nằm ở `Driver/Core/Inc/rcc_driver.h` và `Driver/Core/Src/rcc_driver.c`.
Module này có 2 nhóm việc chính:

1. **Peripheral clock macros**: bật/tắt/reset clock cho GPIO, SPI, I2C, USART, SYSCFG...
2. **System clock API**: chọn SYSCLK từ HSI/HSE/PLL, cấu hình prescaler AHB/APB, đọc lại tần số clock hiện tại.

Target hiện tại: **STM32F407VGTx / STM32F4 Discovery**.

```text
HSI = 16 MHz internal oscillator
HSE =  8 MHz external crystal
```

---

## Clock tree cơ bản

```text
HSI 16 MHz ─┐
HSE  8 MHz ─┼─> SYSCLK ─> AHB prescaler ─> HCLK
PLL output ─┘                              ├─> APB1 prescaler ─> PCLK1
                                           └─> APB2 prescaler ─> PCLK2
```

Giới hạn quan trọng của STM32F407:

| Clock | Max |
|-------|-----|
| SYSCLK | 168 MHz |
| HCLK/AHB | 168 MHz |
| PCLK1/APB1 | 42 MHz |
| PCLK2/APB2 | 84 MHz |

> Khi tăng SYSCLK phải set `FLASH->ACR LATENCY` trước, nếu không CPU có thể chạy sai vì Flash chưa đủ wait-state.

---

## Các thanh ghi RCC liên quan (nền tảng để hiểu code)

Đây là phần quan trọng nhất cho người mới: mọi API trong driver chỉ là các bước đọc/ghi 4 thanh ghi sau. Nắm được thanh ghi thì đọc code sẽ thấy quen thuộc ngay.

### `RCC->CR` (Control Register) — bật/tắt oscillator

| Bit | Ý nghĩa |
|-----|---------|
| `HSION` | Ghi 1 để bật HSI |
| `HSIRDY` | Đọc: 1 khi HSI đã ổn định (ready) |
| `HSEON` | Ghi 1 để bật HSE |
| `HSERDY` | Đọc: 1 khi HSE đã ổn định |
| `PLLON` | Ghi 1 để bật PLL |
| `PLLRDY` | Đọc: 1 khi PLL đã lock |

Đặc điểm quan trọng: oscillator **không bật xong ngay lập tức**. Sau khi set `xxON`, phần cứng cần vài chu kỳ để dao động ổn định rồi mới set `xxRDY = 1`. Vì vậy code driver luôn có bước "set ON rồi polling chờ RDY" — đây chính là việc của hàm `RCC_WaitCRFlag()`.

### `RCC->PLLCFGR` (PLL Configuration) — công thức nhân/chia tần số PLL

| Field | Ý nghĩa |
|-------|---------|
| `PLLSRC` | Nguồn vào PLL: 0 = HSI, 1 = HSE |
| `PLLM` | Chia trước VCO (2..63) |
| `PLLN` | Nhân VCO (50..432) |
| `PLLP` | Chia ra SYSCLK: encode 0/1/2/3 = chia 2/4/6/8 |
| `PLLQ` | Chia ra clock 48MHz cho USB/SDIO (2..15) |

Công thức tính PLLCLK (SYSCLK khi chọn nguồn PLL):

```text
VCO input = PLL_source / PLL_M      (phải nằm trong 1..2 MHz)
VCO       = VCO_input * PLL_N       (phải nằm trong 100..432 MHz)
PLLCLK    = VCO / PLL_P             (PLLP thật = (encode + 1) * 2, tức 2/4/6/8)
```

Thanh ghi này **chỉ được sửa khi PLL đang OFF** (`PLLON = 0`), đó là lý do `RCC_ClockInit()` luôn tắt PLL, chờ `PLLRDY` về 0, rồi mới gọi `RCC_PLL_Config()`.

### `RCC->CFGR` (Clock Configuration) — chọn SYSCLK và chia bus

| Field | Ý nghĩa |
|-------|---------|
| `SW` | Ghi: chọn nguồn SYSCLK muốn chuyển tới (0=HSI, 1=HSE, 2=PLL) |
| `SWS` | Đọc: nguồn SYSCLK **thực tế đang chạy** — chỉ đổi sau khi hardware switch xong |
| `HPRE` | Chia AHB → HCLK |
| `PPRE1` | Chia APB1 → PCLK1 |
| `PPRE2` | Chia APB2 → PCLK2 |
| `MCO1`, `MCO1PRE` | Chọn nguồn + chia cho ngõ ra MCO1 (PA8) |
| `MCO2`, `MCO2PRE` | Chọn nguồn + chia cho ngõ ra MCO2 (PC9) |

`SW` và `SWS` là 2 field khác nhau: ghi `SW` chỉ là "yêu cầu chuyển", còn `SWS` là "kết quả thật". Sau khi ghi `SW`, phải polling `SWS` cho tới khi khớp giá trị mong muốn — đó là bước cuối trong `RCC_ClockInit()`.

### `FLASH->ACR` (Flash Access Control) — wait-state cho bộ nhớ Flash

Field `LATENCY` quyết định CPU chờ bao nhiêu chu kỳ khi đọc lệnh từ Flash. Flash vật lý có tốc độ đọc giới hạn; nếu HCLK tăng cao mà latency thấp, CPU sẽ đọc sai lệnh → treo máy hoặc chạy sai không rõ nguyên nhân (bug rất khó debug vì không có lỗi biên dịch, chỉ chạy sai khi tần số cao).

Đây là lý do **thứ tự bắt buộc**: set latency trước, tăng SYSCLK sau — không bao giờ làm ngược.

---

## Cách `RCC_ClockInit()` hoạt động bên trong (đọc code theo thứ tự này)

`RCC_ClockInit()` (`Driver/Core/Src/rcc_driver.c`) là hàm trung tâm, thực hiện đúng 6 bước sau — mở file và đọc theo thứ tự này sẽ dễ theo dõi hơn đọc từ trên xuống:

1. **`RCC_ValidateClockConfig()`** — kiểm tra toàn bộ config trước khi đụng vào thanh ghi nào. Nếu SysClkSource là PLL, hàm này gọi tiếp `RCC_ValidatePLLConfig()` để kiểm tra PLLM/N/P/Q có nằm trong range hợp lệ của F407 không, và tính trước SYSCLK/HCLK/PCLK1/PCLK2 xem có vượt giới hạn bus (168/168/42/84 MHz) không. Sai bất kỳ điều kiện nào → trả `RCC_STATUS_INVALID_PARAM` ngay, không ghi thanh ghi.
2. **Tính flash latency và ghi `FLASH->ACR`** — tính trước HCLK mục tiêu (SYSCLK dự kiến / AHB prescaler), map qua bảng `RCC_GetFlashLatency()` (hoặc dùng giá trị override nếu `FlashLatency != 0`), rồi ghi vào `FLASH->ACR` **trước khi** chạm tới oscillator/PLL.
3. **Bật oscillator cần dùng** — gọi `RCC_HSI_Enable()` hoặc `RCC_HSE_Enable()`, mỗi hàm set bit `xxON` rồi polling `xxRDY` qua `RCC_WaitCRFlag()` với timeout.
4. **Nếu dùng PLL: tắt PLL → chờ `PLLRDY=0` → `RCC_PLL_Config()` ghi `PLLCFGR` → bật `PLLON` → chờ `PLLRDY=1`.** Đúng thứ tự này vì `PLLCFGR` chỉ ghi được khi PLL đang OFF.
5. **Ghi `RCC->CFGR`**: set `HPRE`, `PPRE1`, `PPRE2` (prescaler bus), rồi set `SW` để yêu cầu chuyển SYSCLK.
6. **Polling `SWS`** cho tới khi khớp nguồn vừa chọn, hoặc hết timeout → trả `RCC_STATUS_TIMEOUT`.

Nếu bất kỳ bước 3-6 timeout hoặc lỗi, hàm trả về ngay, không đi tiếp bước sau — người gọi (ví dụ `SystemClock_Config()`) có trách nhiệm kiểm tra return status.

### Vì sao struct config dùng "0 = auto/default"?

```c
RCC_ClkInit_t clk = {0};   // Toàn bộ field = 0
```

- `FlashLatency = 0` → driver tự tính latency từ HCLK mục tiêu (không cần biết trước bảng tra).
- `Timeout = 0` → driver tự dùng `RCC_TIMEOUT_DEFAULT`.

Người mới chỉ cần set `SysClkSource`, `PLL_Config` (nếu dùng PLL), và 3 prescaler — không cần quan tâm 2 field còn lại trừ khi muốn override để debug hoặc theo yêu cầu voltage range đặc biệt.

---

## Struct cấu hình

```c
typedef struct {
    RCC_PLLSource_t PLL_Source; // HSI hoặc HSE
    uint16_t PLL_M;
    uint16_t PLL_N;
    RCC_PLL_P_Div_t PLL_P;      // /2, /4, /6, /8
    uint16_t PLL_Q;
} RCC_PLL_Config_t;

typedef struct {
    RCC_SysClkSource_t SysClkSource;
    RCC_PLL_Config_t PLL_Config;
    RCC_AHBPrescaler_t AHB_Prescaler;
    RCC_APBPrescaler_t APB1_Prescaler;
    RCC_APBPrescaler_t APB2_Prescaler;
    RCC_FlashLatencyConfig_t FlashLatency; // 0 = auto, chỉ set khi muốn override
    uint32_t Timeout;                  // 0 = RCC_TIMEOUT_DEFAULT, chỉ set khi muốn override
} RCC_ClkInit_t;
```

---

## Ví dụ: dùng HSI mặc định 16 MHz

Sau reset STM32 chạy HSI 16 MHz, AHB/APB không chia. Có thể đọc lại bằng:

```c
uint32_t sysclk = RCC_GetSysClockFreq(); // 16000000
uint32_t hclk   = RCC_GetHCLKFreq();     // 16000000
uint32_t pclk1  = RCC_GetPCLK1Freq();    // 16000000
uint32_t pclk2  = RCC_GetPCLK2Freq();    // 16000000
```

---

## Ví dụ: HSE 8 MHz trực tiếp làm SYSCLK

```c
RCC_ClkInit_t clk = {0};

clk.SysClkSource  = RCC_SYSCLK_HSE;
clk.AHB_Prescaler = RCC_AHB_DIV1;
clk.APB1_Prescaler = RCC_APB_DIV1;
clk.APB2_Prescaler = RCC_APB_DIV1;
/* FlashLatency và Timeout để 0: driver tự dùng auto/default */

if(RCC_ClockInit(&clk) != RCC_STATUS_OK)
{
    /* Handle clock error */
}
```

`RCC_ClockInit()` sẽ tự bật HSE, chờ `HSERDY` bằng timeout, rồi switch SYSCLK. Hàm trả về `RCC_STATUS_OK` nếu thành công.

---

## Ví dụ: PLL 84 MHz từ HSE 8 MHz

Cấu hình an toàn cho F407:

```text
HSE = 8 MHz
PLL_M = 8      -> VCO input = 1 MHz
PLL_N = 336    -> VCO = 336 MHz
PLL_P = /4     -> SYSCLK = 84 MHz
PLL_Q = 7      -> PLL48CLK = 48 MHz
AHB  = /1      -> HCLK  = 84 MHz
APB1 = /2      -> PCLK1 = 42 MHz
APB2 = /1      -> PCLK2 = 84 MHz
Flash latency = 2WS hoặc theo datasheet voltage range
```

```c
RCC_ClkInit_t clk = {0};

clk.SysClkSource = RCC_SYSCLK_PLL;
clk.PLL_Config.PLL_Source = RCC_PLL_SRC_HSE;
clk.PLL_Config.PLL_M = 8;
clk.PLL_Config.PLL_N = 336;
clk.PLL_Config.PLL_P = RCC_PLL_P_DIV4;
clk.PLL_Config.PLL_Q = 7;
clk.AHB_Prescaler = RCC_AHB_DIV1;
clk.APB1_Prescaler = RCC_APB_DIV2;
clk.APB2_Prescaler = RCC_APB_DIV1;
/* FlashLatency và Timeout để 0: driver tự dùng auto/default */

if(RCC_ClockInit(&clk) != RCC_STATUS_OK)
{
    /* Handle HSE/PLL timeout or invalid config */
}
```

Nếu chạy 168 MHz thì thường dùng `PLL_P=/2`, `APB1=/4`, `APB2=/2`, và flash latency cao hơn.

> Đây cũng chính là cấu hình mặc định trong `SystemClock_Config()` (`rcc_driver.c`), chỉ khác là dùng `PLL_M=8, PLL_N=336, PLL_P=/4` cho SYSCLK 168 MHz thay vì 84 MHz — đọc code hàm này để thấy đúng struct này được điền sẵn.

---

### Flash latency tự động và override

Mặc định **không cần cấu hình** field này nếu struct đã zero-init:

```c
RCC_ClkInit_t clk = {0}; // FlashLatency = 0 = auto
```

Driver sẽ tính **target HCLK sau AHB prescaler** rồi chọn wait-state phù hợp cho STM32F407 ở vùng nguồn 2.7V..3.6V:

| HCLK | Flash latency |
|------|---------------|
| <= 30 MHz | 0WS |
| <= 60 MHz | 1WS |
| <= 90 MHz | 2WS |
| <= 120 MHz | 3WS |
| <= 150 MHz | 4WS |
| <= 168 MHz | 5WS |

Nếu muốn tự ép giá trị để debug hoặc theo voltage range khác, mới cấu hình override:

```c
clk.FlashLatency = RCC_FLASH_LATENCY_OVERRIDE_3WS;
```

> Lưu ý: `RCC_FLASH_LATENCY_0WS` là giá trị phần cứng = 0, nên không dùng làm override trong config vì `0` được dành cho auto. Nếu thật sự muốn override 0WS, dùng `RCC_FLASH_LATENCY_OVERRIDE_0WS`.

### Timeout mặc định và override

Mặc định cũng **không cần cấu hình**:

```c
RCC_ClkInit_t clk = {0}; // Timeout = 0 = RCC_TIMEOUT_DEFAULT
```

Nếu muốn chờ lâu hơn/ngắn hơn khi bật HSE/PLL, mới cấu hình override:

```c
clk.Timeout = 500000U;
```

---

## Weak default init (`SystemClock_Config`, `MX_MCO2_Init`)

`rcc_driver.c` khai báo 2 hàm `__weak` (định nghĩa `__weak` ở `stm32f4xx_common.h`):

```c
__weak void SystemClock_Config(void);  // PLL 168 MHz mặc định
__weak void MX_MCO2_Init(void);        // Route PLL ra PC9 mặc định
```

Mục đích: `main()` chỉ cần gọi `SystemClock_Config(); MX_MCO2_Init();` mà không cần biết chi tiết cấu hình bên trong. Nếu một project khác muốn clock khác, chỉ cần **định nghĩa lại cùng tên hàm** (không `__weak`) ở file của project đó — linker sẽ ưu tiên bản không-weak, không cần sửa file driver. Đây là pattern giống HAL của ST (`SystemClock_Config()` trong `main.c` được CubeMX sinh ra theo cùng cách).

`clk` (biến `RCC_ClkInit_t`) cũng là global dùng chung, khai báo `extern` trong `rcc_driver.h`, định nghĩa trong `rcc_driver.c` — tương tự cách STM32 HAL dùng global handle.

---

## API

### Status enum

```c
typedef enum {
    RCC_STATUS_OK = 0,
    RCC_STATUS_ERROR,
    RCC_STATUS_TIMEOUT,
    RCC_STATUS_INVALID_PARAM
} RCC_Status_t;
```

Các hàm init trả về status để tránh treo vô hạn khi HSE/PLL không ready. `Timeout = 0` sẽ dùng `RCC_TIMEOUT_DEFAULT`; `FlashLatency = 0` sẽ auto theo target HCLK.

| Function | Mô tả |
|----------|-------|
| `RCC_HSI_Enable(timeout)` | Bật HSI và chờ `HSIRDY` |
| `RCC_HSE_Enable(timeout)` | Bật HSE và chờ `HSERDY` |
| `RCC_PLL_Config()` | Validate PLL rồi ghi PLLM/PLLN/PLLP/PLLSRC/PLLQ vào `PLLCFGR` |
| `RCC_ClockInit()` | Validate config, cấu hình flash latency, oscillator/PLL, prescaler, switch SYSCLK |
| `RCC_GetSysClockFreq()` | Đọc `SWS` và trả về SYSCLK hiện tại |
| `RCC_GetHCLKFreq()` | Tính HCLK từ SYSCLK và `HPRE` |
| `RCC_GetPCLK1Freq()` | Tính PCLK1 từ HCLK và `PPRE1` |
| `RCC_GetPCLK2Freq()` | Tính PCLK2 từ HCLK và `PPRE2` |
| `RCC_GetPLLOutputClock()` | Tính PLLCLK từ `PLLCFGR` |
| `RCC_MCO1_Config()` | Route clock ra PA8/MCO1 |
| `RCC_MCO2_Config()` | Route clock ra PC9/MCO2 |

---

## Peripheral clock macros

### GPIO (AHB1)

```c
GPIOx_PCLK_EN()
GPIOx_PCLK_DI()
GPIOx_PCLK_RESET()
```

`x = A..I`.

### SPI

```c
SPI1_PCLK_EN()   // APB2 bit 12
SPI2_PCLK_EN()   // APB1 bit 14
SPI3_PCLK_EN()   // APB1 bit 15
```

### I2C

```c
I2C1_PCLK_EN()   // APB1 bit 21
I2C2_PCLK_EN()   // APB1 bit 22
I2C3_PCLK_EN()   // APB1 bit 23
```

### USART

```c
USART1_PCLK_EN() // APB2 bit 4
USART2_PCLK_EN() // APB1 bit 17
USART3_PCLK_EN() // APB1 bit 18
```

### SYSCFG

```c
SYSCFG_PCLK_EN() // APB2 bit 14, cần cho EXTI EXTICR
```

---

## Debug tips

- Peripheral không chạy: kiểm tra clock enable bit trong `RCC->AHB1ENR`, `APB1ENR`, `APB2ENR`.
- Bật PLL fail: kiểm tra return status. `RCC_STATUS_TIMEOUT` thường do HSE/PLL không ready; `RCC_STATUS_INVALID_PARAM` thường do PLLM/N/P/Q hoặc bus clock vượt giới hạn.
- USART baud sai sau khi đổi clock: tính lại BRR theo `RCC_GetPCLKxFreq()`.
- SPI speed thay đổi khi đổi APB clock: baud rate = `PCLK / prescaler`.
- Muốn đo clock thật: dùng `RCC_MCO1_Config()` rồi cấu hình PA8 AF0 và đo bằng logic analyzer/oscilloscope.
- Board chạy sai/treo ngẫu nhiên sau khi tăng SYSCLK: nghi ngờ đầu tiên là flash latency chưa đủ — kiểm tra `FLASH->ACR` hoặc để `FlashLatency = 0` (auto) thay vì tự set tay.
