//
// Created by cookie on 2026/10/13.
//

#ifndef GIMBAL_BOARD_BSP_PWM_H
#define GIMBAL_BOARD_BSP_PWM_H

#include "stdint.h"
#include "tim.h"

void TIM_Set_PWM(TIM_HandleTypeDef *tim_pwmHandle, uint8_t Channel, uint16_t value);

#endif //GIMBAL_BOARD_BSP_PWM_H
