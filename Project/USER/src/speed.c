/*********************************************************************************************************************
 * 
 * @file       		speed.c
 *  				�ٶȿ���
 * @core			S9KEA128
 * @date       		2018
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * Jul 12th, 2020
 * Modifying this file into rt1064 compatible version
 * Motor PWM control output and speed encoder input
 * Here I presuppose we use C0(pulse) and C1(direction) for left encoder
 * C2(pulse) and C24(direction) for right encoder
 * D0 D1 D2 D3 for PWM motor control left forward, left backward, right forward, right backward
 ********************************************************************************************************************/
//KEA VERSION
//#include  "headerfile.h"
//RT1064 VERSION
#include"headfile.h"

/**********ȫ�ֱ�������********/
int32 LeftDead = 0;
int32 RighDead = 0;
float Ratio_Encoder_Left = 200/(1175*0.02);// �����ٶ�=counter*�����ܳ�(mm)/(����תһȦ��Ӧ��������*��������)
float Ratio_Encoder_Righ = 200/(1175*0.02);// �����ٶ�=counter*�����ܳ�(mm)/(����תһȦ��Ӧ��������*��������)
float g_fRealSpeed = 0;				//��ʵ�ٶ�
float g_fLeftRealSpeed;
float g_fRighRealSpeed;
float g_fSpeedFilter = 0;			//�����˲��ٶ�
float g_fExpectSpeed = 1300;		//�����ٶ�
float g_fSpeedError;				//�ٶ�ƫ��
float g_fSpeedErrorTemp[5] = {0};		
int32 g_nLeftpulse = 0,g_nRighpulse = 0;
int32 nLeftPWM = 0,nRighPWM = 0;
int32 g_nLeftPWM = 0, g_nRighPWM = 0;
float g_fSpeedControlOut = 100;		//�ٶ����
int32 MaxPWM = 650;
int8 TurnFlag = OFF;
int8 StraightClk = 0;
//����Ϊ������Ҫ�����Ĳ���

float StraightExpectSpeed;     //ֱ�������ٶ�
float TurnExpectSpeed ;         //��������ٶ�
float SpeedUpSpeed;  //���������ٶ�
float DownSpeed;//���������ٶ�

float Expect_P;
float Expect_D;
//float TurnExpect_P = 0.25;
//float TurnExpect_D = 1.5;

int16 TurnValue = 400;//����ж�����
int16 BasePWM = 0;
int16 TurnBasePWM = 0;

float Kspeed = 1;  //�ٶȺͷ�����Ƶı���ϵ����Ҫע�����Kspeed����Ȼ�ٶȱջ����ƻ᲻ƽ��
float Kdirection = 1;   


/**
 * @file		PWM���
 * @date		2018
 */

void PWMOut(void)
{
	
	if(TurnFlag == OFF)
	{
		g_nLeftPWM = (int32)(Kspeed * g_fSpeedControlOut /2 - Kdirection * g_fDirectionControlOut);
		g_nRighPWM = (int32)(Kspeed * g_fSpeedControlOut /2 + Kdirection * g_fDirectionControlOut); 
		g_nLeftPWM += BasePWM;
		g_nRighPWM += BasePWM;
	}
	else
	{
		if(g_ValueOfAD[0]-g_ValueOfAD[1] > 0)
		{
			g_nLeftPWM = (int32)(Kspeed * g_fSpeedControlOut * 0.5 - Kdirection * g_fDirectionControlOut);
			g_nRighPWM = (int32)(Kspeed * g_fSpeedControlOut * 0.5 + Kdirection * g_fDirectionControlOut); 
		}
		else
			{
			g_nLeftPWM = (int32)(Kspeed * g_fSpeedControlOut * 0.5 - Kdirection * g_fDirectionControlOut);
			g_nRighPWM = (int32)(Kspeed * g_fSpeedControlOut * 0.5 + Kdirection * g_fDirectionControlOut); 
		}
		g_nLeftPWM += TurnBasePWM;
		g_nRighPWM += TurnBasePWM;
	}
	
        
        
    if(Flag_Stop == OFF) 									//���Flag_Stop == OFF������0
	{
	  	g_nLeftPWM = 0;g_nRighPWM = 0;
	}

  	if(g_nLeftPWM < 0)
	{
		nLeftPWM = LeftDead - g_nLeftPWM;
		nLeftPWM = (nLeftPWM > MaxPWM? MaxPWM: nLeftPWM);
		/*//KEA VERSION
		FTM_PWM_Duty(ftm2, ftm_ch5, nLeftPWM);
		FTM_PWM_Duty(ftm2, ftm_ch4, 0);
		*/
		//RT1064 VERSION
		pwm_duty(LMOTOR_B, nLeftPWM);
		pwm_duty(LMOTOR_F, 0);
	}
	else
	{
		nLeftPWM = LeftDead + g_nLeftPWM;
		nLeftPWM = (nLeftPWM > MaxPWM? MaxPWM: nLeftPWM);
		/*//KEA VERSION
		FTM_PWM_Duty(ftm2, ftm_ch5, 0);
		FTM_PWM_Duty(ftm2, ftm_ch4, nLeftPWM);
		*/
		//RT1064 VERSION
		pwm_duty(LMOTOR_B, 0);
		pwm_duty(LMOTOR_F, nLeftPWM);
	}

	if(g_nRighPWM < 0)
	{
		nRighPWM = RighDead - g_nRighPWM;
		nRighPWM = (nRighPWM > MaxPWM? MaxPWM: nRighPWM);
		/*//KEA VERSION
		FTM_PWM_Duty(ftm2, ftm_ch0, 0);
		FTM_PWM_Duty(ftm2, ftm_ch1, nRighPWM);
		*/
		//RT1064 VERSION
		pwm_duty(RMOTOR_B, nRighPWM);
		pwm_duty(RMOTOR_F, 0);
	}
	else
	{
		nRighPWM = RighDead + g_nRighPWM;
		nRighPWM = (nRighPWM > MaxPWM? MaxPWM: nRighPWM);
		/*//KEA VERSION
		FTM_PWM_Duty(ftm2, ftm_ch0, nRighPWM);
		FTM_PWM_Duty(ftm2, ftm_ch1, 0);
		*/
		//RT1064 VERSION
		pwm_duty(RMOTOR_B, 0);
		pwm_duty(RMOTOR_F, nRighPWM);
	}
}
   

