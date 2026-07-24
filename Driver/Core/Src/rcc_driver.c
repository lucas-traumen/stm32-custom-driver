#include "rcc_driver.h"

RCC_ClkInit_t clk = {0};

/* Prescaler lookup tables */
static const uint16_t AHB_Prescaler[8] = {2, 4, 8, 16, 64, 128, 256, 512};
static const uint8_t APB_Prescaler[4] = {2, 4, 8, 16};

/**
 * @brief Return timeout value, using default when caller passes 0.
 * @param timeout User timeout loop count.
 * @return Effective timeout loop count.
 */
static uint32_t RCC_GetEffectiveTimeout(uint32_t timeout)
{
    return (timeout == 0U) ? RCC_TIMEOUT_DEFAULT : timeout;
}

/**
 * @brief Wait until selected RCC->CR flag reaches expected state.
 * @param flag_mask RCC_CR flag mask, for example RCC_CR_HSERDY_Msk.
 * @param expected SET or RESET.
 * @param timeout Polling loop timeout; 0 uses RCC_TIMEOUT_DEFAULT.
 * @return RCC_STATUS_OK if flag reached expected state, otherwise RCC_STATUS_TIMEOUT.
 */
static RCC_Status_t RCC_WaitCRFlag(uint32_t flag_mask, uint8_t expected, uint32_t timeout)
{
    uint32_t tick = RCC_GetEffectiveTimeout(timeout);

    while(tick > 0U)
    {
        uint8_t current = ((RCC->CR & flag_mask) != 0U) ? SET : RESET;

        if(current == expected)
        {
            return RCC_STATUS_OK;
        }

        tick--;
    }

    return RCC_STATUS_TIMEOUT;
}

/**
 * @brief Decode an AHB prescaler register value to a divider.
 * @param hpre Encoded HPRE field value.
 * @return AHB divider value.
 */
static uint32_t RCC_DecodeAHBPrescaler(uint32_t hpre)
{
    return (hpre < 8U) ? 1U : AHB_Prescaler[hpre - 8U];
}

/**
 * @brief Decode an APB prescaler register value to a divider.
 * @param ppre Encoded PPRE field value.
 * @return APB divider value.
 */
static uint32_t RCC_DecodeAPBPrescaler(uint32_t ppre)
{
    return (ppre < 4U) ? 1U : APB_Prescaler[ppre - 4U];
}

/**
 * @brief Check if encoded AHB prescaler value is valid for STM32F4 CFGR HPRE.
 * @param prescaler RCC_AHBPrescaler_t value.
 * @return SET if valid, RESET if invalid.
 */
static uint8_t RCC_IsValidAHBPrescaler(RCC_AHBPrescaler_t prescaler)
{
    return ((prescaler == RCC_AHB_DIV1)   || (prescaler == RCC_AHB_DIV2)   ||
            (prescaler == RCC_AHB_DIV4)   || (prescaler == RCC_AHB_DIV8)   ||
            (prescaler == RCC_AHB_DIV16)  || (prescaler == RCC_AHB_DIV64)  ||
            (prescaler == RCC_AHB_DIV128) || (prescaler == RCC_AHB_DIV256) ||
            (prescaler == RCC_AHB_DIV512)) ? SET : RESET;
}

/**
 * @brief Check if encoded APB prescaler value is valid for STM32F4 CFGR PPRE.
 * @param prescaler RCC_APBPrescaler_t value.
 * @return SET if valid, RESET if invalid.
 */
static uint8_t RCC_IsValidAPBPrescaler(RCC_APBPrescaler_t prescaler)
{
    return ((prescaler == RCC_APB_DIV1)  || (prescaler == RCC_APB_DIV2) ||
            (prescaler == RCC_APB_DIV4)  || (prescaler == RCC_APB_DIV8) ||
            (prescaler == RCC_APB_DIV16)) ? SET : RESET;
}

/**
 * @brief Calculate PLLCLK from a config struct without touching registers.
 * @param pPLLConfig Pointer to PLL config.
 * @return PLLCLK in Hz, or 0 if divider fields would divide by zero.
 */
