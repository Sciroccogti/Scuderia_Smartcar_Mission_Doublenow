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
#define AD1 ADC0_SE1
#define AD2	ADC0_SE3
#define AD3 ADC0_SE2
#define AD4	ADC0_SE9
#define AD5 ADC0_SE10