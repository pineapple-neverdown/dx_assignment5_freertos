//
// Created by cookie on 2026/11/6.
//

#include "motor_task.h"
#include "DJI_motor_driver.h"
#include "FreeRTOS.h"
#include "task.h"
#include "math.h"

#define MOTOR_ID 5
#define SPEED_FREQUENCY 0.5
#define SPEED_RPM 300.0
#define PI 3.14159265358979323846

extern "C" void motor_task(void *argument)
{
    (void)argument;
    static DJI_motor motor(&hcan1,nullptr,MOTOR_ID,DJI_M3508,0);

    motor.motor_control(DJI_MOTOR_CLEAR_PID);
    motor.motor_reset();

    const float w=2*PI*SPEED_FREQUENCY;
    const float location=SPEED_RPM/(60.0*w);

    float t=0.0;
    TickType_t xLastWakeTime=xTaskGetTickCount();
    for (;;)
    {
        float round=location*(1.0-cosf(w*t));
        motor.motor_set_rounds(round);
        t+=0.001;
        vTaskDelayUntil(&xLastWakeTime,pdMS_TO_TICKS(1));
    }
}
