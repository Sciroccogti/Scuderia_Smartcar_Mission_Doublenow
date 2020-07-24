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

/****************全局变量定义******************/
uint8 Flag_Stop = OFF;    //=OFF停车
uint8 Flag_Debuge = OFF;  //=ON进入调参界面

void CSI_IRQHandler(void) {
    CSI_DriverIRQHandler();  //调用SDK自带的中断函数
                             //这个函数最后会调用我们设置的回调函数
    __DSB();  //数据同步隔离
}

void PIT_IRQHandler(void) {
    if (PIT_FLAG_GET(PIT_CH0)) {
        PIT_FLAG_CLEAR(PIT_CH0);
        static uint16 j = 0;
        // GPIO_Init(LED_G,GPO,0);
        // static int STOPi = 3000;
        // if (!STOPi) {
        //     if (!gpio_get(I0)) Flag_Stop = OFF;
        // } else
        //     STOPi--;

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

// 中断函数名称，用于设置对应功能的中断函数
// Sample usage:当前启用了周期定时器中断
/*
void PIT_IRQHandler(void)
{

    //标志变量定义

    static uint16 j = 0;
        //GPIO_Init(LED_G,GPO,0);
        static int STOPi = 3000;
    if(!STOPi)
        {
          if(!gpio_get(I0))
            Flag_Stop=OFF;
        }
        else
          STOPi--;


        //20ms一次速度控制
    j++;
    if(j >= 4)
        {
          j = 0;
          SpeedControl();
    }

    DirectionControl();	//方向控制

        PWMOut();
            //最终PWM输出

    //务必清除标志位
    __DSB();
}
*/
// 记得进入中断后清除标志位

//李的程序中test部分扔了