static uint32_t RCC_CalcPLLClockFromConfig(const RCC_PLL_Config_t *pPLLConfig)
{
    uint32_t pll_input;
    uint32_t pllp;
    uint32_t vco;

    pll_input = (pPLLConfig->PLL_Source == RCC_PLL_SRC_HSE) ? RCC_HSE_FREQ : RCC_HSI_FREQ;
    pllp = ((uint32_t)pPLLConfig->PLL_P + 1U) * 2U;

    if((pPLLConfig->PLL_M == 0U) || (pllp == 0U))
    {
        return 0U;
    }

    vco = (pll_input / (uint32_t)pPLLConfig->PLL_M) * (uint32_t)pPLLConfig->PLL_N;

    return vco / pllp;
}

/**
 * @brief Calculate Flash wait states from target HCLK.
 * @param hclk Target AHB/HCLK frequency in Hz after AHB prescaler.
 * @return Flash latency enum for STM32F407 at 2.7V..3.6V supply range.
 * @note Thresholds follow the common STM32F4 3.3V table: 0WS <=30MHz,
 *       1WS <=60MHz, 2WS <=90MHz, 3WS <=120MHz, 4WS <=150MHz, 5WS <=168MHz.
 */
RCC_FlashLatency_t RCC_GetFlashLatency(uint32_t hclk)
{
    if(hclk <= 30000000U)
    {
        return RCC_FLASH_LATENCY_0WS;
    }
    else if(hclk <= 60000000U)
    {
        return RCC_FLASH_LATENCY_1WS;
    }
    else if(hclk <= 90000000U)
    {
        return RCC_FLASH_LATENCY_2WS;
    }
    else if(hclk <= 120000000U)
    {
        return RCC_FLASH_LATENCY_3WS;
    }
    else if(hclk <= 150000000U)
    {
        return RCC_FLASH_LATENCY_4WS;
    }
    else
    {
        return RCC_FLASH_LATENCY_5WS;
    }
}

/**
 * @brief Validate main PLL parameters against STM32F407 clock constraints.
 * @param pPLLConfig Pointer to PLL config.
 * @return RCC_STATUS_OK if valid, RCC_STATUS_INVALID_PARAM otherwise.
 * @note Checks common F407 ranges: PLLM 2..63, PLLN 50..432, PLLQ 2..15,
 *       VCO input 1..2 MHz, VCO 100..432 MHz, PLLCLK <= 168 MHz.
 */
static RCC_Status_t RCC_ValidatePLLConfig(const RCC_PLL_Config_t *pPLLConfig)
{
    uint32_t pll_input;
    uint32_t vco_input;
    uint32_t vco;
    uint32_t pllclk;

    if(pPLLConfig == NULL)
    {
        return RCC_STATUS_INVALID_PARAM;
    }

    if((pPLLConfig->PLL_Source != RCC_PLL_SRC_HSI) &&
       (pPLLConfig->PLL_Source != RCC_PLL_SRC_HSE))
    {
        return RCC_STATUS_INVALID_PARAM;
    }

    if((pPLLConfig->PLL_M < 2U) || (pPLLConfig->PLL_M > 63U) ||
       (pPLLConfig->PLL_N < 50U) || (pPLLConfig->PLL_N > 432U) ||
       (pPLLConfig->PLL_P > RCC_PLL_P_DIV8) ||
       (pPLLConfig->PLL_Q < 2U) || (pPLLConfig->PLL_Q > 15U))
    {
        return RCC_STATUS_INVALID_PARAM;
    }

    pll_input = (pPLLConfig->PLL_Source == RCC_PLL_SRC_HSE) ? RCC_HSE_FREQ : RCC_HSI_FREQ;
    vco_input = pll_input / (uint32_t)pPLLConfig->PLL_M;
    vco = vco_input * (uint32_t)pPLLConfig->PLL_N;
    pllclk = RCC_CalcPLLClockFromConfig(pPLLConfig);

    if((vco_input < 1000000U) || (vco_input > 2000000U) ||
       (vco < 100000000U) || (vco > 432000000U) ||
       (pllclk > 168000000U))
    {
        return RCC_STATUS_INVALID_PARAM;
    }

    return RCC_STATUS_OK;
}

/**
 * @brief Validate full clock configuration before writing clock registers.
 * @param pClkInit Pointer to clock configuration.
 * @return RCC_STATUS_OK if valid, RCC_STATUS_INVALID_PARAM otherwise.
 * @note Checks encoded prescalers and F407 bus maximum frequencies.
 */
