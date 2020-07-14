#include "direction.h"
#include "flash_param.h"
#include "global_var.h"
#include "isr.h"
#include "myoled.h"
#include "RT106X_config.h"
#include "headfile.h"

//---------------------------------  MY Define  --------------------------------
#define    BUZZ    		I1
#define    LED_G    		G1
#define    LED_R                G2
#define    LED_B                G3
#define    K1			C5
#define    K2			H7
#define    K3			H5
#define    K4			H2
#define    ON           0
#define    OFF  		1

//---------------------------------  ADC  -------------------------------
// #define AD1 ADC0_SE1
#define AD2	ADC1_CH3_B14 // 垂直右
#define AD3 ADC1_CH4_B15 // 水平左
#define AD4	ADC1_CH10_B21 // 垂直左
#define AD5 ADC1_CH12_B23 // 水平右