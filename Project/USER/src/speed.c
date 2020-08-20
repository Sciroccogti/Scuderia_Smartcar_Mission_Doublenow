/*********************************************************************************************************************
 *
 * @file       		speed.c
 *  				速度控制
 * @core			S9KEA128
 * @date       		2018
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * Jul 12th, 2020
 * Modifying this file into rt1064 compatible version
 * Motor PWM control output and speed encoder input
 * Here I presuppose we use C0(pulse) and C1(direction) for left encoder
 * C2(pulse) and C24(direction) for right encoder
 * D0 D1 D2 D3 for PWM motor control left forward, left backward, right forward,
 *right backward
 ********************************************************************************************************************/
// KEA VERSION
//#include  "headerfile.h"
// RT1064 VERSION
#include "myheader.h"

/**********全局变量定义********/
int32 LeftDead = 0;
int32 RighDead = 0;
float Ratio_Encoder_Left =
    200 /
    (1175 *
     0.02);  // 左轮速度=counter*左轮周长(mm)/(左轮�?一圈�?�应的脉冲数*程序周期)
float Ratio_Encoder_Righ =
    200 /
    (1175 *
     0.02);  // 右轮速度=counter*右轮周长(mm)/(右轮�?一圈�?�应的脉冲数*程序周期)
extern float g_fRealSpeed = 0;  //真实速度
float g_fLeftRealSpeed;
float g_fRighRealSpeed;
float g_fSpeedFilter = 0;     //阶�??滤波速度
float g_fExpectSpeed = 1300;  //期望速度
float g_fSpeedError;          //速度偏差
float g_fSpeedErrorTemp[5] = {0};
int32 g_nLeftpulse = 0, g_nRighpulse = 0;
int32 nLeftPWM = 0, nRighPWM = 0;
int32 g_nLeftPWM = 0, g_nRighPWM = 0;
float g_fSpeedControlOut = 100;  //速度输出
float g_fSpeedControlOut_I=0;

int32 MaxPWM = 400;
int8 TurnFlag = OFF; // �?向标�?
int8 StraightClk = 0;
//以下为可能需要调整的参数
int mode = 0;

float StraightExpectSpeed;  //直�?�期望速度
float TurnExpectSpeed;      //�?道期望速度
float SpeedUpSpeed;         //加速期望速度
float DownSpeed;            //下坡期望速度
int outPWM1 = 150;//150
int outPWM2 = 000, diffPWM = 300;  // 出车库直行速度 �? �?向偏�?

float Expect_P;
float Expect_I;
float Expect_D;
// float TurnExpect_P = 0.25;
// float TurnExpect_D = 1.5;

int16 TurnValue = 800;  //�?道判定参�?
int16 BasePWM = 0;
int16 TurnBasePWM = 0;

// 出车库方向，1为右�?�?0为左�?
uint8 GarageDirection = 0;

float Kspeed = 1.2;//1.2
//速度和方向控制的比例系数，�?�注意控制Kspeed，不然速度�?�?控制会不平滑
float Kdirection = 0.8;//0.8

/**
 * @file		PWM输出
 * @date		2018
 */

void PWMOut(void) {
    if (TurnFlag == OFF) {
        g_nLeftPWM = (int32)(Kspeed * g_fSpeedControlOut / 2 -
                             Kdirection * g_fDirectionControlOut);
        g_nRighPWM = (int32)(Kspeed * g_fSpeedControlOut / 2 +
                             Kdirection * g_fDirectionControlOut);
        g_nLeftPWM += BasePWM;
        g_nRighPWM += BasePWM;
    } else {
        if (g_ValueOfAD[0] - g_ValueOfAD[1] > 0) {
            g_nLeftPWM = (int32)(Kspeed * g_fSpeedControlOut * 0.5 -
                                 Kdirection * g_fDirectionControlOut);
            g_nRighPWM = (int32)(Kspeed * g_fSpeedControlOut * 0.5 +
                                 Kdirection * g_fDirectionControlOut);
        } else {
            g_nLeftPWM = (int32)(Kspeed * g_fSpeedControlOut * 0.5 -
                                 Kdirection * g_fDirectionControlOut);
            g_nRighPWM = (int32)(Kspeed * g_fSpeedControlOut * 0.5 +
                                 Kdirection * g_fDirectionControlOut);
        }
        g_nLeftPWM += TurnBasePWM;
        g_nRighPWM += TurnBasePWM;
    }
       
    if (Flag_Stop == OFF)  //如果Flag_Stop == OFF电机输出0
    {
        g_nLeftPWM = 0;
        g_nRighPWM = 0;
    } else if (garage_count == 0)  // �?出车�?
    {
        g_nLeftPWM = g_nRighPWM = outPWM1;
    } else if (garage_count == 1)  // 车库口转�?
    {
        g_nLeftPWM = outPWM2 + diffPWM * (-1 + 2 * GarageDirection);
        g_nRighPWM = outPWM2 - diffPWM * (-1 + 2 * GarageDirection);
    }

    if (g_nLeftPWM < 0) {
        nLeftPWM = LeftDead - g_nLeftPWM;
        nLeftPWM = (nLeftPWM > MaxPWM ? MaxPWM : nLeftPWM);
        pwm_duty(LMOTOR_B, nLeftPWM);
        pwm_duty(LMOTOR_F, 0);
    } else {
        nLeftPWM = LeftDead + g_nLeftPWM;
        nLeftPWM = (nLeftPWM > MaxPWM ? MaxPWM : nLeftPWM);
        pwm_duty(LMOTOR_B, 0);
        pwm_duty(LMOTOR_F, nLeftPWM);
    }

    if (g_nRighPWM < 0) {
        nRighPWM = RighDead - g_nRighPWM;
        nRighPWM = (nRighPWM > MaxPWM ? MaxPWM : nRighPWM);
        pwm_duty(RMOTOR_B, nRighPWM);
        pwm_duty(RMOTOR_F, 0);
    } else {
        nRighPWM = RighDead + g_nRighPWM;
        nRighPWM = (nRighPWM > MaxPWM ? MaxPWM : nRighPWM);
        pwm_duty(RMOTOR_B, 0);
        pwm_duty(RMOTOR_F, nRighPWM);
    }
}

