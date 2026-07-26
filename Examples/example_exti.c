#include "system.h"

static EXTI_Handle_t hexti0;
static GPIO_Handle_t hgpioa_button;
static GPIO_Handle_t hgpiod_leds;

void System_Clock_Config_100MHz(void)
{
    RCC_PLL_Config_t pll_config;
    RCC_ClkInit_t clk_init;

    RCC_HSE_Enable();

    pll_config.PLL_Source = RCC_PLL_SRC_HSE;
    pll_config.PLL_M = 8;
    pll_config.PLL_N = 200;
    pll_config.PLL_P = RCC_PLL_P_DIV2;
    pll_config.PLL_Q = 4;
    RCC_PLL_Config(&pll_config);

    clk_init.SysClkSource = RCC_SYSCLK_PLL;
    clk_init.PLL_Config = pll_config;
    clk_init.AHB_Prescaler = RCC_AHB_DIV1;
    clk_init.APB1_Prescaler = RCC_APB_DIV2;
    clk_init.APB2_Prescaler = RCC_APB_DIV1;
    clk_init.FlashLatency = 3;
    RCC_ClockInit(&clk_init);
}

void EXTI0_Example_Init(void)
{
    hgpioa_button.pGPIOx = GPIOA;
    hgpioa_button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    hgpioa_button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
    hgpioa_button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_Init(&hgpioa_button);

    SYSCFG_PCLK_EN();
    SYSCFG->EXTICR[0] &= ~(0xF << 0);
    SYSCFG->EXTICR[0] |= (0 << 0);

    hexti0.EXTI_Config.EXTI_Line = 0;
    hexti0.EXTI_Config.EXTI_Trigger = EXTI_TRIGGER_FALLING;
    hexti0.EXTI_Config.EXTI_Mode = EXTI_MODE_INTERRUPT;
    hexti0.EXTI_Config.EXTI_LineCmd = ENABLE;
    EXTI_Init(&hexti0);

    DRV_NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_2);
    DRV_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
    DRV_NVIC_EnableIRQ(EXTI0_IRQn);
}

void GPIO_LED_Init(void)
{
    hgpiod_leds.pGPIOx = GPIOD;
    hgpiod_leds.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    hgpiod_leds.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    hgpiod_leds.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    hgpiod_leds.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;

    hgpiod_leds.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
    GPIO_Init(&hgpiod_leds);
    hgpiod_leds.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    GPIO_Init(&hgpiod_leds);
    hgpiod_leds.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
    GPIO_Init(&hgpiod_leds);
    hgpiod_leds.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
    GPIO_Init(&hgpiod_leds);
}

void EXTI0_Callback(void)
{
    for(volatile uint32_t i = 0; i < 50000; i++);

    if(GPIO_Read_Pin(GPIOA, GPIO_PIN_NO_0) == 0) {
        GPIO_Toggle_Pin(&hgpiod_leds, GPIO_PIN_NO_14);
    }
}
