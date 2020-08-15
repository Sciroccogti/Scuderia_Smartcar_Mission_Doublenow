/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		isr
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/

#include "myheader.h"
#include "math.h"

/****************全局变量定义******************/
uint8 Flag_Stop = OFF;    //=OFF停车
uint8 Flag_Debuge = OFF;  //=ON进入调参界面
uint16 distance = 6800;	//超声波接收端测得的距离值

uint8 sonic_rx_buffer;
lpuart_transfer_t   sonic_receivexfer;
lpuart_handle_t     sonic_g_lpuartHandle;

uint8 bluetooth_rx_buffer;
lpuart_transfer_t   bluetooth_receivexfer;
lpuart_handle_t     bluetooth_g_lpuartHandle;

// 本文件临时变量
uint8 sonic_temp;
uint8 sonic_data[3] = {0};
uint8 sonic_count = 0;

void CSI_IRQHandler(void) {
    CSI_DriverIRQHandler();  //调用SDK自带的中断函数
                             //这个函数最后会调用我们设置的回调函数
    __DSB();  //数据同步隔离
}

void PIT_IRQHandler(void) {
    if (PIT_FLAG_GET(PIT_CH0)) {
        PIT_FLAG_CLEAR(PIT_CH0);
        static uint16 j = 0;
        static uint8 k = 0;
        // GPIO_Init(LED_G,GPO,0);
        // static int STOPi = 3000;
        // if (!STOPi) {
        //     if (!gpio_get(I0)) Flag_Stop = OFF;
        // } else
        //     STOPi--;
        //Ball release & full stop
        const float ball_height_mm = 120;
        float drop_time = sqrt(2 * ball_height_mm / 10000);
        const float box_length = 50;
        if (distance - 100 < drop_time * g_fRealSpeed - box_length){
            k++;
            gpio_set(D4, 0);
            if(k >= 3){
                Flag_Stop = OFF;
            }
            if(k == 5){
            }
        }

        // 20ms一次速度控制
        j++;
        if (j >= 4) {
            j = 0;
            SpeedControl();
        }

        DirectionControl();  //方向控制

        PWMOut();
        //最终PWM输出
    }

    if (PIT_FLAG_GET(PIT_CH1)) {
        PIT_FLAG_CLEAR(PIT_CH1);
    }

    if (PIT_FLAG_GET(PIT_CH2)) {
        PIT_FLAG_CLEAR(PIT_CH2);
    }

    if (PIT_FLAG_GET(PIT_CH3)) {
        PIT_FLAG_CLEAR(PIT_CH3);
    }

    __DSB();
}

void sonic_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    if(kStatus_LPUART_RxIdle == status)
    {
        //数据已经被写入到了 之前返回的BUFF中
        //本例程使用的BUFF为 example_rx_buffer
        sonic_temp = sonic_rx_buffer;//将数据取出
		
		if(sonic_count == 3)					//接收完成，开始处理数据
		{
			sonic_count = 0;
			distance = sonic_data[1]<<8 | sonic_data[2];	//得到超声波模块测出的距离
		}
		if(sonic_count != 0)
		{
			sonic_data[sonic_count] = sonic_temp;
			sonic_count ++;
		}
		if(sonic_temp == 0xa5)
		{
			sonic_count ++;
		}
    }
    
    handle->rxDataSize = sonic_receivexfer.dataSize;  //还原缓冲区长度
    handle->rxData = sonic_receivexfer.data;          //还原缓冲区地址
}

void bluetooth_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData){
    if(kStatus_LPUART_RxIdle == status){
        // char bt[10];
        // sprintf(bt, "bt:%d", (int)bluetooth_rx_buffer);
        // lcd_showstr(0, 7, bt);
    }
    handle->rxDataSize = bluetooth_receivexfer.dataSize;  //还原缓冲区长度
    handle->rxData = bluetooth_receivexfer.data;          //还原缓冲区地址
}

void GPIO2_Combined_16_31_IRQHandler(void) {
    if (GET_GPIO_FLAG(C16)) {
        CLEAR_GPIO_FLAG(C16);  //清除中断标志位
    }
}

void GPIO2_Combined_0_15_IRQHandler(void) {
    if (GET_GPIO_FLAG(MT9V03X_VSYNC_PIN)) {
        //不用清除标志位，标志位在mt9v03x_vsync函数内部会清除
        if (1 == flexio_camera_type) mt9v03x_vsync();
    }
    if (GET_GPIO_FLAG(SCC8660_VSYNC_PIN)) {
        //不用清除标志位，标志位在scc8660_vsync函数内部会清除
        if (2 == flexio_camera_type) scc8660_vsync();
    }
}

/*
GPIO3_Combined_0_15_IRQHandler
此中断函数默认被SD卡检测插入功能占用，如果需要gpio中断建议使用其他IO
或者不使用SD的卡可以将fsl_sdmmc_host.c中的
SDMMCHOST_CARD_DETECT_GPIO_INTERRUPT_HANDLER函数注释掉即可

*/