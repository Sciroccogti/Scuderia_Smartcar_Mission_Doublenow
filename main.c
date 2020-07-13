/*********************************************************************************************************************
 * 
 * @file       		main.c
 *  				������
 * @core			S9KEA128
 * @date       		2018
 ********************************************************************************************************************/
/*********************************************************************************************************************
 * Jul 12th, 2020
 * Modifying this file into rt1064 compatible version
 ********************************************************************************************************************/
//KEA VERSION
//#include "headerfile.h"
//RT1064 VERSION
#include "headfile.h"
uint8 page = 0;
uint8 SW1, SW2, SW3, SW4;
uint8 UpFlag = 1, DownFlag = 1, LeftFlag = 1, RightFlag = 1, MidFlag = 1;

void myoled()
{
    //need adc_init(ADC_1,ADC1_CH3_B14,ADC_8BIT); //��ʼ��B14ΪADC���� �ֱ���Ϊ8λ
    //and adc_init(ADC_1,ADC1_CH4_B15,ADC_8BIT);
    uint16 ad5 = adc_convert(ADC_1, ADC1_CH3_B14);
    // uint16 ad4=ADC_Read(ADC0_SE9);
    uint16 ad3 = adc_convert(ADC_1, ADC1_CH4_B15);

    char Left[8];
    char Right[8];
    char LeftMiddle[8];
    char RightMiddle[8];

    //char LeftPwm[8];
    //char RightPwm[8];

    sprintf(Left, "L:%d", g_ValueOfAD[0]);         //ˮƽ����
    sprintf(Right, "R:%d", g_ValueOfAD[1]);        //ˮƽ�ҵ��
    sprintf(LeftMiddle, "LM:%d", g_ValueOfAD[2]);  //ˮƽ����
    sprintf(RightMiddle, "RM:%d", g_ValueOfAD[3]); //ˮƽ�ҵ��
                                                  //sprintf(LeftPwm,"LP:%d",LeftP);
                                                  //sprintf(LeftPwm,"RP:%d",RightP);
                                                  //sprintf(LeftPwm,"LP:%d",(int16)g_fLeftRealSpeed);//��������
                                                  //sprintf(RightPwm,"RP:%d",(int16)g_fRighRealSpeed);//��������
                                                  /*//KEA version
    OLED_Display_Config(1);
    OLED_Clear(0x00);

    OLED_Show_String(8, 13, 0, 63, 1, Left, 0);
    OLED_Show_String(8, 13, 0, 32, 1, Right, 0);
    OLED_Show_String(8, 13, 50, 63, 1, LeftMiddle, 0);
    OLED_Show_String(8, 13, 50, 32, 1, RightMiddle, 0);
    

    //OLED_Show_String(8,13,50,63,1,RightPwm,0);
    //OLED_Show_String(8,13,50,32,1,LeftPwm,0);
    OLED_Refresh_Gram();
    */

    //RT1064 version
    oled_fill(0x00); //clear
    oled_p8x16str(0, 6, Left);
    oled_p8x16str(0, 4, Right);
    oled_p8x16str(64, 6, LeftMiddle);
    oled_p8x16str(64, 4, RightMiddle);
}

