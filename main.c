/*********************************************************************************************************************
 * 
 * @file       		main.c
 *  				主函数
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
#include "myheader.h"
uint8 page = 0;
uint8 SW1, SW2, SW3, SW4;
uint8 UpFlag = 1, DownFlag = 1, LeftFlag = 1, RightFlag = 1, MidFlag = 1;

void myoled()
{
    //need adc_init(ADC_1,ADC1_CH3_B14,ADC_8BIT); //初始化B14为ADC功能 分辨率为8位
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

    sprintf(Left, "L:%d", g_ValueOfAD[0]);         //水平左电感
    sprintf(Right, "R:%d", g_ValueOfAD[1]);        //水平右电感
    sprintf(LeftMiddle, "LM:%d", g_ValueOfAD[2]);  //水平左电感
    sprintf(RightMiddle, "RM:%d", g_ValueOfAD[3]); //水平右电感
                                                  //sprintf(LeftPwm,"LP:%d",LeftP);
                                                  //sprintf(LeftPwm,"RP:%d",RightP);
                                                  //sprintf(LeftPwm,"LP:%d",(int16)g_fLeftRealSpeed);//左轮脉冲
                                                  //sprintf(RightPwm,"RP:%d",(int16)g_fRighRealSpeed);//右轮脉冲
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
    //need adc_init(ADC_1,ADC1_CH3_B14,ADC_8BIT); //初始化B14为ADC功能 分辨率为8位
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

    sprintf(Left, "L:%d", g_ValueOfAD[0]);         //水平左电感
    sprintf(Right, "R:%d", g_ValueOfAD[1]);        //水平右电感
    sprintf(LeftMiddle, "LM:%d", g_ValueOfAD[2]);  //水平左电感
    sprintf(RightMiddle, "RM:%d", g_ValueOfAD[3]); //水平右电感
                                                  //sprintf(LeftPwm,"LP:%d",LeftP);
                                                  //sprintf(LeftPwm,"RP:%d",RightP);
                                                  //sprintf(LeftPwm,"LP:%d",(int16)g_fLeftRealSpeed);//左轮脉冲
                                                  //sprintf(RightPwm,"RP:%d",(int16)g_fRighRealSpeed);//右轮脉冲
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

//蓝牙参数监控
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

// 逐飞无五向开关
// void myoled4()

// {
//     char TurnTD[16];
//     char FreezeTD[16];

//     sprintf(TurnTD, "TTDur:%d", (int16)TurnTimeDuring);
//     sprintf(FreezeTD, "FTDur:%d", (int16)FreezingTimeDuring);

//     /*//KEA128 version
//     OLED_Display_Config(1);
//     OLED_Clear(0x00);
//     OLED_Show_String(8, 13, 0, 63, 1, TurnTD, 0);
//     OLED_Show_String(8, 13, 0, 32, 1, FreezeTD, 0);
//     OLED_Refresh_Gram();
//     */

//     //RT1064 version
//     oled_fill(0x00); //clear
//     oled_p8x16str(0, 6, TurnTD);
//     oled_p8x16str(0, 4, FreezeTD);

//     if (gpio_get(H3) == 0)
//         TurnTimeDuring += 10;
//     if (gpio_get(F7) == 0)
//         TurnTimeDuring -= 10;
//     if (gpio_get(H4) == 0)
//         FreezingTimeDuring += 10;
//     if (gpio_get(F5) == 0)
//         FreezingTimeDuring -= 10;
// }

