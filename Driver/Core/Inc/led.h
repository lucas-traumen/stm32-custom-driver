#ifndef _LED_H_
#define _LED_H_

typedef enum
{
    GREEN_LED = 12,
    ORANGE_LED,
    RED_LED,
    BLUE_LED
}led_num_t;
typedef enum
{
    LED_OFF,
    LED_ON
}led_state_t;

#endif