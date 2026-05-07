#ifndef _RCC_H_
#define _RCC_H_

#include "system.h"
#include "gpio.h"
#include "SYSCFG.h"



#define SYSCFG_PCLK_EN() (RCC->AHB2ENR &= ~(1<<14))
#define SYSCFG_PCLK_DI() (RCC->AHB2ENR &= ~(1<<14))

// GPIO clock
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

//GPIO reset 
#define GPIOA_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<0); RCC->AHB1RSTR &=~(1<<0);}while(0)
#define GPIOB_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<1); RCC->AHB1RSTR &=~(1<<1);}while(0)
#define GPIOC_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<2); RCC->AHB1RSTR &=~(1<<2);}while(0)
#define GPIOD_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<3); RCC->AHB1RSTR &=~(1<<3);}while(0)
#define GPIOE_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<4); RCC->AHB1RSTR &=~(1<<4);}while(0)
#define GPIOF_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<5); RCC->AHB1RSTR &=~(1<<5);}while(0)
#define GPIOG_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<6); RCC->AHB1RSTR &=~(1<<6);}while(0)
#define GPIOH_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<7); RCC->AHB1RSTR &=~(1<<7);}while(0)
#define GPIOI_PCLK_RESET() do{RCC->AHB1RSTR |=(1<<8); RCC->AHB1RSTR &=~(1<<8);}while(0)

//Timer
#define TIMER1_CLK_EN() (RCC->APB2ENR |= (1<<0))

//SPI clock
#define SPI1_PCLK_EN() (RCC->APB2ENR |=(1<<12))
#define SPI2_PCLK_EN() (RCC->APB1ENR |=(1<<14))
#define SPI3_PCLK_EN() (RCC->APB1ENR |=(1<<15))

#define SPI1_PCLK_DI() (RCC->APB2ENR &=~(1<<12))
#define SPI2_PCLK_DI() (RCC->APB1ENR &=~(1<<14))
#define SPI3_PCLK_DI() (RCC->APB1ENR &=~(1<<15))

//SPI reset 
#define SPI1_PCLK_RESET() do{RCC->APB2RSTR |=(1<<12); RCC->APB2RSTR &=~(1<<12);}while(0)
#define SPI2_PCLK_RESET() do{RCC->APB1RSTR |=(1<<12); RCC->APB1RSTR &=~(1<<14);}while(0)
#define SPI3_PCLK_RESET() do{RCC->APB1RSTR |=(1<<12); RCC->APB1RSTR &=~(1<<15);}while(0)




void rcc_init(void);

#endif
