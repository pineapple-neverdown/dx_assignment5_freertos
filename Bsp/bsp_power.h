//
// Created by cookie on 2026/11/5.
//

#ifndef DX_ASSIGNMENT5_FREERTOS_BSP_POWER_H
#define DX_ASSIGNMENT5_FREERTOS_BSP_POWER_H

#include "stdint.h"

typedef struct
{
    float chassis_power;
    float buffer_energy;
    int16_t raw_power;
    int16_t raw_energy;
}power_data_t;

#ifdef __cplusplus
extern "C" {
#endif

extern power_data_t power_data;

void Power_Init(void);

#ifdef __cplusplus
}
#endif

#endif //DX_ASSIGNMENT5_FREERTOS_BSP_POWER_H
