#ifndef _RCC_DRIVER_H_
#define _RCC_DRIVER_H_

#include "stm32f407xx.h"
#include "stm32f4xx_common.h"

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
    RCC_PLLSource_t PLL_Source;
    uint16_t PLL_M;
    uint16_t PLL_N;
    RCC_PLL_P_Div_t PLL_P;
    uint16_t PLL_Q;
} RCC_PLL_Config_t;

typedef struct {
    RCC_SysClkSource_t SysClkSource;
    RCC_PLL_Config_t PLL_Config;
    RCC_AHBPrescaler_t AHB_Prescaler;
    RCC_APBPrescaler_t APB1_Prescaler;
    RCC_APBPrescaler_t APB2_Prescaler;
    uint8_t FlashLatency;
} RCC_ClkInit_t;

#define SYSCFG_PCLK_EN() (RCC->APB2ENR |= (1<<14))
#define SYSCFG_PCLK_DI() (RCC->APB2ENR &= ~(1<<14))

#define GPIOA_PCLK_EN() (RCC->AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN() (RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN() (RCC->AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN() (RCC->AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN() (RCC->AHB1ENR |= (1<<4))
#define GPIOF_PCLK_EN() (RCC->AHB1ENR |= (1<<5))
#define GPIOG_PCLK_EN() (RCC->AHB1ENR |= (1<<6))
#define GPIOH_PCLK_EN() (RCC->AHB1ENR |= (1<<7))
#define GPIOI_PCLK_EN() (RCC->AHB1ENR |= (1<<8))

#define GPIOA_PCLK_DI() (RCC->AHB1ENR &= ~(1<<0))
#define GPIOB_PCLK_DI() (RCC->AHB1ENR &= ~(1<<1))
#define GPIOC_PCLK_DI() (RCC->AHB1ENR &= ~(1<<2))
#define GPIOD_PCLK_DI() (RCC->AHB1ENR &= ~(1<<3))
#define GPIOE_PCLK_DI() (RCC->AHB1ENR &= ~(1<<4))
#define GPIOF_PCLK_DI() (RCC->AHB1ENR &= ~(1<<5))
#define GPIOG_PCLK_DI() (RCC->AHB1ENR &= ~(1<<6))
#define GPIOH_PCLK_DI() (RCC->AHB1ENR &= ~(1<<7))
#define GPIOI_PCLK_DI() (RCC->AHB1ENR &= ~(1<<8))

#define GPIOA_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<0); RCC->AHB1RSTR &=~(1<<0);}while(0)
#define GPIOB_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<1); RCC->AHB1RSTR &=~(1<<1);}while(0)
#define GPIOC_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<2); RCC->AHB1RSTR &=~(1<<2);}while(0)
#define GPIOD_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<3); RCC->AHB1RSTR &=~(1<<3);}while(0)
#define GPIOE_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<4); RCC->AHB1RSTR &=~(1<<4);}while(0)
#define GPIOF_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<5); RCC->AHB1RSTR &=~(1<<5);}while(0)
#define GPIOG_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<6); RCC->AHB1RSTR &=~(1<<6);}while(0)
#define GPIOH_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<7); RCC->AHB1RSTR &=~(1<<7);}while(0)
#define GPIOI_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<8); RCC->AHB1RSTR &=~(1<<8);}while(0)

#define TIMER1_CLK_EN() (RCC->APB2ENR |= (1<<0))

#define SPI1_PCLK_EN() (RCC->APB2ENR |=(1<<12))
#define SPI2_PCLK_EN() (RCC->APB1ENR |=(1<<14))
#define SPI3_PCLK_EN() (RCC->APB1ENR |=(1<<15))

#define SPI1_PCLK_DI() (RCC->APB2ENR &=~(1<<12))
#define SPI2_PCLK_DI() (RCC->APB1ENR &=~(1<<14))
#define SPI3_PCLK_DI() (RCC->APB1ENR &=~(1<<15))

#define SPI1_PCLK_RESET() do{RCC->APB2RSTR |=(1<<12); RCC->APB2RSTR &=~(1<<12);}while(0)
#define SPI2_PCLK_RESET() do{RCC->APB1RSTR |=(1<<14); RCC->APB1RSTR &=~(1<<14);}while(0)
#define SPI3_PCLK_RESET() do{RCC->APB1RSTR |=(1<<15); RCC->APB1RSTR &=~(1<<15);}while(0)

void RCC_HSE_Config(void);
void RCC_PLL_Config(RCC_PLL_Config_t *pPLLConfig);
void RCC_SysClk_Config(RCC_ClkInit_t *pClkInit);
uint32_t RCC_GetSysClockFreq(void);
uint32_t RCC_GetHCLKFreq(void);
uint32_t RCC_GetPCLK1Freq(void);
uint32_t RCC_GetPCLK2Freq(void);

#endif
