//
// Created by cookie on 2026/10/31.
//

#include "led_task.h"
#include "cmsis_os.h"

static const uint16_t led_pins[3] = {LED_B_Pin, LED_G_Pin, LED_R_Pin};

void led_task(void * argument)
{
    (void)argument;
    uint8_t i;
    for (i=0; i<3; i++)
    {
        HAL_GPIO_WritePin(GPIOH, led_pins[i], GPIO_PIN_RESET);
    }
    for (;;)
    {
        for (i=0; i<3; i++)
        {
            HAL_GPIO_WritePin(GPIOH, led_pins[i], GPIO_PIN_SET);
            osDelay(LED_FLOW_MS);
            HAL_GPIO_WritePin(GPIOH, led_pins[i], GPIO_PIN_RESET);
        }
    }
}
