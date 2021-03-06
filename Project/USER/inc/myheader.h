#ifndef _MYHEADER_H_
#define _MYHEADER_H_

#include <stdio.h>

#include "RT106X_config.h"
#include "car_init.h"
#include "direction.h"
// #include "flash_param.h"
// #include "global_var.h"
#include "headfile.h"
#include "isr.h"
#include "myoled.h"
#include "speed.h"

//---------------------------------  MY Define  --------------------------------
#define BUZZ I1
#define LED_G G1
#define LED_R G2
#define LED_B G3
#define K1 C5
#define K2 H7
#define K3 H5
#define K4 H2
#define ON 0
#define OFF 1

//---------------------------------  ADC  -------------------------------
// #define AD1 ADC1_CH5_B16 // 中间
#define AD2 ADC1_CH4_B15   // 垂直右
#define AD3 ADC1_CH7_B18   // 水平左
//#define ADM ADC1_CH5_B16 // 中
#define AD4 ADC1_CH6_B17  // 垂直左
#define AD5 ADC1_CH3_B14  // 水平右

#define LMOTOR_F PWM1_MODULE3_CHA_D0 // Left Forward
#define LMOTOR_B PWM1_MODULE3_CHB_D1 // Left Backward
#define RMOTOR_F PWM2_MODULE3_CHB_D3 // Right Forward
#define RMOTOR_B PWM2_MODULE3_CHA_D2 // Right Backward

#define TUNE_AD 0 // 调节电感
#define WAIT 1 // 等待发车
#define IN_GAR 2 // 车库内
#define GAR_TURN 3 // 转出车库
#define OUT_GAR 4 // 已出车库

#endif