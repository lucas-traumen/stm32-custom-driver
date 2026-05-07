#ifndef _GPIO_H_
#define _GPIO_H_

#include "system.h"



typedef struct
{
    uint8_t GPIO_PinNumber;
    uint8_t GPIO_PinMode;
    uint8_t GPIO_PinSpeed;
    uint8_t GPIO_PinPuPdControl;
    uint8_t GPIO_PinOPType;
    uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;

typedef struct
{
    GPIO_TypeDef *pGPIOx;
    GPIO_PinConfig_t GPIO_PinConfig;
}GPIO_Handle_t;





#define GPIO_PIN_NO_0           0
#define GPIO_PIN_NO_1           1
#define GPIO_PIN_NO_2           2
#define GPIO_PIN_NO_3           3
#define GPIO_PIN_NO_4           4
#define GPIO_PIN_NO_5           5
#define GPIO_PIN_NO_6           6
#define GPIO_PIN_NO_7           7
#define GPIO_PIN_NO_8           8
#define GPIO_PIN_NO_9           9
#define GPIO_PIN_NO_10          10
#define GPIO_PIN_NO_11          11
#define GPIO_PIN_NO_12          12
#define GPIO_PIN_NO_13          13
#define GPIO_PIN_NO_14          14
#define GPIO_PIN_NO_15          15

/*
 * GPIO pin modes
 */
#define GPIO_MODE_IN            0
#define GPIO_MODE_OUT           1
#define GPIO_MODE_ALTFN         2
#define GPIO_MODE_ANALOG        3
#define GPIO_MODE_IT_FT         4
#define GPIO_MODE_IT_RT         5
#define GPIO_MODE_IT_RFT        6

/*
 * GPIO pin possible output speeds
 */
#define GPIO_SPEED_LOW          0
#define GPIO_SPEED_MEDIUM       1
#define GPIO_SPEED_FAST         2
#define GPIO_SPEED_HIGH         3  

/*
 * GPIO pin possible output types
 */
#define GPIO_OP_TYPE_PP         0
#define GPIO_OP_TYPE_OD         1

/*
 * GPIO pin pull up AND pull down
 */
#define GPIO_NO_PUPD            0
#define GPIO_PIN_PU             1
#define GPIO_PIN_PD             2

#define AF0      0
#define AF1      1
#define AF2      2
#define AF3      3
#define AF4      4
#define AF5      5
#define AF6      6
#define AF7      7
#define AF8      8
#define AF9      9
#define AF10     10
#define AF11     11
#define AF12     12
#define AF13     13
#define AF14     14
#define AF15     15

//
#define GPIO_BASEADDR_TO_CODE(x)    (((x)==GPIOA)?0:((x)==GPIOB)?1:((x)==GPIOC)?2:((x)==GPIOD)?3:((x)==GPIOE)?4: \
                                        ((x)==GPIOF)?5:((x)==GPIOG)?6:((x)==GPIOH)?7:((x)==GPIOI)?8:0xFF)

void GPIO_PeriClockControl(GPIO_TypeDef *pGPIOx, uint8_t EnorDi);
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_TypeDef *pGPIOx);
void GPIO_Write_Pin(GPIO_Handle_t *pGPIOHandle,uint8_t GPIO_Pin, uint8_t Value);
void GPIO_Write_Port(GPIO_Handle_t *pGPIOHandle, uint16_t Value);
uint8_t GPIO_Read_Pin(GPIO_Handle_t *pGPIOHandle,uint8_t GPIO_Pin );
uint16_t GPIO_Read_Port(GPIO_Handle_t *pGPIOHandle);
void GPIO_Toggle_Pin(GPIO_Handle_t *pGPIOHandle,uint8_t GPIO_Pin);

#endif