static RCC_Status_t RCC_ValidateClockConfig(const RCC_ClkInit_t *pClkInit)
{
    uint32_t sysclk;
    uint32_t hclk;
    uint32_t pclk1;
    uint32_t pclk2;

    if(pClkInit == NULL)
    {
        return RCC_STATUS_INVALID_PARAM;
    }

    if((pClkInit->SysClkSource != RCC_SYSCLK_HSI) &&
       (pClkInit->SysClkSource != RCC_SYSCLK_HSE) &&
       (pClkInit->SysClkSource != RCC_SYSCLK_PLL))
    {
        return RCC_STATUS_INVALID_PARAM;
    }

    if((RCC_IsValidAHBPrescaler(pClkInit->AHB_Prescaler) == RESET) ||
       (RCC_IsValidAPBPrescaler(pClkInit->APB1_Prescaler) == RESET) ||
       (RCC_IsValidAPBPrescaler(pClkInit->APB2_Prescaler) == RESET) ||
       (pClkInit->FlashLatency > RCC_FLASH_LATENCY_OVERRIDE_7WS))
    {
        return RCC_STATUS_INVALID_PARAM;
    }

    if(pClkInit->SysClkSource == RCC_SYSCLK_HSI)
    {
        sysclk = RCC_HSI_FREQ;
    }
    else if(pClkInit->SysClkSource == RCC_SYSCLK_HSE)
    {
        sysclk = RCC_HSE_FREQ;
    }
    else
    {
        if(RCC_ValidatePLLConfig(&pClkInit->PLL_Config) != RCC_STATUS_OK)
        {
            return RCC_STATUS_INVALID_PARAM;
        }

        sysclk = RCC_CalcPLLClockFromConfig(&pClkInit->PLL_Config);
    }

    hclk = sysclk / RCC_DecodeAHBPrescaler((uint32_t)pClkInit->AHB_Prescaler);
    pclk1 = hclk / RCC_DecodeAPBPrescaler((uint32_t)pClkInit->APB1_Prescaler);
    pclk2 = hclk / RCC_DecodeAPBPrescaler((uint32_t)pClkInit->APB2_Prescaler);

    if((sysclk > 168000000U) || (hclk > 168000000U) ||
       (pclk1 > 42000000U) || (pclk2 > 84000000U))
    {
        return RCC_STATUS_INVALID_PARAM;
    }

    return RCC_STATUS_OK;
}

/**
 * @brief Enable HSI and wait until the oscillator is ready.
 * @param timeout Polling loop timeout; 0 uses RCC_TIMEOUT_DEFAULT.
 * @return RCC_STATUS_OK or RCC_STATUS_TIMEOUT.
 */
RCC_Status_t RCC_HSI_Enable(uint32_t timeout)
{
    RCC->CR |= RCC_CR_HSION;

    return RCC_WaitCRFlag(RCC_CR_HSIRDY_Msk, SET, timeout);
}

/**
 * @brief Enable HSE and wait until the oscillator is ready.
 * @param timeout Polling loop timeout; 0 uses RCC_TIMEOUT_DEFAULT.
 * @return RCC_STATUS_OK or RCC_STATUS_TIMEOUT.
 * @note STM32F407 Discovery normally uses an 8 MHz external crystal.
 */
RCC_Status_t RCC_HSE_Enable(uint32_t timeout)
{
    RCC->CR |= RCC_CR_HSEON;

    return RCC_WaitCRFlag(RCC_CR_HSERDY_Msk, SET, timeout);
}

/**
 * @brief Configure PLL register fields.
 * @param pPLLConfig Pointer to PLL configuration struct.
 * @return RCC_STATUS_OK or RCC_STATUS_INVALID_PARAM.
 * @note PLL must be OFF before changing PLLCFGR. This function only writes
 *       PLLCFGR; RCC_ClockInit() handles PLL disable/enable/wait.
 */
