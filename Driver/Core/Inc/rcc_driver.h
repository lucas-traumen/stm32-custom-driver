#ifndef _RCC_DRIVER_H_
#define _RCC_DRIVER_H_

#include "stm32f407xx.h"
#include "stm32f4xx_common.h"

#define RCC_HSI_FREQ 16000000U
#define RCC_HSE_FREQ  8000000U

#define RCC_TIMEOUT_DEFAULT 100000U

/* FlashLatency config values: 0 means auto; non-zero values override auto. */
#define RCC_FLASH_LATENCY_AUTO         0U
#define RCC_FLASH_LATENCY_OVERRIDE_0WS 1U
#define RCC_FLASH_LATENCY_OVERRIDE_1WS 2U
#define RCC_FLASH_LATENCY_OVERRIDE_2WS 3U
#define RCC_FLASH_LATENCY_OVERRIDE_3WS 4U
#define RCC_FLASH_LATENCY_OVERRIDE_4WS 5U
#define RCC_FLASH_LATENCY_OVERRIDE_5WS 6U
#define RCC_FLASH_LATENCY_OVERRIDE_6WS 7U
#define RCC_FLASH_LATENCY_OVERRIDE_7WS 8U

typedef enum {
    RCC_STATUS_OK = 0,
    RCC_STATUS_ERROR,
    RCC_STATUS_TIMEOUT,
    RCC_STATUS_INVALID_PARAM
} RCC_Status_t;

typedef enum {
    RCC_SYSCLK_HSI = 0,
    RCC_SYSCLK_HSE,
    RCC_SYSCLK_PLL
} RCC_SysClkSource_t;

typedef enum {
    RCC_PLL_SRC_HSI = 0,
    RCC_PLL_SRC_HSE
} RCC_PLLSource_t;

typedef enum {
    RCC_AHB_DIV1 = 0,
    RCC_AHB_DIV2 = 8,
    RCC_AHB_DIV4 = 9,
    RCC_AHB_DIV8 = 10,
    RCC_AHB_DIV16 = 11,
    RCC_AHB_DIV64 = 12,
    RCC_AHB_DIV128 = 13,
    RCC_AHB_DIV256 = 14,
    RCC_AHB_DIV512 = 15
} RCC_AHBPrescaler_t;

typedef enum {
    RCC_APB_DIV1 = 0,
    RCC_APB_DIV2 = 4,
    RCC_APB_DIV4 = 5,
    RCC_APB_DIV8 = 6,
    RCC_APB_DIV16 = 7
} RCC_APBPrescaler_t;

typedef enum {
    RCC_PLL_P_DIV2 = 0,
    RCC_PLL_P_DIV4 = 1,
    RCC_PLL_P_DIV6 = 2,
    RCC_PLL_P_DIV8 = 3
} RCC_PLL_P_Div_t;

typedef struct {
    RCC_PLLSource_t PLL_Source; /* PLL input clock source: HSI or HSE */
    uint16_t PLL_M;             /* Division factor for the PLL input clock, valid range 2..63 */
    uint16_t PLL_N;             /* Multiplication factor for the VCO, valid range 50..432 */
    RCC_PLL_P_Div_t PLL_P;      /* Division factor for the main system clock (PLLCLK) */
    uint16_t PLL_Q;             /* Division factor for USB OTG FS/SDIO/RNG clocks, valid range 2..15 */
} RCC_PLL_Config_t;

typedef enum {
    RCC_FLASH_LATENCY_0WS = FLASH_ACR_LATENCY_0WS,
    RCC_FLASH_LATENCY_1WS = FLASH_ACR_LATENCY_1WS,
    RCC_FLASH_LATENCY_2WS = FLASH_ACR_LATENCY_2WS,
    RCC_FLASH_LATENCY_3WS = FLASH_ACR_LATENCY_3WS,
    RCC_FLASH_LATENCY_4WS = FLASH_ACR_LATENCY_4WS,
    RCC_FLASH_LATENCY_5WS = FLASH_ACR_LATENCY_5WS,
    RCC_FLASH_LATENCY_6WS = FLASH_ACR_LATENCY_6WS,
    RCC_FLASH_LATENCY_7WS = FLASH_ACR_LATENCY_7WS
} RCC_FlashLatency_t;

