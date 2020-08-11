/*********************************************************************************************************************
 *
 * @file       		direction.c
 *  				方向控制
 * @core			S9KEA128
 * @date       		2018
 ********************************************************************************************************************/
#include "myheader.h"

/**********全局变量定义********/
// 方向偏差
//（g_fDirectionError[0]为一对水平电感的差比和偏差）
//（g_fDirectionError[1]为一对垂直电感的差比和偏差）
float g_fDirectionError[2];

// 方向偏差微分
//（g_fDirectionError_dot[0]为一对水平电感的差比和偏差微分）
//（g_fDirectionError_dot[1]为一对垂直电感的差比和偏差微分）
float g_fDirectionError_dot[2];
float g_fDirectionControlOut;      //方向控制输出
int16 g_ValueOfAD[4] = {0};        //获取的电感值
int16 g_ValueOfADFilter[4] = {0};  //阶梯滤波的电感值（未使用）
uint8 Flag_Round = OFF;  //进入环岛的标志（在环岛里为ON）
uint8 Leave = OFF;       //出岛标志(出岛为ON)
float TurnTime = 0;      //进岛转向时间
float FreezingTime = 0;  //进岛判定冻结时间
float DownTime = 100;    //下坡时间
int DownFlagI = 0;
uint8 garage_count = 0;  // 出车库计数器

//以下为可能需要调整的参数

float g_dirControl_P;     //方向控制P
float g_dirControl_D;     //方向控制D
float Turn_dirControl_P;  //进岛方向控制P
float Turn_dirControl_D;  //进岛方向控制D

float TurnTimeDuring;  //转向时间常量，若要修改转向时间，就修改这个
float FreezingTimeDuring;  //冻结时间常量
float DownTimeDuring;      //下坡时间常量

// 水平左右，垂直左右电感，判断是否到达环岛的阈值
int16 TurnAD0 = 2000, TurnAD1 = 2000, TurnAD2 = 1200, TurnAD3 = 1200;

// 离开环岛的阈值放松
int16 LeaveAD0 = 1300, LeaveAD1 = 1300, LeaveAD2 = 1000, LeaveAD3 = 1000;

// 下坡判定电感值
int16 DownAD0 = 2000, DownAD1 = 2000, DownAD2 = 1000, DownAD3 = 1000;

// 车库电感2,3之和
int16 GarageAD23 = 1500;
// 车库电感0,1
int16 GarageAD0 =1000, GarageAD1 = 1000;

// 受环境影响的电感系数  把左右水平电感控制在 800左右（参考）
float Environment = 0.9;

/**
 * @file		方向控制
 *				一般情况下：用两水平电感的差比和作为偏差
 *				在环岛时中：用量垂直电感的差比和作为偏差
 *
 *									电感值对应变量
 *
 *				g_ValueOfAD[0] (水平左电感)
 *              g_ValueOfAD[1]（水平右电感）
 *				g_ValueOfAD[2]（水平中电感）
 *
 * @date		2018
 */