RCC_Status_t RCC_PLL_Config(const RCC_PLL_Config_t *pPLLConfig)
{
    uint32_t tempreg;

    if(RCC_ValidatePLLConfig(pPLLConfig) != RCC_STATUS_OK)
    {
        return RCC_STATUS_INVALID_PARAM;
    }

    tempreg = RCC->PLLCFGR;

    tempreg &= ~(RCC_PLLCFGR_PLLM_Msk |
                 RCC_PLLCFGR_PLLN_Msk |
                 RCC_PLLCFGR_PLLP_Msk |
                 RCC_PLLCFGR_PLLSRC_Msk |
                 RCC_PLLCFGR_PLLQ_Msk);

    tempreg |= ((uint32_t)pPLLConfig->PLL_M & 0x3FU) << RCC_PLLCFGR_PLLM_Pos;
    tempreg |= ((uint32_t)pPLLConfig->PLL_N & 0x1FFU) << RCC_PLLCFGR_PLLN_Pos;
    tempreg |= ((uint32_t)pPLLConfig->PLL_P & 0x3U) << RCC_PLLCFGR_PLLP_Pos;
    tempreg |= ((uint32_t)pPLLConfig->PLL_Source & 0x1U) << RCC_PLLCFGR_PLLSRC_Pos;
    tempreg |= ((uint32_t)pPLLConfig->PLL_Q & 0xFU) << RCC_PLLCFGR_PLLQ_Pos;

    RCC->PLLCFGR = tempreg;

    return RCC_STATUS_OK;
}

/**
 * @brief Get PLL system clock output frequency from RCC_PLLCFGR.
 * @return PLLCLK frequency in Hz, or 0 if PLLM/PLLP are invalid.
 */
uint32_t RCC_GetPLLOutputClock(void)
{
    RCC_PLL_Config_t pll_config;

    pll_config.PLL_Source = ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC_Msk) != 0U) ?
                            RCC_PLL_SRC_HSE : RCC_PLL_SRC_HSI;
    pll_config.PLL_M = (uint16_t)((RCC->PLLCFGR & RCC_PLLCFGR_PLLM_Msk) >> RCC_PLLCFGR_PLLM_Pos);
    pll_config.PLL_N = (uint16_t)((RCC->PLLCFGR & RCC_PLLCFGR_PLLN_Msk) >> RCC_PLLCFGR_PLLN_Pos);
    pll_config.PLL_P = (RCC_PLL_P_Div_t)((RCC->PLLCFGR & RCC_PLLCFGR_PLLP_Msk) >> RCC_PLLCFGR_PLLP_Pos);
    pll_config.PLL_Q = (uint16_t)((RCC->PLLCFGR & RCC_PLLCFGR_PLLQ_Msk) >> RCC_PLLCFGR_PLLQ_Pos);

    return RCC_CalcPLLClockFromConfig(&pll_config);
}

/**
 * @brief Get system clock (SYSCLK) frequency.
 * @return SYSCLK frequency in Hz.
 */
uint32_t RCC_GetSysClockFreq(void)
{
    uint32_t sysclk;
    uint32_t clk_src;

    clk_src = (RCC->CFGR & RCC_CFGR_SWS_Msk) >> RCC_CFGR_SWS_Pos;

    switch(clk_src)
    {
        case RCC_SYSCLK_HSI:
            sysclk = RCC_HSI_FREQ;
            break;

        case RCC_SYSCLK_HSE:
            sysclk = RCC_HSE_FREQ;
            break;

        case RCC_SYSCLK_PLL:
            sysclk = RCC_GetPLLOutputClock();
            break;

        default:
            sysclk = RCC_HSI_FREQ;
            break;
    }

    return sysclk;
}

/**
 * @brief Get AHB bus clock (HCLK) frequency.
 * @return HCLK frequency in Hz.
 */
uint32_t RCC_GetHCLKFreq(void)
{
    uint32_t sysclk;
    uint32_t hpre;

    sysclk = RCC_GetSysClockFreq();
    hpre = (RCC->CFGR & RCC_CFGR_HPRE_Msk) >> RCC_CFGR_HPRE_Pos;

    return sysclk / RCC_DecodeAHBPrescaler(hpre);
}

/**
 * @brief Get APB1 bus clock (PCLK1) frequency.
 * @return PCLK1 frequency in Hz.
 */
uint32_t RCC_GetPCLK1Freq(void)
{
    uint32_t hclk;
    uint32_t ppre1;

    hclk = RCC_GetHCLKFreq();
    ppre1 = (RCC->CFGR & RCC_CFGR_PPRE1_Msk) >> RCC_CFGR_PPRE1_Pos;

    return hclk / RCC_DecodeAPBPrescaler(ppre1);
}

