#include "gpio_driver.h"
#include "rcc_driver.h"
#include "exti_driver.h"

GPIO_Handle_t hgpioc = {0};

void GPIO_PeriClockControl(GPIO_TypeDef *pGPIOx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_PCLK_EN();
        }else if (pGPIOx == GPIOB)
        {
            GPIOB_PCLK_EN();
        }else if (pGPIOx == GPIOC)
        {
            GPIOC_PCLK_EN();
        }else if (pGPIOx == GPIOD)
        {
            GPIOD_PCLK_EN();
        }else if (pGPIOx == GPIOE)
        {
            GPIOE_PCLK_EN();
        }else if (pGPIOx == GPIOF)
        {
            GPIOF_PCLK_EN();
        }else if (pGPIOx == GPIOG)
        {
            GPIOG_PCLK_EN();
        }else if (pGPIOx == GPIOH)
        {
            GPIOH_PCLK_EN();
        }else if (pGPIOx == GPIOI)
        {
            GPIOI_PCLK_EN();
        }
    }
    else
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_PCLK_DI();
        }else if (pGPIOx == GPIOB)
        {
            GPIOB_PCLK_DI();
        }else if (pGPIOx == GPIOC)
        {
            GPIOC_PCLK_DI();
        }else if (pGPIOx == GPIOD)
        {
            GPIOD_PCLK_DI();
        }else if (pGPIOx == GPIOE)
        {
            GPIOE_PCLK_DI();
        }else if (pGPIOx == GPIOF)
        {
            GPIOF_PCLK_DI();
        }else if (pGPIOx == GPIOG)
        {
            GPIOG_PCLK_DI();
        }else if (pGPIOx == GPIOH)
        {
            GPIOH_PCLK_DI();
        }else if (pGPIOx == GPIOI)
        {
            GPIOI_PCLK_DI();
        }
    }
}
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint32_t temp=0; //temp. register

    //enable the peripheral clock
    GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

    //1 . configure the mode of gpio pin
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
    {
        //the non interrupt mode
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
        pGPIOHandle->pGPIOx->MODER &= ~( 0x3 << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); 
        pGPIOHandle->pGPIOx->MODER |= temp; 
    }
    else
    {
        //this part will code later . ( interrupt mode)
        if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT )
        {
            //1. configure the FTSR
            EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            //Clear the corresponding RTSR bit
            EXTI->RTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            
        }else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT )
        {
            //1 . configure the RTSR
            EXTI->RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            //Clear the corresponding FTSR bit
            EXTI->FTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            
        }else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT )
        {
            //1. configure both FTSR and RTSR
            EXTI->RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            //Clear the corresponding RTSR bit
            EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }

        //2. configure the GPIO port selection in SYSCFG_EXTICR
        uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
        uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
        uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
        SYSCFG_PCLK_EN();
        SYSCFG->EXTICR[temp1] &= ~(0xF << (temp2 * 4)); //clear the 4-bit field for this line, preserving the other 3 lines in this register
        SYSCFG->EXTICR[temp1] |= (portcode << (temp2 * 4));

        //3 . enable the exti interrupt delivery using IMR (Interrupt mask register)
        EXTI->IMR |= 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
        
    }

    //2. configure the speed
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
    pGPIOHandle->pGPIOx->OSPEEDR &= ~( 0x3 << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
    pGPIOHandle->pGPIOx->OSPEEDR |= temp;

    //3. configure the pupd settings
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
    pGPIOHandle->pGPIOx->PUPDR &= ~( 0x3 << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
    pGPIOHandle->pGPIOx->PUPDR |= temp;

    //4. configure the optype
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
    pGPIOHandle->pGPIOx->OTYPER &= ~( 0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //clearing
    pGPIOHandle->pGPIOx->OTYPER |= temp;

    //5. configure the alt functionality
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
    {
        //configure the alt function registers.
        uint8_t temp1, temp2;

        temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
        temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
        pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << ( 4 * temp2 ) ); //clearing
        pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << ( 4 * temp2 )); 
    }
}
void GPIO_DeInit(GPIO_TypeDef *pGPIOx)
{
    if(pGPIOx == GPIOA)
    {
        GPIOA_PCLK_RESET();
    }else if (pGPIOx == GPIOB)
    {
        GPIOB_PCLK_RESET();
    }else if (pGPIOx == GPIOC)
    {
        GPIOC_PCLK_RESET();
    }else if (pGPIOx == GPIOD)
    {
        GPIOD_PCLK_RESET();
    }else if (pGPIOx == GPIOE)
    {
        GPIOE_PCLK_RESET();
    }else if (pGPIOx == GPIOF)
    {
        GPIOF_PCLK_RESET();
    }else if (pGPIOx == GPIOG)
    {
        GPIOG_PCLK_RESET();
    }else if (pGPIOx == GPIOH)
    {
        GPIOH_PCLK_RESET();
    }else if (pGPIOx == GPIOI)
    {
        GPIOI_PCLK_RESET();
    }
}
void GPIO_Write_Pin(GPIO_Handle_t *pGPIOHandle, uint8_t GPIO_Pin, uint8_t Value)
{
    if(Value == 1)
    {
        pGPIOHandle->pGPIOx->BSRR |= (1 << GPIO_Pin);
    }
    else
    {
        pGPIOHandle->pGPIOx->BSRR |= (1 << (GPIO_Pin + 16));
    }
}
void GPIO_Write_Port(GPIO_Handle_t *pGPIOHandle, uint16_t Value)
{
     pGPIOHandle->pGPIOx->ODR = Value;
}

void GPIO_Toggle_Pin(GPIO_Handle_t *pGPIOHandle,uint8_t GPIO_Pin )
{
    pGPIOHandle->pGPIOx->ODR ^=(1<<(GPIO_Pin));
}
uint8_t GPIO_Read_Pin(GPIO_Handle_t *pGPIOHandle,uint8_t GPIO_Pin )
{
    return ((pGPIOHandle->pGPIOx->IDR >>GPIO_Pin)&1);
}
uint16_t GPIO_Read_Port(GPIO_Handle_t *pGPIOHandle)
{
    return (pGPIOHandle->pGPIOx->IDR);
}

/**
 * @brief Default GPIO setup: PC9 as AF0 push-pull for MCO2 output. Override this weak function per application.
 */
__weak void MX_GPIO_Init(void)
{
    hgpioa = (GPIO_Handle_t){0};
    hgpioa.pGPIOx = GPIOA;
    hgpioa.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
    hgpioa.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    hgpioa.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_Init(&hgpioa);

    hgpiod = (GPIO_Handle_t){0};
    hgpiod.pGPIOx = GPIOD;
    hgpiod.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    hgpiod.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    hgpiod.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    hgpiod.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    hgpiod.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
    GPIO_Init(&hgpiod);
    hgpiod.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
    GPIO_Init(&hgpiod);
}