void DirectionControl(void) {
    static float g_fDirectionErrorTemp[2][5];

    Read_ADC();  //获取电感值

    if (g_ValueOfAD[0] < 300 && g_ValueOfAD[1] < 300 && garage_count > 1)
        Flag_Stop = OFF;  //冲出赛道停车保护

    // 以下为出车库处理
    if ((g_ValueOfAD[2] + g_ValueOfAD[3] < GarageAD23) &&
        (g_ValueOfAD[2] + g_ValueOfAD[3] > 25) &&
        !garage_count)  //到达电感阈值且未出车库，开始转向
    {
        garage_count++;
        gpio_set(C14, 1);  // 黄灯亮
    }

    if ((g_ValueOfAD[0] > GarageAD0 && g_ValueOfAD[1] > GarageAD1) &&
        garage_count == 1)  //到达电感阈值且已出车库，结束转向
    {
        garage_count++;
        gpio_set(C14, 0);  // 黄灯灭
    }

    g_ValueOfAD[0] =
        (g_ValueOfAD[0] < 10 ? 10 : g_ValueOfAD[0]);  //四个电感值限幅
    g_ValueOfAD[1] = (g_ValueOfAD[1] < 10 ? 10 : g_ValueOfAD[1]);
    g_ValueOfAD[2] = (g_ValueOfAD[2] < 10 ? 10 : g_ValueOfAD[2]);
    // g_ValueOfAD[3]*=1.4;
    g_ValueOfAD[3] = (g_ValueOfAD[3] < 10 ? 10 : g_ValueOfAD[3]);
    for (int ADi = 0; ADi < 4; ADi++) g_ValueOfAD[ADi] *= Environment;

    g_fDirectionError[0] =
        (float)(g_ValueOfAD[0] - g_ValueOfAD[1]) /
        (g_ValueOfAD[0] + g_ValueOfAD[1]);  //水平电感的差比和作为偏差
    g_fDirectionError[0] =
        (g_fDirectionError[0] >= 1 ? 1 : g_fDirectionError[0]);  //偏差限幅
    g_fDirectionError[0] =
        (g_fDirectionError[0] <= -1 ? -1 : g_fDirectionError[0]);

    g_fDirectionError[1] =
        (float)(g_ValueOfAD[2] - g_ValueOfAD[3]) /
        (g_ValueOfAD[2] + g_ValueOfAD[3]);  //垂直电感的差比和作为偏差
    g_fDirectionError[1] =
        (g_fDirectionError[1] >= 1 ? 1 : g_fDirectionError[1]);  //偏差限幅
    g_fDirectionError[1] =
        (g_fDirectionError[1] <= -1 ? -1 : g_fDirectionError[1]);

    g_fDirectionErrorTemp[0][4] = g_fDirectionErrorTemp[0][3];
    g_fDirectionErrorTemp[0][3] = g_fDirectionErrorTemp[0][2];
    g_fDirectionErrorTemp[0][2] = g_fDirectionErrorTemp[0][1];
    g_fDirectionErrorTemp[0][1] = g_fDirectionErrorTemp[0][0];
    g_fDirectionErrorTemp[0][0] = g_fDirectionError[0];
    g_fDirectionError_dot[0] =
        5 * (g_fDirectionErrorTemp[0][0] -
             g_fDirectionErrorTemp[0][3]);  //水平电感的偏差微分
    g_fDirectionError_dot[0] = (g_fDirectionError_dot[0] > 0.7
                                    ? 0.7
                                    : g_fDirectionError_dot[0]);  //偏差微分限幅
    g_fDirectionError_dot[0] =
        (g_fDirectionError_dot[0] < -0.7 ? -0.7 : g_fDirectionError_dot[0]);

    g_fDirectionErrorTemp[1][4] = g_fDirectionErrorTemp[1][3];
    g_fDirectionErrorTemp[1][3] = g_fDirectionErrorTemp[1][2];
    g_fDirectionErrorTemp[1][2] = g_fDirectionErrorTemp[1][1];
    g_fDirectionErrorTemp[1][1] = g_fDirectionErrorTemp[1][0];
    g_fDirectionErrorTemp[1][0] = g_fDirectionError[1];
    g_fDirectionError_dot[1] =
        5 * (g_fDirectionErrorTemp[1][0] -
             g_fDirectionErrorTemp[1][3]);  //垂直电感的偏差微分
    g_fDirectionError_dot[1] = (g_fDirectionError_dot[1] > 0.7
                                    ? 0.7
                                    : g_fDirectionError_dot[1]);  //偏差微分限幅
    g_fDirectionError_dot[1] =
        (g_fDirectionError_dot[1] < -0.7 ? -0.7 : g_fDirectionError_dot[1]);

    //以下为环岛处理
    if ((g_ValueOfAD[0] > TurnAD0) && (g_ValueOfAD[1] > TurnAD1) &&
        ((g_ValueOfAD[2] > TurnAD2) || (g_ValueOfAD[3] > TurnAD3)) &&
        !FreezingTime)  //到达电感阈值且不与上一次判定重复
    {
        if (Leave == OFF)  //离岛标志为off，进岛，亮绿灯，冻结时间
        {
            Flag_Round = ON;
            Leave = ON;
            gpio_set(E6, 1);
            TurnTime = TurnTimeDuring;
            FreezingTime = FreezingTimeDuring;
        }
    } else if ((g_ValueOfAD[0] > LeaveAD0) && (g_ValueOfAD[1] > LeaveAD1) &&
               ((g_ValueOfAD[2] > LeaveAD2) || (g_ValueOfAD[3] > LeaveAD3)) &&
               !FreezingTime) {
        if (Leave ==
            ON)  //离岛标志，亮红灯，不改变方向控制，冻结一次进岛判定时间
        {
            Leave = OFF;
            gpio_set(H0, 1);
            FreezingTime = FreezingTimeDuring;
        }
    }

    if (g_ValueOfAD[0] < DownAD0 && g_ValueOfAD[1] < DownAD1 &&
        g_ValueOfAD[2] > DownAD2 && g_ValueOfAD[3] > DownAD3 && !DownTime &&
        !FreezingTime && (OFF == Leave))  //下坡减速
    {
        DownTime = DownTimeDuring;
    }

    if (DownTime) {
        if (DownFlagI)
            DownFlagI--;
        else {
            DownFlagI = 30;
            gpio_toggle(H0);
        }

        DownTime--;
        if (!DownTime) gpio_set(H0, 0);
    }

    if (FreezingTime)  //冻结时间倒数
    {
        FreezingTime--;
        if (!FreezingTime)  //冻结时间结束，灭灯
        {
            gpio_set(E6, 0);
            gpio_set(H0, 0);
        }
    }

    if (TurnTime)  //转向时间倒数
    {
        TurnTime--;
        if (!TurnTime)  //转向时间结束，Flag倒下
        {
            Flag_Round = OFF;
        }
    }

    //方向算法（位置式PD）
    if (Flag_Round == ON)
        g_fDirectionControlOut =
            (g_fDirectionError[1] * Turn_dirControl_P +
             g_fDirectionError_dot[1] * Turn_dirControl_D);  //依据垂直电感转向
    else
        g_fDirectionControlOut =
            (g_fDirectionError[0] * g_dirControl_P +
             g_fDirectionError_dot[0] * g_dirControl_D);  //依据水平电感转向
}

