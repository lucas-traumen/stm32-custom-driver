//#include "rcc.h"
//
//
//void rcc_init()
//{
//    // HSE , M =/8 N=x200 P/2
//    RCC->CR |=(1<<16); // enbale HSE
//    while(((RCC->CR >>17)&1) == 0); // wait HSE ready
//
//    //set M divide
//    RCC->PLLCFGR &= ~(0b111111 << 0);
//    RCC->PLLCFGR |= (8<<0);
//
//    // set N multiple
//    RCC->PLLCFGR &=~(0b111111111 << 6);
//    RCC->PLLCFGR |= (200<<6);
//
//    // set P divide
//    RCC->PLLCFGR &=~(0b11<<16);
//    RCC->PLLCFGR |= (0b00<<16);
//
//    // set PLL source is HSE
//    RCC->PLLCFGR |= (0b1<<22);
//
//    RCC->CR |=(1<<24); // enable PLL
//    while(((RCC->CR >>25) &1)==0); //wait PLL ready
//
//    /*
//         AHB <=100MHz
//         APB1 <=50MHz
//         APB2 <=100MHz
//    */
//   // set APB1 = APB/2
//    RCC->CFGR &= ~(0b100 <<10);
//    RCC->CFGR |=(0b100 <<10);
//
//    uint32_t *FLASH_ACR =(uint32_t*)(FLASH_R_BASE+0x00);
//    *FLASH_ACR |=(3<<0);
//
//    RCC->CFGR |= 0b10 <<0; // select system clock in PLL
//
//}