void oled()
{
    //need adc_init(ADC_1,ADC1_CH3_B14,ADC_8BIT); //��ʼ��B14ΪADC���� �ֱ���Ϊ8λ
    //and adc_init(ADC_1,ADC1_CH4_B15,ADC_8BIT);
    uint16 ad5 = adc_convert(ADC_1, ADC1_CH3_B14);
    // uint16 ad4=ADC_Read(ADC0_SE9);
    uint16 ad3 = adc_convert(ADC_1, ADC1_CH4_B15);

    char Left[8];
    char Right[8];
    char LeftMiddle[8];
    char RightMiddle[8];

    //char LeftPwm[8];
    //char RightPwm[8];

    sprintf(Left, "L:%d", g_ValueOfAD[0]);         //ˮƽ����
    sprintf(Right, "R:%d", g_ValueOfAD[1]);        //ˮƽ�ҵ��
    sprintf(LeftMiddle, "LM:%d", g_ValueOfAD[2]);  //ˮƽ����
    sprintf(RightMiddle, "RM:%d", g_ValueOfAD[3]); //ˮƽ�ҵ��
                                                  //sprintf(LeftPwm,"LP:%d",LeftP);
                                                  //sprintf(LeftPwm,"RP:%d",RightP);
                                                  //sprintf(LeftPwm,"LP:%d",(int16)g_fLeftRealSpeed);//��������
                                                  //sprintf(RightPwm,"RP:%d",(int16)g_fRighRealSpeed);//��������
                                                  /*//KEA version
    OLED_Display_Config(1);
    OLED_Clear(0x00);

    OLED_Show_String(8, 13, 0, 63, 1, Left, 0);
    OLED_Show_String(8, 13, 0, 32, 1, Right, 0);
    OLED_Show_String(8, 13, 50, 63, 1, LeftMiddle, 0);
    OLED_Show_String(8, 13, 50, 32, 1, RightMiddle, 0);
    

    //OLED_Show_String(8,13,50,63,1,RightPwm,0);
    //OLED_Show_String(8,13,50,32,1,LeftPwm,0);
    OLED_Refresh_Gram();
    */

    //RT1064 version
    oled_fill(0x00); //clear
    oled_p8x16str(0, 6, Left);
    oled_p8x16str(0, 4, Right);
    oled_p8x16str(64, 6, LeftMiddle);
    oled_p8x16str(64, 4, RightMiddle);
    //not sure if refresh is required
}

//�����������
void BlueTooth()
{
    char data[16];
    sprintf(data, "L:%d\n", (uint8)g_ValueOfAD[0]);
    uart_putbuff(uart2, &data[0], sizeof(data));

    char data2[16];
    sprintf(data2, "R:%d\n", (uint8)g_ValueOfAD[1]);
    uart_putbuff(uart2, &data2[0], sizeof(data2));

    /*
      uart_putbuff(uart2,"g_fRealSpeed: ",18);
      UART_Putchar(uart2,(uint8)g_fRealSpeed);
      UART_Putchar(uart2,'\n');
      
      uart_putbuff(uart2,"g_fSpeedControlOut: ",18);
      UART_Putchar(uart2,(uint8)g_fSpeedControlOut);
      UART_Putchar(uart2,'\n');
      
      uart_putbuff(uart2,"g_nLeftPWM: ",14);
      UART_Putchar(uart2,g_nLeftPWM);
      UART_Putchar(uart2,'\n');
      
      uart_putbuff(uart2,"g_nRighPWM: ",14);
      UART_Putchar(uart2,g_nRighPWM);
      UART_Putchar(uart2,'\n');
      
      UART_Putchar(uart2,'\n');
*/
}

void myoled1()

{
    char DirP[16];
    char DirD[16];

    sprintf(DirP, "DirP:%d", (int16)g_dirControl_P);
    sprintf(DirD, "DirD:%d", (int16)g_dirControl_D);
    /*//KEA128 version
    OLED_Display_Config(1);
    OLED_Clear(0x00);

    OLED_Show_String(8, 13, 0, 64, 1, DirP, 0);
    OLED_Show_String(8, 13, 0, 50, 1, DirD, 0);

    OLED_Refresh_Gram();
    */

    //RT1024 version
    oled_fill(0x00); //clear
    oled_p8x16str(0, 6, DirP);
    oled_p8x16str(0, 4, DirD);

    //need info about ports for this part
    if (gpio_get(H3) == 0)
        g_dirControl_P -= 10;
    if (gpio_get(F7) == 0)
        g_dirControl_P += 10;
    if (gpio_get(H4) == 0)
        g_dirControl_D -= 10;
    if (gpio_get(F5) == 0)
        g_dirControl_D += 10;
}
void myoled2()

{
    char TurnDirP[16];
    char TurnDirD[16];

    sprintf(TurnDirP, "TurnDirP:%d", (int16)Turn_dirControl_P);
    sprintf(TurnDirD, "TurnDirD:%d", (int16)Turn_dirControl_D);

    OLED_Display_Config(1);
    OLED_Clear(0x00);
    /*//KEA128 version
	OLED_Show_String(8, 13, 0, 63, 1, TurnDirP, 0);
	OLED_Show_String(8, 13, 0, 32, 1, TurnDirD, 0);
    OLED_Refresh_Gram();
    */

    //RT1064 version
    oled_fill(0x00); //clear
    oled_p8x16str(0, 6, TurnDirP);
    oled_p8x16str(0, 4, TurnDirD);

    //need info about ports for this part
    if (gpio_get(H3) == 0)
        Turn_dirControl_P -= 10;
    if (gpio_get(F7) == 0)
        Turn_dirControl_P += 10;
    if (gpio_get(H4) == 0)
        Turn_dirControl_D -= 10;
    if (gpio_get(F5) == 0)
        Turn_dirControl_D += 10;
}