/**
 * @file		电感信号采集和处理
 * @note
 * @date		2018
 */
void Read_ADC(void) {
    int16 i, j, k, temp;
    int16 ad_valu[4][5], ad_valu1[4], ad_sum[4];
    int16 ValueOfADOld[4], ValueOfADNew[4];

    for (i = 0; i < 5; i++) {
        // ad_valu[0][i] = adc_mean_filter(ADC_1, AD3, 5) * 11046 / 10000;  //
        // 水平左 ad_valu[1][i] = adc_mean_filter(ADC_1, AD5, 5) * 13624 /
        // 10000;  // 水平右
        ad_valu[0][i] =
            adc_mean_filter(ADC_1, AD3, 5) * 10000 / 10000;  // 水平左
        ad_valu[1][i] =
            adc_mean_filter(ADC_1, AD5, 5) * 15000 / 10000;  // 水平右

        ad_valu[2][i] = adc_mean_filter(ADC_1, AD4, 5);  // 垂直左
        ad_valu[3][i] = adc_mean_filter(ADC_1, AD2, 5);  //垂直右
    }
    /*=========================冒泡排序升序==========================*/  //舍弃最大值和最小值
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            for (k = 0; k < 4 - j; k++) {
                if (ad_valu[i][k] >
                    ad_valu[i][k + 1])  //前面的比后面的大  则进行交换
                {
                    temp = ad_valu[i][k + 1];
                    ad_valu[i][k + 1] = ad_valu[i][k];
                    ad_valu[i][k] = temp;
                }
            }
        }
    }
    /*===========================中值滤波=================================*/
    for (i = 0; i < 4; i++)  //求中间三项的和
    {
        ad_sum[i] = ad_valu[i][1] + ad_valu[i][2] + ad_valu[i][3];
        ad_valu1[i] = ad_sum[i] / 3;
    }

    for (i = 0; i < 4; i++)  //将数值中个位数除掉
    {
        g_ValueOfAD[i] = (int16)(ad_valu1[i] / 10 * 10);

        //采集梯度平滑，每次采集最大变化40
        ValueOfADOld[i] = g_ValueOfADFilter[i];
        ValueOfADNew[i] = g_ValueOfAD[i];

        if (ValueOfADNew[i] >= ValueOfADOld[i])
            g_ValueOfADFilter[i] = ((ValueOfADNew[i] - ValueOfADOld[i]) > 50
                                        ? (ValueOfADOld[i] + 50)
                                        : ValueOfADNew[i]);
        else
            g_ValueOfADFilter[i] = ((ValueOfADNew[i] - ValueOfADOld[i]) < -60
                                        ? (ValueOfADOld[i] - 60)
                                        : ValueOfADNew[i]);
    }
}