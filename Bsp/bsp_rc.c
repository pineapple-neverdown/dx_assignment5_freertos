//
// Created by cookie on 2026/10/31.
//

#include "bsp_rc.h"
#include "usart.h"
#include "main.h"

RC_Ctl_t RC_Ctl;

extern DMA_HandleTypeDef hdma_usart3_rx;

#define RC_FRAME_SIZE 18
static uint8_t rc_buf[RC_FRAME_SIZE];

void RC_Init(void)
{
    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rc_buf, RC_FRAME_SIZE);
    __HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);
}

void RC_Unpack(void)
{
    RC_Ctl.ch0=((uint16_t)rc_buf[0]|((uint16_t)rc_buf[1]<<8))&0x07FF;
    RC_Ctl.ch1=(((uint16_t)rc_buf[1])>>3|((uint16_t)rc_buf[2]<<5))&0x07FF;
    RC_Ctl.ch2=(((uint16_t)rc_buf[2]>>6)|((uint16_t)rc_buf[3]<<2)|((uint16_t)rc_buf[4]<<10))&0x07FF;
    RC_Ctl.ch3=(((uint16_t)rc_buf[4]>>1)|((uint16_t)rc_buf[5]<<7))&0x07FF;
    RC_Ctl.s1=(rc_buf[5]>>4)&0x03;
    RC_Ctl.s2=(rc_buf[5]>>6)&0x03;

    RC_Ctl.mouse_x=(int16_t)(rc_buf[6]|((uint16_t)rc_buf[7]<<8));
    RC_Ctl.mouse_y=(int16_t)(rc_buf[8]|((uint16_t)rc_buf[9]<<8));
    RC_Ctl.mouse_z=(int16_t)(rc_buf[10]|((uint16_t)rc_buf[11]<<8));
    RC_Ctl.mouse_l=rc_buf[12];
    RC_Ctl.mouse_r=rc_buf[13];
    RC_Ctl.key=(uint16_t)(rc_buf[14]|((uint16_t)rc_buf[15]<<8));
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart,uint16_t Size)
{
    if (huart->Instance == USART3)
    {
        if (Size==RC_FRAME_SIZE)
        {
            RC_Unpack();
        }
        RC_Init();
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART3) {
        __HAL_UART_CLEAR_OREFLAG(huart);
        __HAL_UART_CLEAR_FEFLAG(huart);
        __HAL_UART_CLEAR_NEFLAG(huart);
        __HAL_UART_CLEAR_PEFLAG(huart);
        huart->ErrorCode = HAL_UART_ERROR_NONE;
        RC_Init();
    }
}