/**
 * @file		�����ٶ�ƫ��
 * @note      	����ȫ�ֱ���g_fSpeedError
 * @date		2018
 */
void CalSpeedError(void)
{
	static float fSpeedOld = 0, fSpeedNew = 0;

	/*//KEA version
	g_nLeftpulse = (GPIO_Get(E1) ==1?FTM_Pulse_Get(ftm0):-FTM_Pulse_Get(ftm0));//��ȡ��������
	FTM_Count_Clean(ftm0);
	g_nRighpulse = (GPIO_Get(H6)==0?FTM_Pulse_Get(ftm1):-FTM_Pulse_Get(ftm1));//��ȡ��������
	FTM_Count_Clean(ftm1);	
	*/

	//rt1064 version, optimizing style of coding
	g_nLeftpulse = qtimer_quad_get(QTIMER_1, QTIMER1_TIMER0_C0);//��ȡ�������� C0:LSB C1:DIR
	g_nLeftpulse = qtimer_quad_get(QTIMER_1, QTIMER1_TIMER0_C2);//��ȡ�������� C2:LSB C24:DIR
	qtimer_quad_clear(QTIMER_1,QTIMER1_TIMER0_C0 );  
	qtimer_quad_clear(QTIMER_1,QTIMER1_TIMER2_C2 );  

	g_fLeftRealSpeed = g_nLeftpulse*Ratio_Encoder_Left;
	g_fLeftRealSpeed = (g_fLeftRealSpeed>3400?3400:g_fLeftRealSpeed);		//���������������
	g_fRighRealSpeed = g_nRighpulse*Ratio_Encoder_Righ;
	g_fRighRealSpeed = (g_fRighRealSpeed>3400?3400:g_fRighRealSpeed);		//���ұ�����������
	
	g_fRealSpeed = (g_fLeftRealSpeed + g_fRighRealSpeed)*0.5;				//��ʵ�ٶ�
	
	//�ٶȲɼ��ݶ�ƽ����ÿ�βɼ����仯200
	fSpeedOld = g_fSpeedFilter;
	fSpeedNew = g_fRealSpeed;

	if(fSpeedNew>=fSpeedOld)
		g_fSpeedFilter = ((fSpeedNew-fSpeedOld)>300?(fSpeedOld+300):fSpeedNew);
	else
		g_fSpeedFilter = ((fSpeedNew-fSpeedOld)<-300?(fSpeedOld-300):fSpeedNew);

       
	if(g_ValueOfAD[0]-g_ValueOfAD[1]>  TurnValue||g_ValueOfAD[1]-g_ValueOfAD[0]>TurnValue)
          TurnFlag = ON;
        else
        {
          TurnFlag = OFF;
        }
        
       if(DownTime)
        {
          g_fExpectSpeed = DownSpeed;
        }
        else
          if(ON == TurnFlag)  
            g_fExpectSpeed=TurnExpectSpeed;
          else
            g_fExpectSpeed=StraightExpectSpeed;


	g_fSpeedErrorTemp[4] = g_fSpeedErrorTemp[3];
	g_fSpeedErrorTemp[3] = g_fSpeedErrorTemp[2];
	g_fSpeedErrorTemp[2] = g_fSpeedErrorTemp[1];
	g_fSpeedErrorTemp[1] = g_fSpeedErrorTemp[0];
	g_fSpeedErrorTemp[0] = g_fSpeedError;
	g_fSpeedError =  (g_fExpectSpeed - g_fSpeedFilter);
	
}


/**
 * @file		�ٶȿ���
 * @note      	�ٶ��ݶ�ƽ��
 * @date		2019
 */
void SpeedControl(void)
{
	CalSpeedError();	//�����ٶ�ƫ��
 
        if(g_ValueOfAD[0]-g_ValueOfAD[1]>  TurnValue||g_ValueOfAD[1]-g_ValueOfAD[0]>  TurnValue)
          g_fSpeedControlOut = Expect_P * g_fSpeedError + Expect_D * (g_fSpeedErrorTemp[0]-g_fSpeedErrorTemp[1]);
        else
          g_fSpeedControlOut = Expect_P * g_fSpeedError + Expect_D * (g_fSpeedErrorTemp[0]-g_fSpeedErrorTemp[1]);

}







