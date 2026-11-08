//
// Created by cookie on 2026/10/31.
//

#ifndef DX_ASSIGNMENT5_FREERTOS_RC_TASK_H
#define DX_ASSIGNMENT5_FREERTOS_RC_TASK_H

#include "stdint.h"

typedef struct
{
    float yaw,pitch,chassis_vy,chassis_vx;
    uint8_t s1,s2;
    uint8_t spin_mode,follow_mode,shooter;
    int8_t lifter;
}rc_ctrl_t;

extern rc_ctrl_t rc_ctrl;

void rc_task(void *argument);
float rc_norm(int16_t raw);

#endif //DX_ASSIGNMENT5_FREERTOS_RC_TASK_H
