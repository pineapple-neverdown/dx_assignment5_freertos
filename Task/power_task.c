//
// Created by cookie on 2026/11/5.
//

#include "power_task.h"
#include "bsp_power.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"

void power_task(void *argument)
{
    (void)argument;
    Power_Init();

    TickType_t xLastWakeTime=xTaskGetTickCount();
    for (;;)
    {
        vTaskDelayUntil(&xLastWakeTime,pdMS_TO_TICKS(20));
    }
}
