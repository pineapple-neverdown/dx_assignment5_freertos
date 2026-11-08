//
// Created by cookie on 2026/10/31.
//

#ifndef DX_ASSIGNMENT5_FREERTOS_BSP_RC_H
#define DX_ASSIGNMENT5_FREERTOS_BSP_RC_H

#include "stdint.h"

typedef struct
{
    uint16_t ch0,ch1,ch2,ch3;
    uint8_t s1;
    uint8_t s2;
    int16_t mouse_x,mouse_y,mouse_z;
    uint8_t mouse_l,mouse_r;
    uint16_t key;
}RC_Ctl_t;

extern RC_Ctl_t RC_Ctl;

void RC_Init(void);
void RC_Unpack(void);

#endif //DX_ASSIGNMENT5_FREERTOS_BSP_RC_H
