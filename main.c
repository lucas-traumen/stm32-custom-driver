	//#include "stm32f407xx.h"
	#include "gpio.h"
	#include "rcc.h"
	#include "exti.h"
	#include "spi_driver.h"
	#include "string.h"

	GPIO_Handle_t gpiod;
	GPIO_Handle_t gpioa;
	SPI_Handle_t spi2;
	uint32_t cnt=0;

	void Timer_init()
	{
	#if (TIMER_SRC == TIMER1)
		TIMER1_CLK_EN();
		uint32_t *TIM1_CR1 = (uint32_t*)(TIM1_BASE+0x00);
		uint32_t *TIM1_DIER = (uint32_t*)(TIM1_BASE+0x0C);
		uint32_t *TIM1_CNT = (uint32_t*)(TIM1_BASE+0x24);
		uint32_t *TIM1_PSC = (uint32_t*)(TIM1_BASE+0x28);
		uint32_t *TIM1_ARR = (uint32_t*)(TIM1_BASE+0x2C);
		volatile uint32_t *TIM1_EGR = (volatile uint32_t*)(TIM1_BASE + 0x14);
		//uint32_t *TIM1_RCR = (uint32_t*)(TIM1_BASE+0x30);
		// uint32_t *TIM1_SR = (uint32_t*)(TIM1_BASE+0x10);
		// uint32_t *NVIC_ISER0 = (uint32_t*)(NVIC_ISER_BASE_ADDRESSS);
		// Driver_NVIC_SetPriority(TIM1_UP_TIM10_IRQn,0,0);

		*TIM1_CNT=0;
		*TIM1_PSC=99;
		*TIM1_ARR=0xFFFF;
		*TIM1_EGR |= (1 << 0);
		// *TIM1_CR1=(1<<0);
		// *TIM1_SR &= ~(1 << 0);

		// *TIM1_DIER |=(1<<0);
		// *NVIC_ISER0 |=(1<<25); //enabled interupt TIM1
	#else
		uint32_t *STK_CTRL = (uint32_t*)(SYSTICK_TIMER_ADDRESS+0x00);
		uint32_t *STK_LOAD = (uint32_t*)(SYSTICK_TIMER_ADDRESS+0x04);
		uint32_t *STK_VAL = (uint32_t*)(SYSTICK_TIMER_ADDRESS+0x08);
		*STK_CTRL = 0;
		// 2. Nạp giá trị đếm (cho 1ms với clock 16MHz)
		*STK_LOAD = 15999;
		// 3. Xóa giá trị hiện tại
		*STK_VAL = 0;
		// Bit 2 (CLKSOURCE) = 1 (Processor Clock - AHB)
		// Bit 1 (TICKINT)   = 1 (Enable Interrupt - Nếu muốn dùng ngắt)
		// Bit 0 (ENABLE)    = 1 (Start Counter)

		*STK_CTRL|=(1<<2)|(1<<1)|(1<<0);
	#endif
	}
	// void TIM1_UP_TIM10_IRQHandler()
	// {
	// 	uint32_t *TIM1_SR = (uint32_t*)(TIM1_BASE+0x10);

	// 		*TIM1_SR &=~(1<<0);
			
	// }
	void delay_us(uint32_t us)
	{
	//	uint32_t *TIM1_SR = (uint32_t*)(TIM1_BASE+0x10);
	//	uint32_t *TIM1_CNT = (uint32_t*)(TIM1_BASE+0x24);
	//    *TIM1_CNT = 0;
	//
	//    // Xóa cờ ngắt trước khi chờ
	//	*TIM1_SR &= ~(1 << 0); // Xóa bit UIF
	//
	//	while(((*TIM1_SR>>0)&1)!=1);
	//	*TIM1_SR &=~(1<<0);
	uint32_t *TIM1_CR1 = (uint32_t*)(TIM1_BASE+0x00);
	uint32_t *TIM1_CNT = (uint32_t*)(TIM1_BASE+0x24);
		
		*TIM1_CNT=0;

		*TIM1_CR1 |=(1<<0);
	while((*TIM1_CNT)<us){};

		*TIM1_CR1 &=~ (1<<0);
	}
	void delay_ms(uint32_t ms)
	{
	//	uint32_t *TIM1_SR = (uint32_t*)(TIM1_BASE+0x10);
	//	uint32_t *TIM1_CNT = (uint32_t*)(TIM1_BASE+0x24);
	//    *TIM1_CNT = 0;
	//
	//    // Xóa cờ ngắt trước khi chờ
	//	*TIM1_SR &= ~(1 << 0); // Xóa bit UIF
	//
	//	while(((*TIM1_SR>>0)&1)!=1);
	//	*TIM1_SR &=~(1<<0);
	for(uint32_t i=0;i<ms;i++) delay_us(1000);
		
	}
	void SPI2_Inits()
	{
		spi2.pSPIx=SPI2;
		spi2.SPIConfig.SPI_DeviceMode=SPI_DEVICE_MODE_MASTER;
		spi2.SPIConfig.SPI_BusConfig=SPI_BUS_CONFIG_FD;
		spi2.SPIConfig.SPI_DFF=SPI_DFF_8bits;
		spi2.SPIConfig.SPI_Frame_format=MSB_TRANSMITTED_FIRST;
		spi2.SPIConfig.SPI_SSM=SPI_SSM_EN;
		spi2.SPIConfig.SPI_CPHA=SPI_CPHA_LOW;
		spi2.SPIConfig.SPI_CPOL=SPI_CPOL_LOW;
		spi2.SPIConfig.speed=SPI_SCLK_SPEED_DIV256;
		SPI_Init(&spi2);
	}
	volatile uint8_t flag=0;
	volatile uint8_t flag1=0;
	int main(void) {
		// /* 1. Bật clock cho GPIOD */
		RCC->AHB1ENR |= (1 << 3);     // GPIODEN = bit 3
		gpiod.pGPIOx= GPIOD;
		gpiod.GPIO_PinConfig.GPIO_PinNumber= GPIO_PIN_NO_13;
		gpiod.GPIO_PinConfig.GPIO_PinMode= GPIO_MODE_OUT;
		gpiod.GPIO_PinConfig.GPIO_PinOPType= GPIO_OP_TYPE_PP;
		gpiod.GPIO_PinConfig.GPIO_PinPuPdControl= GPIO_NO_PUPD;
		gpiod.GPIO_PinConfig.GPIO_PinSpeed= GPIO_SPEED_HIGH;
		GPIO_Init(&gpiod);
		gpiod.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
		GPIO_Init(&gpiod);

		// gpiod.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
		// GPIO_Init(&gpiod);

		gpiod.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
		GPIO_Init(&gpiod);

		// gpiod.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
		// GPIO_Init(&gpiod);

		// gpioa.pGPIOx= GPIOA;
		// gpioa.GPIO_PinConfig.GPIO_PinNumber= GPIO_PIN_NO_0;
		// gpioa.GPIO_PinConfig.GPIO_PinMode= GPIO_MODE_IT_FT;
		// gpioa.GPIO_PinConfig.GPIO_PinPuPdControl= GPIO_NO_PUPD;
		// GPIO_Init(&gpioa);

		//rcc_init();
		 Timer_init();
		// NVIC_ICSR(EXTI0_IRQn,ENABLE);
		// Driver_NVIC_SetPriorityGrouping();
		// Driver_NVIC_SetPriority(EXTI0_IRQn,0,0);
		SPI_GpioConfig(SPI2);
		SPI2_Inits();
		SPI_SSI_Config(SPI2,ENABLE);
		SPI_PeripheralControl(SPI2,ENABLE);
		GPIO_Write_Pin(&gpiod,GPIO_PIN_NO_12,SET);
		
		delay_ms(2000);
		while (1) {
		// GPIO_Write_Port(&gpiod,0);

		// gpiod.pGPIOx->ODR ^= (1 << 13); // Toggle LED
				// 	if(flag){
				// 		flag=0;
				// 	  for(int i=3;i>=0;i--)
				//   {
				// 		GPIO_Toggle_Pin(&gpiod,GPIO_PIN_NO_12+i);
						
				// 		delay_ms(1000);
				// 		//GPIOA_PCLK_DI();																			
				// 		//GPIOD_PCLK_DI();
						
				// 	}
					
				//   }
				GPIO_Write_Pin(&gpiod,GPIO_PIN_NO_14,RESET);
		delay_us(50);
			SPI_SendData(SPI2,(uint8_t*)"hello lucas",strlen("hello lucas"));
			delay_us(50);
		GPIO_Write_Pin(&gpiod,GPIO_PIN_NO_13,SET);
		GPIO_Write_Pin(&gpiod,GPIO_PIN_NO_14,SET);
		delay_ms(1000);
			
		}
	}


	void EXTI0_IRQCallback(uint8_t GPIO_PinNumber)
	{
		if(GPIO_PinNumber == GPIO_PIN_NO_0)
		{
			delay_ms(50);
			if(GPIO_Read_Pin(&gpioa,0)){
			flag=1;
			GPIO_Toggle_Pin(&gpiod,GPIO_PIN_NO_13);
			flag1++;
			}
		}
	}