typedef uint8_t RCC_FlashLatencyConfig_t;

typedef struct {
    RCC_SysClkSource_t SysClkSource;       /* SYSCLK source: HSI, HSE, or PLL */
    RCC_PLL_Config_t PLL_Config;           /* PLL settings, only used when SysClkSource is PLL */
    RCC_AHBPrescaler_t AHB_Prescaler;      /* AHB bus (HCLK) prescaler */
    RCC_APBPrescaler_t APB1_Prescaler;     /* APB1 bus (PCLK1) prescaler, PCLK1 max 42 MHz */
    RCC_APBPrescaler_t APB2_Prescaler;     /* APB2 bus (PCLK2) prescaler, PCLK2 max 84 MHz */
    RCC_FlashLatencyConfig_t FlashLatency;  /* 0 = auto, non-zero = override */
    uint32_t Timeout;                      /* 0 = RCC_TIMEOUT_DEFAULT */
} RCC_ClkInit_t;

/* MCO1 clock source, RCC_CFGR MCO1 field [22:21] (output on PA8) */
typedef enum {
    RCC_MCO1_SRC_HSI = 0,
    RCC_MCO1_SRC_LSE = 1,
    RCC_MCO1_SRC_HSE = 2,
    RCC_MCO1_SRC_PLL = 3
} RCC_MCO1Source_t;

/* MCO2 clock source, RCC_CFGR MCO2 field [31:30] (output on PC9) */
typedef enum {
    RCC_MCO2_SRC_SYSCLK  = 0,
    RCC_MCO2_SRC_PLLI2S  = 1,
    RCC_MCO2_SRC_HSE     = 2,
    RCC_MCO2_SRC_PLL     = 3
} RCC_MCO2Source_t;

/* MCO output prescaler, shared encoding for MCO1PRE [26:24] and MCO2PRE [29:27] */
typedef enum {
    RCC_MCO_DIV1 = 0,   /* 0xx: no division */
    RCC_MCO_DIV2 = 4,
    RCC_MCO_DIV3 = 5,
    RCC_MCO_DIV4 = 6,
    RCC_MCO_DIV5 = 7
} RCC_MCOPrescaler_t;

#define SYSCFG_PCLK_EN() (RCC->APB2ENR |= (1<<14))   /* APB2ENR bit14: enable SYSCFG clock (needed for EXTI port selection) */
#define SYSCFG_PCLK_DI() (RCC->APB2ENR &= ~(1<<14))   /* APB2ENR bit14: disable SYSCFG clock */

#define GPIOA_PCLK_EN() (RCC->AHB1ENR |= (1<<0))      /* AHB1ENR bit0: enable GPIOA clock */
#define GPIOB_PCLK_EN() (RCC->AHB1ENR |= (1<<1))      /* AHB1ENR bit1: enable GPIOB clock */
#define GPIOC_PCLK_EN() (RCC->AHB1ENR |= (1<<2))      /* AHB1ENR bit2: enable GPIOC clock */
#define GPIOD_PCLK_EN() (RCC->AHB1ENR |= (1<<3))      /* AHB1ENR bit3: enable GPIOD clock */
#define GPIOE_PCLK_EN() (RCC->AHB1ENR |= (1<<4))      /* AHB1ENR bit4: enable GPIOE clock */
#define GPIOF_PCLK_EN() (RCC->AHB1ENR |= (1<<5))      /* AHB1ENR bit5: enable GPIOF clock */
#define GPIOG_PCLK_EN() (RCC->AHB1ENR |= (1<<6))      /* AHB1ENR bit6: enable GPIOG clock */
#define GPIOH_PCLK_EN() (RCC->AHB1ENR |= (1<<7))      /* AHB1ENR bit7: enable GPIOH clock */
#define GPIOI_PCLK_EN() (RCC->AHB1ENR |= (1<<8))      /* AHB1ENR bit8: enable GPIOI clock */