/**
 * @brief Get APB2 bus clock (PCLK2) frequency.
 * @return PCLK2 frequency in Hz.
 */
uint32_t RCC_GetPCLK2Freq(void)
{
    uint32_t hclk;
    uint32_t ppre2;

    hclk = RCC_GetHCLKFreq();
    ppre2 = (RCC->CFGR & RCC_CFGR_PPRE2_Msk) >> RCC_CFGR_PPRE2_Pos;

    return hclk / RCC_DecodeAPBPrescaler(ppre2);
}

/**
 * @brief Configure SYSCLK source and AHB/APB prescalers.
 * @param pClkInit Pointer to clock configuration struct.
 * @return RCC_STATUS_OK, RCC_STATUS_INVALID_PARAM, or RCC_STATUS_TIMEOUT.
 *
 * HAL/OOP-style sequence:
 * 1. Validate config and bus limits.
 * 2. Auto-calculate flash latency from target HCLK unless user overrides it.
 * 3. Enable selected oscillator / configure and lock PLL if needed.
 * 4. Program AHB/APB prescalers.
 * 5. Switch SYSCLK and wait until SWS confirms the switch.
 */
RCC_Status_t RCC_ClockInit(const RCC_ClkInit_t *pClkInit)
{
    RCC_Status_t status;
    uint32_t flash_acr;
    uint32_t cfgr;
    uint32_t target_sws;
    uint32_t timeout;
    uint32_t sysclk;
    uint32_t hclk;
    RCC_FlashLatency_t flash_latency;

    status = RCC_ValidateClockConfig(pClkInit);
    if(status != RCC_STATUS_OK)
    {
        return status;
    }

    timeout = RCC_GetEffectiveTimeout(pClkInit->Timeout);

    if(pClkInit->SysClkSource == RCC_SYSCLK_HSI)
    {
        sysclk = RCC_HSI_FREQ;
    }
    else if(pClkInit->SysClkSource == RCC_SYSCLK_HSE)
    {
        sysclk = RCC_HSE_FREQ;
    }
    else
    {
        sysclk = RCC_CalcPLLClockFromConfig(&pClkInit->PLL_Config);
    }

    hclk = sysclk / RCC_DecodeAHBPrescaler((uint32_t)pClkInit->AHB_Prescaler);

    if(pClkInit->FlashLatency == RCC_FLASH_LATENCY_AUTO)
    {
        flash_latency = RCC_GetFlashLatency(hclk);
    }
    else
    {
        /* Override encoding is 1..8, hardware latency encoding is 0..7. */
        flash_latency = (RCC_FlashLatency_t)(pClkInit->FlashLatency - 1U);
    }

    flash_acr = FLASH->ACR;
    flash_acr &= ~FLASH_ACR_LATENCY_Msk;
    flash_acr |= ((uint32_t)flash_latency & FLASH_ACR_LATENCY_Msk);
    FLASH->ACR = flash_acr;

    if(pClkInit->SysClkSource == RCC_SYSCLK_HSI)
    {
        status = RCC_HSI_Enable(timeout);
    }
    else if(pClkInit->SysClkSource == RCC_SYSCLK_HSE)
    {
        status = RCC_HSE_Enable(timeout);
    }
    else
    {
        if(pClkInit->PLL_Config.PLL_Source == RCC_PLL_SRC_HSE)
        {
            status = RCC_HSE_Enable(timeout);
        }
        else
        {
            status = RCC_HSI_Enable(timeout);
        }

        if(status != RCC_STATUS_OK)
        {
            return status;
        }

        RCC->CR &= ~RCC_CR_PLLON_Msk;
        status = RCC_WaitCRFlag(RCC_CR_PLLRDY_Msk, RESET, timeout);
        if(status != RCC_STATUS_OK)
        {
            return status;
        }

        status = RCC_PLL_Config(&pClkInit->PLL_Config);
        if(status != RCC_STATUS_OK)
        {
            return status;
        }

        RCC->CR |= RCC_CR_PLLON;
        status = RCC_WaitCRFlag(RCC_CR_PLLRDY_Msk, SET, timeout);
    }

    if(status != RCC_STATUS_OK)
    {
        return status;
    }

    cfgr = RCC->CFGR;

    cfgr &= ~RCC_CFGR_HPRE_Msk;
    cfgr |= ((uint32_t)pClkInit->AHB_Prescaler << RCC_CFGR_HPRE_Pos);

    cfgr &= ~RCC_CFGR_PPRE1_Msk;
    cfgr |= ((uint32_t)pClkInit->APB1_Prescaler << RCC_CFGR_PPRE1_Pos);

    cfgr &= ~RCC_CFGR_PPRE2_Msk;
    cfgr |= ((uint32_t)pClkInit->APB2_Prescaler << RCC_CFGR_PPRE2_Pos);

    cfgr &= ~RCC_CFGR_SW_Msk;
    cfgr |= ((uint32_t)pClkInit->SysClkSource << RCC_CFGR_SW_Pos);

    RCC->CFGR = cfgr;

    target_sws = (uint32_t)pClkInit->SysClkSource;
    timeout = RCC_GetEffectiveTimeout(pClkInit->Timeout);

    while(timeout > 0U)
    {
        if(((RCC->CFGR & RCC_CFGR_SWS_Msk) >> RCC_CFGR_SWS_Pos) == target_sws)
        {
            return RCC_STATUS_OK;
        }

        timeout--;
    }

    return RCC_STATUS_TIMEOUT;
}