/**
 * @file		计算速度偏差
 * @note      	产生全局变量g_fSpeedError
 * @date		2018
 */
void CalSpeedError(void) {
    static float fSpeedOld = 0, fSpeedNew = 0;
    g_nLeftpulse = -qtimer_quad_get(
        QTIMER_1, QTIMER1_TIMER0_C0);  //读取左轮脉冲 C0:LSB C1:DIR
    g_nRighpulse = qtimer_quad_get(
        QTIMER_1, QTIMER1_TIMER2_C2);  //读取右轮脉冲 C2:LSB C24:DIR
    qtimer_quad_clear(QTIMER_1, QTIMER1_TIMER0_C0);
    qtimer_quad_clear(QTIMER_1, QTIMER1_TIMER2_C2);

    g_fLeftRealSpeed = g_nLeftpulse * Ratio_Encoder_Left;
    g_fLeftRealSpeed =
        (g_fLeftRealSpeed > 9000 ? 9000 : g_fLeftRealSpeed);  //滤左编码器的�?�?
    g_fRighRealSpeed = g_nRighpulse * Ratio_Encoder_Righ;
    g_fRighRealSpeed =
        (g_fRighRealSpeed < -9000 ? -9000 : g_fRighRealSpeed);  //滤右编码器的�?�?

    g_fRealSpeed = (g_fLeftRealSpeed + g_fRighRealSpeed) * 0.5;  //真实速度

    //速度采集�?度平滑，每�?�采集最大变�?200
    fSpeedOld = g_fSpeedFilter;
    fSpeedNew = g_fRealSpeed;

    if (fSpeedNew >= fSpeedOld)
        g_fSpeedFilter =
            ((fSpeedNew - fSpeedOld) > 300 ? (fSpeedOld + 300) : fSpeedNew);
    else
        g_fSpeedFilter =
            ((fSpeedNew - fSpeedOld) < -300 ? (fSpeedOld - 300) : fSpeedNew);

    if (g_ValueOfAD[0] - g_ValueOfAD[1] > TurnValue ||
        g_ValueOfAD[1] - g_ValueOfAD[0] > TurnValue)
        TurnFlag = ON;
    else {
        TurnFlag = OFF;
    }
    gpio_set(D13, 0);
    if (DownTime) {
        g_fExpectSpeed = DownSpeed;
        gpio_set(D13, 1);
    } else if (ON == TurnFlag)
        g_fExpectSpeed = TurnExpectSpeed;
    else
        g_fExpectSpeed = StraightExpectSpeed;

    g_fSpeedErrorTemp[4] = g_fSpeedErrorTemp[3];
    g_fSpeedErrorTemp[3] = g_fSpeedErrorTemp[2];
    g_fSpeedErrorTemp[2] = g_fSpeedErrorTemp[1];
    g_fSpeedErrorTemp[1] = g_fSpeedErrorTemp[0];
    g_fSpeedErrorTemp[0] = g_fSpeedError;
    g_fSpeedError = (g_fExpectSpeed - g_fSpeedFilter);
}

/**
 * @file		速度控制
 * @note      	速度�?度平�?
 * @date		2019
 */
void SpeedControl(void) {
    CalSpeedError();  //计算速度偏差
    if (g_ValueOfAD[0] - g_ValueOfAD[1] > TurnValue ||
        g_ValueOfAD[1] - g_ValueOfAD[0] > TurnValue)
    {
        g_fSpeedControlOut_I += g_fSpeedErrorTemp[0];
        g_fSpeedControlOut =
            Expect_P * g_fSpeedError +
            Expect_I * g_fSpeedControlOut_I+
            Expect_D * (g_fSpeedErrorTemp[0] - g_fSpeedErrorTemp[1]);
    }
    else
    {
        g_fSpeedControlOut_I += g_fSpeedErrorTemp[0];
        g_fSpeedControlOut =
            Expect_P * g_fSpeedError +
            Expect_I * g_fSpeedControlOut_I+
            Expect_D * (g_fSpeedErrorTemp[0] - g_fSpeedErrorTemp[1]);
    }
}