#define GPIOA_PCLK_DI() (RCC->AHB1ENR &= ~(1<<0))     /* AHB1ENR bit0: disable GPIOA clock */
#define GPIOB_PCLK_DI() (RCC->AHB1ENR &= ~(1<<1))     /* AHB1ENR bit1: disable GPIOB clock */
#define GPIOC_PCLK_DI() (RCC->AHB1ENR &= ~(1<<2))     /* AHB1ENR bit2: disable GPIOC clock */
#define GPIOD_PCLK_DI() (RCC->AHB1ENR &= ~(1<<3))     /* AHB1ENR bit3: disable GPIOD clock */
#define GPIOE_PCLK_DI() (RCC->AHB1ENR &= ~(1<<4))     /* AHB1ENR bit4: disable GPIOE clock */
#define GPIOF_PCLK_DI() (RCC->AHB1ENR &= ~(1<<5))     /* AHB1ENR bit5: disable GPIOF clock */
#define GPIOG_PCLK_DI() (RCC->AHB1ENR &= ~(1<<6))     /* AHB1ENR bit6: disable GPIOG clock */
#define GPIOH_PCLK_DI() (RCC->AHB1ENR &= ~(1<<7))     /* AHB1ENR bit7: disable GPIOH clock */
#define GPIOI_PCLK_DI() (RCC->AHB1ENR &= ~(1<<8))     /* AHB1ENR bit8: disable GPIOI clock */

#define GPIOA_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<0); RCC->AHB1RSTR &=~(1<<0);}while(0)  /* AHB1RSTR bit0: pulse-reset GPIOA */
#define GPIOB_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<1); RCC->AHB1RSTR &=~(1<<1);}while(0)  /* AHB1RSTR bit1: pulse-reset GPIOB */
#define GPIOC_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<2); RCC->AHB1RSTR &=~(1<<2);}while(0)  /* AHB1RSTR bit2: pulse-reset GPIOC */
#define GPIOD_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<3); RCC->AHB1RSTR &=~(1<<3);}while(0)  /* AHB1RSTR bit3: pulse-reset GPIOD */
#define GPIOE_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<4); RCC->AHB1RSTR &=~(1<<4);}while(0)  /* AHB1RSTR bit4: pulse-reset GPIOE */
#define GPIOF_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<5); RCC->AHB1RSTR &=~(1<<5);}while(0)  /* AHB1RSTR bit5: pulse-reset GPIOF */
#define GPIOG_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<6); RCC->AHB1RSTR &=~(1<<6);}while(0)  /* AHB1RSTR bit6: pulse-reset GPIOG */
#define GPIOH_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<7); RCC->AHB1RSTR &=~(1<<7);}while(0)  /* AHB1RSTR bit7: pulse-reset GPIOH */
#define GPIOI_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<8); RCC->AHB1RSTR &=~(1<<8);}while(0)  /* AHB1RSTR bit8: pulse-reset GPIOI */

#define TIMER1_CLK_EN() (RCC->APB2ENR |= (1<<0))      /* APB2ENR bit0: enable TIM1 clock */

#define USART1_PCLK_EN() (RCC->APB2ENR |= (1<<4))     /* APB2ENR bit4: enable USART1 clock */
#define USART2_PCLK_EN() (RCC->APB1ENR |= (1<<17))    /* APB1ENR bit17: enable USART2 clock */
#define USART3_PCLK_EN() (RCC->APB1ENR |= (1<<18))    /* APB1ENR bit18: enable USART3 clock */

#define USART1_PCLK_DI() (RCC->APB2ENR &= ~(1<<4))    /* APB2ENR bit4: disable USART1 clock */
#define USART2_PCLK_DI() (RCC->APB1ENR &= ~(1<<17))   /* APB1ENR bit17: disable USART2 clock */
#define USART3_PCLK_DI() (RCC->APB1ENR &= ~(1<<18))   /* APB1ENR bit18: disable USART3 clock */

#define USART1_PCLK_RESET() do{RCC->APB2RSTR |= (1<<4); RCC->APB2RSTR &= ~(1<<4);}while(0)      /* APB2RSTR bit4: pulse-reset USART1 */
#define USART2_PCLK_RESET() do{RCC->APB1RSTR |= (1<<17); RCC->APB1RSTR &= ~(1<<17);}while(0)    /* APB1RSTR bit17: pulse-reset USART2 */
#define USART3_PCLK_RESET() do{RCC->APB1RSTR |= (1<<18); RCC->APB1RSTR &= ~(1<<18);}while(0)    /* APB1RSTR bit18: pulse-reset USART3 */

