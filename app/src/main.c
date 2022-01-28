#include "stm8s.h"
#include "__assert__.h"

#define len(arr) sizeof(arr)/sizeof(arr[0])

void delay(uint32_t iterations)
{
    iterations *= 110;

    for(uint32_t i = 0; i < iterations; i++);
}

GPIO_Pin_TypeDef Leds[] = {
    GPIO_PIN_0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
};

int active_index = 0;

void main(void)
{
    GPIO_DeInit;
    GPIO_Init(GPIOB, GPIO_PIN_ALL, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(GPIOE, GPIO_PIN_0, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(GPIOD, GPIO_PIN_5, GPIO_MODE_IN_PU_IT);
    GPIO_Init(GPIOD, GPIO_PIN_6, GPIO_MODE_IN_PU_IT);
    GPIO_WriteLow(GPIOB, Leds[active_index]);

    while(1) {
        if(GPIO_ReadInputPin(GPIOD, GPIO_PIN_5) == RESET) {
            GPIO_WriteReverse(GPIOB, Leds[active_index]);
            delay(10);
            GPIO_WriteReverse(GPIOE, GPIO_PIN_0);
        } else {
            GPIO_WriteLow(GPIOB, Leds[active_index]);
            delay(10);
            GPIO_WriteLow(GPIOE, GPIO_PIN_0);
        }

        if(GPIO_ReadInputPin(GPIOD, GPIO_PIN_6) == RESET) {
            int prev_index = active_index;
            active_index++;

            if(active_index > (len(Leds) - 1)) {
                active_index = 0;
            }

            GPIO_WriteHigh(GPIOB, Leds[prev_index]);
            GPIO_WriteLow(GPIOB, Leds[active_index]);
            GPIO_WriteHigh(GPIOE, GPIO_PIN_0);
        }
        delay(10);
        GPIO_WriteLow(GPIOE, GPIO_PIN_0);
        delay(100);

    }
}


