#ifndef __SPEED_H__
#define __SPEED_H__

#include  "common.h"



/**********ȫ�ֱ����ⲿ����********/
extern int32 g_nLeftpulse;
extern int32 g_nRighpulse;
extern float g_fSpeedError;
extern float g_fRealSpeed;
extern float g_fLeftRealSpeed;
extern float g_fRighRealSpeed;
extern float g_fSpeedFilter;
extern float g_fSpeedControlOut;
extern int32 g_nLeftPWM, g_nRighPWM;
extern float g_fExpectSpeed;
extern int32 MaxPWM;

extern float StraightExpectSpeed;     //ֱ�������ٶ�
extern float TurnExpectSpeed;         //��������ٶ�
extern float SpeedUpSpeed;
extern float DownSpeed ;

extern float Expect_P;
extern float Expect_D;
//extern float TurnExpect_P;
//extern float TurnExpect_D;

extern int16 TurnValue;//����ж�����
extern int16 BasePWM ;
extern int16 TurnBasePWM ;

extern float Kspeed;  //�ٶȺͷ�����Ƶı���ϵ����Ҫע�����Kspeed����Ȼ�ٶȱջ����ƻ᲻ƽ��
extern float Kdirection; 

/***********��������***********/
void MotorInit(void);
void PWMOut(void);
void CalSpeedError(void);
void SpeedControl(void);


#endif