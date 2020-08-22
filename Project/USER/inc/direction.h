#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include  "common.h"



/**********全局变量外部申明********/
extern float g_fDirectionError[2];
extern float g_fDirectionError_dot[2];
extern float g_fDirectionControlOut;
extern int16 g_ValueOfAD[4];
extern int16 g_ValueOfADFilter[4];
extern float Environment;
extern float g_dirControl_P;		//方向控制P
extern float g_dirControl_D;	//方向控制D
extern float Turn_dirControl_P;		//进岛方向控制P
extern float Turn_dirControl_D;	//进岛方向控制D


extern float DownTime;
extern float DownTimeDuring;
extern float TurnTimeDuring; //转向时间常量，若要修改转向时间，就修改这个
extern float FreezingTimeDuring;  //冻结时间常量
extern float TurnTime;

extern int16 TurnAD0,TurnAD1,TurnAD2,TurnAD3;//水平左右，垂直左右电感，判断是否到达环岛的阈值
extern int16 LeaveAD0,LeaveAD1,LeaveAD2,LeaveAD3;//离开环岛的阈值放松
extern int16 DownAD0 ,DownAD1,DownAD2,DownAD3;//下坡判定电感值
extern int16 GarageAD23; // 车库电感2,3之和
extern int16 GarageAD0, GarageAD1; // 车库电感0,1
extern uint8 Flag_RoundSpeed;
extern uint8 garage_count;  // 出车库计数器



/***********函数声明***********/

void DirectionControl(void);
void Read_ADC(void);

#endif