void myoled3()

{
    char Env[16];

    sprintf(Env, "Environment:%d", (int16)(Environment * 100));

    /*//KEA128 version
	OLED_Display_Config(1);
	OLED_Clear(0x00);
   
	OLED_Show_String(8, 13, 0, 63, 1, Env, 0);

	OLED_Refresh_Gram();
    */

    //RT1064 version
    oled_fill(0x00); //clear
    oled_p8x16str(0, 6, Env);


    if (gpio_get(H4) == 0)
    {
        systick_delay_ms(20);
        Environment -= 0.05;
    }
    if (gpio_get(F5) == 0)
    {
        systick_delay_ms(20);
        Environment += 0.05;
    }
}

void myoled4()

{
    char TurnTD[16];
    char FreezeTD[16];

    sprintf(TurnTD, "TTDur:%d", (int16)TurnTimeDuring);
    sprintf(FreezeTD, "FTDur:%d", (int16)FreezingTimeDuring);

    /*//KEA128 version
    OLED_Display_Config(1);
    OLED_Clear(0x00);
    OLED_Show_String(8, 13, 0, 63, 1, TurnTD, 0);
    OLED_Show_String(8, 13, 0, 32, 1, FreezeTD, 0);
    OLED_Refresh_Gram();
    */

    //RT1064 version
    oled_fill(0x00); //clear
    oled_p8x16str(0, 6, TurnTD);
    oled_p8x16str(0, 4, FreezeTD);

    if (gpio_get(H3) == 0)
        TurnTimeDuring += 10;
    if (gpio_get(F7) == 0)
        TurnTimeDuring -= 10;
    if (gpio_get(H4) == 0)
        FreezingTimeDuring += 10;
    if (gpio_get(F5) == 0)
        FreezingTimeDuring -= 10;
}

//���������ж�
/*
void uart_RX_INT(uint8 ch)
{
    UART_Getchar(uart2,&ch);
    
    switch(ch)
    {
    case 's':
      Flag_Stop= !Flag_Stop;
      break;
      
      
    case 'a':
      g_speedControl_P+=10;
      //uart_putbuff(uart2,"g_speedControl_P: ",18);
      UART_Putchar(uart2,(int32)g_speedControl_P);
      //UART_Putchar(uart2,'\n');
      break;
      
    case 'b':
      g_speedControl_P-=10;
      uart_putbuff(uart2,"g_speedControl_P: ",18);
      UART_Putchar(uart2,(char)g_speedControl_P);
      UART_Putchar(uart2,'\n');
      
      break;
      
    case 'c':
      g_speedControl_I+=10;
       uart_putbuff(uart2,"g_speedControl_I: ",18);
      UART_Putchar(uart2,(uint8)g_speedControl_I);
      UART_Putchar(uart2,'\n');
      break;
    case 'd':
      g_speedControl_I-=10;
       uart_putbuff(uart2,"g_speedControl_I: ",18);
      UART_Putchar(uart2,(uint8)g_speedControl_I);
      UART_Putchar(uart2,'\n');
      break;
      
    case 'e':
      g_dirControl_P+=10;
      uart_putbuff(uart2,"g_dirControl_P: ",14);
      UART_Putchar(uart2,(uint8)g_dirControl_P);
      UART_Putchar(uart2,'\n');
      break;
      
    case 'f':
      g_dirControl_P-=10;
      uart_putbuff(uart2,"g_dirControl_P: ",14);
      UART_Putchar(uart2,(uint8)g_dirControl_P);
      UART_Putchar(uart2,'\n');
      break;
      
    case 'g':
      g_dirControl_D+=10;
       uart_putbuff(uart2,"g_dirControl_D: ",14);
      UART_Putchar(uart2,(uint8)g_dirControl_D);
      UART_Putchar(uart2,'\n');
      break;
      
    case 'h':
      g_dirControl_D-=10;
       uart_putbuff(uart2,"g_dirControl_D: ",14);
      UART_Putchar(uart2,(uint8)g_dirControl_D);
      UART_Putchar(uart2,'\n');
      break;
    case 'r':
      uart_putbuff(uart2,"g_speedControl_P: ",18);
      UART_Putchar(uart2,(uint8)g_speedControl_P);
      UART_Putchar(uart2,'\n');
      
       uart_putbuff(uart2,"g_speedControl_I: ",18);
      UART_Putchar(uart2,(uint8)g_speedControl_I);
      UART_Putchar(uart2,'\n');
      
       uart_putbuff(uart2,"g_dirControl_P: ",14);
      UART_Putchar(uart2,(uint8)g_dirControl_P);
      UART_Putchar(uart2,'\n');
      
       uart_putbuff(uart2,"g_dirControl_D: ",14);
      UART_Putchar(uart2,(uint8)g_dirControl_D);
      UART_Putchar(uart2,'\n');
    default:
      break;
    }
}
*/

