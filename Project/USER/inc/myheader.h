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
// #define AD3 ADC1_CH2_B13   // 水平左
#define AD3 ADC1_CH5_B16 // 飞线水平左
#define AD4 ADC1_CH1_B12  // 垂直左
#define AD5 ADC1_CH3_B14  // 水平右

#define LMOTOR_F PWM1_MODULE3_CHA_D0 // Left Forward
#define LMOTOR_B PWM1_MODULE3_CHB_D1 // Left Backward
#define RMOTOR_F PWM2_MODULE3_CHA_D2 // Right Forward
#define RMOTOR_B PWM2_MODULE3_CHB_D3 // Right Backward


#endif