//蓝牙接受中断
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

    //while ((1280 * ex_clk_khz) != (256 * ics_clk_khz)); //确保时钟配置无误

    //UART_RX_IRQ_Enable(uart2);
    Flag_Stop = ON;

    while (1)
    {

        //myoled();
        //五向开关调参

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

        //0.5sLED闪烁
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

        //拨码开关换参
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

        TurnAD0 = 2000, TurnAD1 = 2000, TurnAD2 = 1200, TurnAD3 = 1200; //水平左右，垂直左右电感，判断是否到达环岛的阈值
        LeaveAD0 = 1300, LeaveAD1 = 1300, LeaveAD2 = 1000, LeaveAD3 = 1000;
        DownAD0 = 2000, DownAD1 = 2000, DownAD2 = 1200, DownAD3 = 1200; //下坡判定电感值

        int Flag_0 = 1;
        if (Flag_0)
        {
            if (SW1 && SW2 && SW3 && SW4) //正常  摩擦不够可能漂移
            {
                StraightExpectSpeed = 3700; //直行期望速度
                TurnExpectSpeed = 3600;     //弯道期望速度
                DownSpeed = 3450;           //下坡期望速度

                g_dirControl_P = 3000; //方向控制P
                g_dirControl_D = 5000; //方向控制D

                Turn_dirControl_P = 3000; //进岛方向控制P
                Turn_dirControl_D = 7000; //进岛方向控制D

                TurnTimeDuring = 100;     //转向时间常量，若要修改转向时间，就修改这个
                FreezingTimeDuring = 250; //冻结时间常量
                DownTimeDuring = 175;     //下坡时间常量

                Expect_P = 0.4; //1.25
                Expect_D = 0.5;

                TurnValue = (int)(275 * Environment);
            }
            if (!SW1 && SW2 && SW3 && SW4) //稳
            {
                StraightExpectSpeed = 3500; //直行期望速度
                TurnExpectSpeed = 3400;     //弯道期望速度9
                DownSpeed = 3250;           //下坡期望速度

                g_dirControl_P = 3000; //方向控制P
                g_dirControl_D = 3200; //方向控制D

                Turn_dirControl_P = 2500; //进岛方向控制P
                Turn_dirControl_D = 6000; //进岛方向控制D

                TurnTimeDuring = 100;     //转向时间常量，若要修改转向时间，就修改这个
                FreezingTimeDuring = 250; //冻结时间常量
                DownTimeDuring = 175;     //下坡时间常量

                Expect_P = 0.4; //1.25
                Expect_D = 0.5;

                TurnValue = (int)(275 * Environment);
            }
            if (SW1 && !SW2 && SW3 && SW4) //更稳
            {
                StraightExpectSpeed = 3200; //直行期望速度
                TurnExpectSpeed = 3100;     //弯道期望速度
                DownSpeed = 2950;           //下坡期望速度

                g_dirControl_P = 3000; //方向控制P
                g_dirControl_D = 3200; //方向控制D

                Turn_dirControl_P = 2500; //进岛方向控制P
                Turn_dirControl_D = 5500; //进岛方向控制D

                TurnTimeDuring = 100;     //转向时间常量，若要修改转向时间，就修改这个
                FreezingTimeDuring = 300; //冻结时间常量
                DownTimeDuring = 175;     //下坡时间常量

                Expect_P = 0.5; //1.25
                Expect_D = 0.6;

                TurnValue = (int)(275 * Environment);
            }
            if (SW1 && SW2 && !SW3 && SW4) //最稳
            {
                StraightExpectSpeed = 2800; //直行期望速度
                TurnExpectSpeed = 2700;     //弯道期望速度
                DownSpeed = 2650;           //下坡期望速度

                g_dirControl_P = 3000; //方向控制P
                g_dirControl_D = 3200; //方向控制D

                Turn_dirControl_P = 3000; //进岛方向控制P
                Turn_dirControl_D = 6000; //进岛方向控制D

                TurnTimeDuring = 100;     //转向时间常量，若要修改转向时间，就修改这个
                FreezingTimeDuring = 350; //冻结时间常量
                DownTimeDuring = 175;     //下坡时间常量

                Expect_P = 0.5; //1.25
                Expect_D = 0.6;

                TurnValue = (int)(275 * Environment);
            }
            if (!SW1 && !SW2 && SW3 && SW4) //加速
            {
                StraightExpectSpeed = 3800; //直行期望速度
                TurnExpectSpeed = 3700;     //弯道期望速度9
                DownSpeed = 3500;           //下坡期望速度

                g_dirControl_P = 3800; //方向控制P
                g_dirControl_D = 6800; //方向控制D2069622222222262090

                Turn_dirControl_P = 4500; //进岛方向控制P
                Turn_dirControl_D = 8500; //进岛方向控制D

                TurnTimeDuring = 100;     //转向时间常量，若要修改转向时间，就修改这个
                FreezingTimeDuring = 220; //冻结时间常量
                DownTimeDuring = 175;     //下坡时间常量

                Expect_P = 0.5; //1.25
                Expect_D = 0.65;

                TurnValue = (int)(275 * Environment);
            }
            if (!SW1 && SW2 && !SW3 && SW4) //加速+1
            {
                StraightExpectSpeed = 4200; //直行期望速度
                TurnExpectSpeed = 3900;     //弯道期望速度9
                DownSpeed = 3900;           //下坡期望速度

                g_dirControl_P = 3500; //方向控制P
                g_dirControl_D = 6000; //方向控制D

                Turn_dirControl_P = 4500; //进岛方向控制P
                Turn_dirControl_D = 9000; //进岛方向控制D

                TurnTimeDuring = 100;     //转向时间常量，若要修改转向时间，就修改这个
                FreezingTimeDuring = 200; //冻结时间常量
                DownTimeDuring = 175;     //下坡时间常量

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
