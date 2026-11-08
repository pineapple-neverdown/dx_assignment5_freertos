//
// Created by cookie on 2026/11/5.
//

#include "bsp_power.h"
#include "CAN_bsp.h"
#include "cmsis_os.h"

#define POWER_CAN_ID 0x31
#define POWER_CAN (&hcan1)

power_data_t power_data;

static void power_rx_callback(can_device_receive *dev,uint8_t *data)
{
    (void)dev;
    power_data.raw_power=(int16_t)((uint16_t)data[1]<<8|data[0]);
    power_data.raw_energy=(int16_t)((uint16_t)data[3]<<8|data[2]);
    power_data.chassis_power=(float)power_data.raw_power*0.1f;
    power_data.buffer_energy=(float)power_data.raw_energy*0.1f;
}

void Power_Init()
{
    static can_device_receive dev(POWER_CAN,POWER_CAN_ID,power_rx_callback);
    (void)dev;
}