int main(void)
{
    //RT1064 EXCLUSIVE CONTENT
    DisableGlobalIRQ();
    board_init();
    systick_delay_ms(100);
    car_init();

    EnableGlobalIRQ(0);

    //while ((1280 * ex_clk_khz) != (256 * ics_clk_khz)); //ȷ��ʱ����������

    //UART_RX_IRQ_Enable(uart2);
    Flag_Stop = ON;

    while (1)
    {

        //myoled();
        //���򿪹ص���

        BlueTooth();
        if (gpio_get(F4) == 0)
        {
            page++;
        }
        switch (page % 4)
        {
        case 0:
            oled();

            break;

        case 1:
            myoled1();
            break;

        case 2:
            myoled2();
            break;

        case 3:
            myoled3();
            break;

        default:
            break;
        }

        //0.5sLED��˸
        static uint16 i = 0;
        i++;
        if (i >= 100)
        {
            //KEA VERSION
            //GPIO_Turn(LED_R);

            //RT1064 VERSION
            gpio_turn(LED_R);
            i = 0;
        }

        //���뿪�ػ���
        /*//KEA VERSION
        SW1 = gpio_get(C5);
        SW2 = gpio_get(H7);
        SW3 = gpio_get(H5);
        SW4 = gpio_get(H2);
        */

        //RT1064 VERSION
        SW1 = gpio_get(C5); //C31
        SW2 = gpio_get(H7); //B11
        SW3 = gpio_get(H5); //C27
        SW4 = gpio_get(H2); //C25

        TurnAD0 = 2000, TurnAD1 = 2000, TurnAD2 = 1200, TurnAD3 = 1200; //ˮƽ���ң���ֱ���ҵ�У��ж��Ƿ񵽴ﻷ������ֵ
        LeaveAD0 = 1300, LeaveAD1 = 1300, LeaveAD2 = 1000, LeaveAD3 = 1000;
        DownAD0 = 2000, DownAD1 = 2000, DownAD2 = 1200, DownAD3 = 1200; //�����ж����ֵ

        int Flag_0 = 1;
        if (Flag_0)
        {
            if (SW1 && SW2 && SW3 && SW4) //����  Ħ����������Ư��
            {
                StraightExpectSpeed = 3700; //ֱ�������ٶ�
                TurnExpectSpeed = 3600;     //��������ٶ�
                DownSpeed = 3450;           //���������ٶ�

                g_dirControl_P = 3000; //�������P
                g_dirControl_D = 5000; //�������D

                Turn_dirControl_P = 3000; //�����������P
                Turn_dirControl_D = 7000; //�����������D

                TurnTimeDuring = 100;     //ת��ʱ�䳣������Ҫ�޸�ת��ʱ�䣬���޸����
                FreezingTimeDuring = 250; //����ʱ�䳣��
                DownTimeDuring = 175;     //����ʱ�䳣��

                Expect_P = 0.4; //1.25
                Expect_D = 0.5;

                TurnValue = (int)(275 * Environment);
            }
            if (!SW1 && SW2 && SW3 && SW4) //��
            {
                StraightExpectSpeed = 3500; //ֱ�������ٶ�
                TurnExpectSpeed = 3400;     //��������ٶ�9
                DownSpeed = 3250;           //���������ٶ�

                g_dirControl_P = 3000; //�������P
                g_dirControl_D = 3200; //�������D

                Turn_dirControl_P = 2500; //�����������P
                Turn_dirControl_D = 6000; //�����������D

                TurnTimeDuring = 100;     //ת��ʱ�䳣������Ҫ�޸�ת��ʱ�䣬���޸����
                FreezingTimeDuring = 250; //����ʱ�䳣��
                DownTimeDuring = 175;     //����ʱ�䳣��

                Expect_P = 0.4; //1.25
                Expect_D = 0.5;

                TurnValue = (int)(275 * Environment);
            }
            if (SW1 && !SW2 && SW3 && SW4) //����
            {
                StraightExpectSpeed = 3200; //ֱ�������ٶ�
                TurnExpectSpeed = 3100;     //��������ٶ�
                DownSpeed = 2950;           //���������ٶ�

                g_dirControl_P = 3000; //�������P
                g_dirControl_D = 3200; //�������D

                Turn_dirControl_P = 2500; //�����������P
                Turn_dirControl_D = 5500; //�����������D

                TurnTimeDuring = 100;     //ת��ʱ�䳣������Ҫ�޸�ת��ʱ�䣬���޸����
                FreezingTimeDuring = 300; //����ʱ�䳣��
                DownTimeDuring = 175;     //����ʱ�䳣��

                Expect_P = 0.5; //1.25
                Expect_D = 0.6;

                TurnValue = (int)(275 * Environment);
            }
            if (SW1 && SW2 && !SW3 && SW4) //����
            {
                StraightExpectSpeed = 2800; //ֱ�������ٶ�
                TurnExpectSpeed = 2700;     //��������ٶ�
                DownSpeed = 2650;           //���������ٶ�

                g_dirControl_P = 3000; //�������P
                g_dirControl_D = 3200; //�������D

                Turn_dirControl_P = 3000; //�����������P
                Turn_dirControl_D = 6000; //�����������D

                TurnTimeDuring = 100;     //ת��ʱ�䳣������Ҫ�޸�ת��ʱ�䣬���޸����
                FreezingTimeDuring = 350; //����ʱ�䳣��
                DownTimeDuring = 175;     //����ʱ�䳣��

                Expect_P = 0.5; //1.25
                Expect_D = 0.6;

                TurnValue = (int)(275 * Environment);
            }
            if (!SW1 && !SW2 && SW3 && SW4) //����
            {
                StraightExpectSpeed = 3800; //ֱ�������ٶ�
                TurnExpectSpeed = 3700;     //��������ٶ�9
                DownSpeed = 3500;           //���������ٶ�

                g_dirControl_P = 3800; //�������P
                g_dirControl_D = 6800; //�������D2069622222222262090

                Turn_dirControl_P = 4500; //�����������P
                Turn_dirControl_D = 8500; //�����������D

                TurnTimeDuring = 100;     //ת��ʱ�䳣������Ҫ�޸�ת��ʱ�䣬���޸����
                FreezingTimeDuring = 220; //����ʱ�䳣��
                DownTimeDuring = 175;     //����ʱ�䳣��

                Expect_P = 0.5; //1.25
                Expect_D = 0.65;

                TurnValue = (int)(275 * Environment);
            }
            if (!SW1 && SW2 && !SW3 && SW4) //����+1
            {
                StraightExpectSpeed = 4200; //ֱ�������ٶ�
                TurnExpectSpeed = 3900;     //��������ٶ�9
                DownSpeed = 3900;           //���������ٶ�

                g_dirControl_P = 3500; //�������P
                g_dirControl_D = 6000; //�������D

                Turn_dirControl_P = 4500; //�����������P
                Turn_dirControl_D = 9000; //�����������D

                TurnTimeDuring = 100;     //ת��ʱ�䳣������Ҫ�޸�ת��ʱ�䣬���޸����
                FreezingTimeDuring = 200; //����ʱ�䳣��
                DownTimeDuring = 175;     //����ʱ�䳣��

                Expect_P = 0.5; //1.25
                Expect_D = 0.65;

                TurnValue = (int)(275 * Environment);
            }
            Flag_0--;
        }

        if (!SW4)
            Flag_Stop = ON;
    }
}
