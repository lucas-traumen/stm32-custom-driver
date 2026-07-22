# RCC (Reset and Clock Control) Driver

## Tổng quan

RCC driver cung cấp các API để cấu hình clock tree của STM32F407, bao gồm HSE, PLL, và các prescaler cho AHB/APB1/APB2.

## Kiến trúc Clock Tree STM32F407

```
HSI (16MHz) ───┐
               ├──> PLL ──> SYSCLK ──> AHB Prescaler ──> HCLK
HSE (8MHz)  ───┘                            │
                                            ├──> APB1 Prescaler ──> PCLK1 (≤50MHz)
                                            └──> APB2 Prescaler ──> PCLK2 (≤100MHz)
```

### PLL Configuration

PLL_VCO = (HSE_VALUE or HSI_VALUE / PLLM) × PLLN
SYSCLK = PLL_VCO / PLLP

**Ví dụ:** HSE 8MHz, PLLM=8, PLLN=200, PLLP=2
- VCO = (8MHz / 8) × 200 = 200MHz
- SYSCLK = 200MHz / 2 = 100MHz

## Structures

### `RCC_PLL_Config_t`
```c
typedef struct {
    RCC_PLLSource_t PLL_Source;  // HSI hoặc HSE
    uint16_t PLL_M;               // 2-63: Division factor cho PLL input
    uint16_t PLL_N;               // 50-432: Multiplication factor
    RCC_PLL_P_Div_t PLL_P;        // 2,4,6,8: Division factor cho SYSCLK
    uint16_t PLL_Q;               // 2-15: Division factor cho USB/SDIO
} RCC_PLL_Config_t;
```

### `RCC_ClkInit_t`
```c
typedef struct {
    RCC_SysClkSource_t SysClkSource;     // HSI, HSE, hoặc PLL
    RCC_PLL_Config_t PLL_Config;         // Cấu hình PLL
    RCC_AHBPrescaler_t AHB_Prescaler;    // AHB divider
    RCC_APBPrescaler_t APB1_Prescaler;   // APB1 divider
    RCC_APBPrescaler_t APB2_Prescaler;   // APB2 divider
    uint8_t FlashLatency;                // 0-7 wait states
} RCC_ClkInit_t;
```

## API Functions

### `RCC_HSE_Config(void)`
Bật HSE oscillator và đợi cho đến khi ổn định.

### `RCC_PLL_Config(RCC_PLL_Config_t *pPLLConfig)`
Cấu hình PLL với các tham số PLLM, PLLN, PLLP, PLLQ.

**Parameters:**
- `pPLLConfig`: Con trỏ tới cấu hình PLL

### `RCC_SysClk_Config(RCC_ClkInit_t *pClkInit)`
Cấu hình system clock, flash latency, và các prescaler.

**Parameters:**
- `pClkInit`: Con trỏ tới cấu hình clock

### `RCC_GetSysClockFreq(void)`
Trả về tần số SYSCLK hiện tại.

**Returns:** Tần số SYSCLK tính bằng Hz

### `RCC_GetHCLKFreq(void)`
Trả về tần số HCLK (AHB clock).

**Returns:** Tần số HCLK tính bằng Hz

### `RCC_GetPCLK1Freq(void)`
Trả về tần số PCLK1 (APB1 clock).

**Returns:** Tần số PCLK1 tính bằng Hz

### `RCC_GetPCLK2Freq(void)`
Trả về tần số PCLK2 (APB2 clock).

**Returns:** Tần số PCLK2 tính bằng Hz

## Ví dụ sử dụng

### Cấu hình SYSCLK 100MHz từ HSE 8MHz

```c
void System_Clock_Config_100MHz(void)
{
    RCC_PLL_Config_t pll_config;
    RCC_ClkInit_t clk_init;

    // Bật HSE
    RCC_HSE_Config();

    // Cấu hình PLL: VCO = 8MHz/8 * 200 = 200MHz, SYSCLK = 200MHz/2 = 100MHz
    pll_config.PLL_Source = RCC_PLL_SRC_HSE;
    pll_config.PLL_M = 8;
    pll_config.PLL_N = 200;
    pll_config.PLL_P = RCC_PLL_P_DIV2;
    pll_config.PLL_Q = 4;
    RCC_PLL_Config(&pll_config);

    // Cấu hình System Clock
    clk_init.SysClkSource = RCC_SYSCLK_PLL;
    clk_init.PLL_Config = pll_config;
    clk_init.AHB_Prescaler = RCC_AHB_DIV1;     // HCLK = 100MHz
    clk_init.APB1_Prescaler = RCC_APB_DIV2;    // PCLK1 = 50MHz
    clk_init.APB2_Prescaler = RCC_APB_DIV1;    // PCLK2 = 100MHz
    clk_init.FlashLatency = 3;                  // 3 wait states cho 100MHz
    RCC_SysClk_Config(&clk_init);
}
```

## Flash Latency

Flash latency phải được cấu hình dựa trên HCLK frequency và Vdd:

| HCLK (MHz) | Vdd ≥ 2.7V | Vdd 2.4-2.7V | Vdd 2.1-2.4V |
|------------|------------|--------------|--------------|
| 0-30       | 0 WS       | 0 WS         | 0 WS         |
| 30-60      | 1 WS       | 1 WS         | 2 WS         |
| 60-90      | 2 WS       | 3 WS         | 4 WS         |
| 90-120     | 3 WS       | 4 WS         | 5 WS         |
| 120-150    | 4 WS       | 5 WS         | 6 WS         |
| 150-168    | 5 WS       | 6 WS         | 7 WS         |

## Lưu ý

1. **Flash latency phải được cấu hình TRƯỚC khi tăng clock**
2. APB1 tần số tối đa là 50MHz
3. APB2 tần số tối đa là 100MHz
4. PLL_VCO phải trong khoảng 100-432MHz
5. PLL input phải trong khoảng 1-2MHz (sau khi chia PLLM)