#define I2C1_PCLK_EN() (RCC->APB1ENR |= (1<<21))      /* APB1ENR bit21: enable I2C1 clock */
#define I2C2_PCLK_EN() (RCC->APB1ENR |= (1<<22))      /* APB1ENR bit22: enable I2C2 clock */
#define I2C3_PCLK_EN() (RCC->APB1ENR |= (1<<23))      /* APB1ENR bit23: enable I2C3 clock */

#define I2C1_PCLK_DI() (RCC->APB1ENR &= ~(1<<21))     /* APB1ENR bit21: disable I2C1 clock */
#define I2C2_PCLK_DI() (RCC->APB1ENR &= ~(1<<22))     /* APB1ENR bit22: disable I2C2 clock */
#define I2C3_PCLK_DI() (RCC->APB1ENR &= ~(1<<23))     /* APB1ENR bit23: disable I2C3 clock */

#define I2C1_PCLK_RESET() do{RCC->APB1RSTR |= (1<<21); RCC->APB1RSTR &= ~(1<<21);}while(0)  /* APB1RSTR bit21: pulse-reset I2C1 */
#define I2C2_PCLK_RESET() do{RCC->APB1RSTR |= (1<<22); RCC->APB1RSTR &= ~(1<<22);}while(0)  /* APB1RSTR bit22: pulse-reset I2C2 */
#define I2C3_PCLK_RESET() do{RCC->APB1RSTR |= (1<<23); RCC->APB1RSTR &= ~(1<<23);}while(0)  /* APB1RSTR bit23: pulse-reset I2C3 */

#define SPI1_PCLK_EN() (RCC->APB2ENR |=(1<<12))       /* APB2ENR bit12: enable SPI1 clock */
#define SPI2_PCLK_EN() (RCC->APB1ENR |=(1<<14))       /* APB1ENR bit14: enable SPI2 clock */
#define SPI3_PCLK_EN() (RCC->APB1ENR |=(1<<15))       /* APB1ENR bit15: enable SPI3 clock */

#define SPI1_PCLK_DI() (RCC->APB2ENR &=~(1<<12))      /* APB2ENR bit12: disable SPI1 clock */
#define SPI2_PCLK_DI() (RCC->APB1ENR &=~(1<<14))      /* APB1ENR bit14: disable SPI2 clock */
#define SPI3_PCLK_DI() (RCC->APB1ENR &=~(1<<15))      /* APB1ENR bit15: disable SPI3 clock */

#define SPI1_PCLK_RESET() do{RCC->APB2RSTR |=(1<<12); RCC->APB2RSTR &=~(1<<12);}while(0)  /* APB2RSTR bit12: pulse-reset SPI1 */
#define SPI2_PCLK_RESET() do{RCC->APB1RSTR |=(1<<14); RCC->APB1RSTR &=~(1<<14);}while(0)  /* APB1RSTR bit14: pulse-reset SPI2 */
#define SPI3_PCLK_RESET() do{RCC->APB1RSTR |=(1<<15); RCC->APB1RSTR &=~(1<<15);}while(0)  /* APB1RSTR bit15: pulse-reset SPI3 */

RCC_Status_t RCC_HSI_Enable(uint32_t timeout);
RCC_Status_t RCC_HSE_Enable(uint32_t timeout);
RCC_Status_t RCC_PLL_Config(const RCC_PLL_Config_t *pPLLConfig);
RCC_Status_t RCC_ClockInit(const RCC_ClkInit_t *pClkInit);

uint32_t RCC_GetSysClockFreq(void);
uint32_t RCC_GetHCLKFreq(void);
uint32_t RCC_GetPCLK1Freq(void);
uint32_t RCC_GetPCLK2Freq(void);
uint32_t RCC_GetPLLOutputClock(void);
RCC_FlashLatency_t RCC_GetFlashLatency(uint32_t hclk);

void RCC_MCO1_Config(RCC_MCO1Source_t source, RCC_MCOPrescaler_t prescaler);
void RCC_MCO2_Config(RCC_MCO2Source_t source, RCC_MCOPrescaler_t prescaler);

extern RCC_ClkInit_t clk;

/* Default clock/MCO setup, weak so applications can override per project. */
__weak void SystemClock_Config(void);
__weak void MX_MCO2_Init(void);

#endif
