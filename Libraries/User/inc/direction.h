#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include  "common.h"



/**********ȫ�ֱ����ⲿ����********/
extern float g_fDirectionError[2];
extern float g_fDirectionError_dot[2];
extern float g_fDirectionControlOut;
extern int16 g_ValueOfAD[4];
extern int16 g_ValueOfADFilter[4];
extern float Environment;
extern float g_dirControl_P;		//�������P
extern float g_dirControl_D;	//�������D
extern float Turn_dirControl_P;		//�����������P
extern float Turn_dirControl_D;	//�����������D

extern float DownTime;
extern float DownTimeDuring;
extern float TurnTimeDuring; //ת��ʱ�䳣������Ҫ�޸�ת��ʱ�䣬���޸����
extern float FreezingTimeDuring;  //����ʱ�䳣��

extern int16 TurnAD0,TurnAD1,TurnAD2,TurnAD3;//ˮƽ���ң���ֱ���ҵ�У��ж��Ƿ񵽴ﻷ������ֵ
extern int16 LeaveAD0,LeaveAD1,LeaveAD2,LeaveAD3;//�뿪��������ֵ����
extern int16 DownAD0 ,DownAD1,DownAD2,DownAD3;//�����ж����ֵ
extern uint8 Flag_Round;



/***********��������***********/

void DirectionControl(void);
void Read_ADC(void);

#endif