//
// Created by cookie on 2026/10/31.
//

#include "rc_task.h"
#include "bsp_rc.h"
#include "cmsis_os.h"
#include "math.h"

#define RC_MID 1024.0f
#define RC_HALF 660.0f
#define RC_DEAD 20.0f

rc_ctrl_t rc_ctrl;

float rc_norm(int16_t raw)
{
    float d=(float)raw-RC_MID;
    if (fabsf(d)<RC_DEAD)
    {
        return 0.0f;
    }
    d/=RC_HALF;
    if (d>1.0f) d=1.0f;
    if (d<-1.0f) d=-1.0f;
    return d;
}

void rc_task(void *argument)
{
    (void) argument;
    RC_Init();
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        uint16_t ch0 = RC_Ctl.ch0;
        uint16_t ch1 = RC_Ctl.ch1;
        uint16_t ch2 = RC_Ctl.ch2;
        uint16_t ch3 = RC_Ctl.ch3;
        uint8_t  s1  = RC_Ctl.s1;
        uint8_t  s2  = RC_Ctl.s2;
        rc_ctrl.yaw   = rc_norm((int16_t)ch0);
        rc_ctrl.pitch      = rc_norm((int16_t)ch1);
        rc_ctrl.chassis_vy = rc_norm((int16_t)ch2);
        rc_ctrl.chassis_vx = rc_norm((int16_t)ch3);
        rc_ctrl.s1 = s1;
        rc_ctrl.s2 = s2;
        rc_ctrl.spin_mode    = (uint8_t)(s1 == 2);
        rc_ctrl.follow_mode  = (uint8_t)(s1 != 2);
        rc_ctrl.shooter = (uint8_t)(s1 == 1);
        rc_ctrl.lifter = (s2 == 1) ? 1 : ((s2 == 2) ? -1 : 0);
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(5));
    }
}