/**
 * @brief Route a clock to the MCO1 pin (PA8).
 * @param source Clock to output: HSI, LSE, HSE, or PLL.
 * @param prescaler Division applied before output: DIV1..DIV5.
 * @note Caller must configure PA8 as AF0, push-pull, high speed.
 */
void RCC_MCO1_Config(RCC_MCO1Source_t source, RCC_MCOPrescaler_t prescaler)
{
    uint32_t cfgr;

    cfgr = RCC->CFGR;
    cfgr &= ~(RCC_CFGR_MCO1_Msk | RCC_CFGR_MCO1PRE_Msk);
    cfgr |= ((uint32_t)source & 0x3U) << RCC_CFGR_MCO1_Pos;
    cfgr |= ((uint32_t)prescaler & 0x7U) << RCC_CFGR_MCO1PRE_Pos;
    RCC->CFGR = cfgr;
}

/**
 * @brief Route a clock to the MCO2 pin (PC9).
 * @param source Clock to output: SYSCLK, PLLI2S, HSE, or PLL.
 * @param prescaler Division applied before output: DIV1..DIV5.
 * @note Caller must configure PC9 as AF0, push-pull, high speed.
 */
void RCC_MCO2_Config(RCC_MCO2Source_t source, RCC_MCOPrescaler_t prescaler)
{
    uint32_t cfgr;

    cfgr = RCC->CFGR;
    cfgr &= ~(RCC_CFGR_MCO2_Msk | RCC_CFGR_MCO2PRE_Msk);
    cfgr |= ((uint32_t)source & 0x3U) << RCC_CFGR_MCO2_Pos;
    cfgr |= ((uint32_t)prescaler & 0x7U) << RCC_CFGR_MCO2PRE_Pos;
    RCC->CFGR = cfgr;
}

/**
 * @brief Default system clock setup. Override this weak function when needed.
 * @note PLL @ HSE 8MHz, M=8, N=336, P=DIV4, Q=7 -> SYSCLK 168MHz, APB1 42MHz, APB2 84MHz.
 */
__weak void SystemClock_Config(void)
{
    clk.SysClkSource = RCC_SYSCLK_PLL;
    clk.PLL_Config.PLL_Source = RCC_PLL_SRC_HSE;
    clk.PLL_Config.PLL_M = 8;
    clk.PLL_Config.PLL_N = 336;
    clk.PLL_Config.PLL_P = RCC_PLL_P_DIV4;
    clk.PLL_Config.PLL_Q = 7;
    clk.AHB_Prescaler = RCC_AHB_DIV1;
    clk.APB1_Prescaler = RCC_APB_DIV2;
    clk.APB2_Prescaler = RCC_APB_DIV1;

    if(RCC_ClockInit(&clk) != RCC_STATUS_OK)
    {
        while(1);
    }
}

/**
 * @brief Default MCO2 setup on PC9. Override to select another source/divider.
 */
__weak void MX_MCO2_Init(void)
{
    RCC_MCO2_Config(RCC_MCO2_SRC_PLL, RCC_MCO_DIV3);
}
