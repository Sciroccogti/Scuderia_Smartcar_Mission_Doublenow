#ifndef __SPEED_H__
#define __SPEED_H__

#include  "common.h"



/**********全局变量外部申明********/
extern int32 g_nLeftpulse;
extern int32 g_nRighpulse;
extern float g_fSpeedError;
extern float g_fRealSpeed;
extern float g_fLeftRealSpeed;
extern float g_fRighRealSpeed;
extern float g_fSpeedFilter;
extern float g_fSpeedControlOut;
extern float g_fSpeedControlOut_I;
extern int32 g_nLeftPWM, g_nRighPWM;
extern float g_fExpectSpeed;
extern int32 MaxPWM;

extern float StraightExpectSpeed;     //直行期望速度
extern float TurnExpectSpeed;         //弯道期望速度
extern float SpeedUpSpeed;
extern float DownSpeed ;
extern int outPWM1, outPWM2, diffPWM; // 出车库直行速度 和 转向偏差

extern float Expect_P;
extern float Expect_I;
extern float Expect_D;
//extern float TurnExpect_P;
//extern float TurnExpect_D;

extern int16 TurnValue;//弯道判定参数
extern int8 TurnFlag;
extern int16 BasePWM ;
extern int16 TurnBasePWM ;

extern uint8 GarageDirection;

extern float Kspeed;  //速度和方向控制的比例系数，要注意控制Kspeed，不然速度闭环控制会不平滑
extern float Kdirection; 
extern int mode;

/***********函数声明***********/
void MotorInit(void);
void PWMOut(void);
void CalSpeedError(void);
void SpeedControl(void);


#endif