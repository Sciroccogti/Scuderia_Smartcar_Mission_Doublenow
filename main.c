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
// KEA VERSION
//#include "headerfile.h"
// RT1064 VERSION
#include "myheader.h"
uint8 page = 0;
uint8 SW1, SW2, SW3, SW4;
uint8 UpFlag = 1, DownFlag = 1, LeftFlag = 1, RightFlag = 1, MidFlag = 1;

void display() {
    // need adc_init(ADC_1,ADC1_CH3_B14,ADC_8BIT); //初始化B14为ADC功能
    // 分辨率为8位 and adc_init(ADC_1,ADC1_CH4_B15,ADC_8BIT);
    // uint16 ad5 = adc_convert(ADC_1, ADC1_CH3_B14);
    // uint16 ad4=ADC_Read(ADC0_SE9);
    // uint16 ad3 = adc_convert(ADC_1, ADC1_CH4_B15);
    static uint8 last_D4 = 0;
    if (gpio_get(D4) != last_D4) {
        last_D4 = 1 - last_D4;
        lcd_clear(WHITE);
    }
    if (gpio_get(D4)) {
        char Left[10];
        char Right[10];
        char LeftMiddle[10];
        char RightMiddle[10];

        char LeftPwm[10];
        char RightPwm[10];

        char LeftSpeed[10];
        char RightSpeed[10];

        char SpeedOut[10];
        char DirOut[10];
        char Sonic[20];
        char Garage[20];

        sprintf(Left, "L:%04d", g_ValueOfAD[0]);          //水平左电感
        sprintf(Right, "R:%04d", g_ValueOfAD[1]);         //水平右电感
        sprintf(LeftMiddle, "LM:%04d", g_ValueOfAD[2]);   //水平左电感
        sprintf(RightMiddle, "RM:%04d", g_ValueOfAD[3]);  //水平右电感
        sprintf(LeftPwm, "LP:%05d", g_nLeftPWM);
        sprintf(RightPwm, "RP:%05d", g_nRighPWM);
        sprintf(LeftSpeed, "LS:%06d", (int16)g_fLeftRealSpeed);   //左轮脉冲
        sprintf(RightSpeed, "RS:%06d", (int16)g_fRighRealSpeed);  //右轮脉冲
        sprintf(SpeedOut, "SO:%05d", (int)g_fSpeedControlOut);
        sprintf(DirOut, "DO:%05d", (int)g_fDirectionControlOut);
        sprintf(Sonic, "sonic:%04dmm", distance);  // 超声波
        sprintf(Garage, "garage:%d", garage_count);  // 超声波

        lcd_showstr(0, 0, Left);
        lcd_showstr(64, 0, Right);
        lcd_showstr(0, 1, LeftMiddle);
        lcd_showstr(64, 1, RightMiddle);
        lcd_showstr(0, 2, LeftPwm);
        lcd_showstr(64, 2, RightPwm);
        lcd_showstr(0, 3, LeftSpeed);
        lcd_showstr(0, 4, RightSpeed);
        lcd_showstr(0, 5, SpeedOut);
        lcd_showstr(64, 5, DirOut);
        lcd_showstr(0, 6, Sonic);
        lcd_showstr(0, 7, Garage);
    } else {
        if (scc8660_csi_finish_flag)  //图像采集完成
        {
            scc8660_csi_finish_flag = 0;  //清除采集完成标志位

            //使用缩放显示函数，根据原始图像大小
            //以及设置需要显示的大小自动进行缩放或者放大显示
            //本例程默认采集分辨率为160*120，显示分辨率为160*128，纵向拉伸全屏
            lcd_displayimage8660_zoom(scc8660_csi_image[0], SCC8660_CSI_PIC_W,
                                      SCC8660_CSI_PIC_H, 160, 128);
        }
    }
}

//蓝牙参数监控
void BlueTooth() {
    char data[16];
    sprintf(data, "L:%d\n", (uint8)g_ValueOfAD[0]);
    uart_putbuff(USART_8, &data[0], sizeof(data));

    char data2[16];
    sprintf(data2, "R:%d\n", (uint8)g_ValueOfAD[1]);
    uart_putbuff(USART_8, &data2[0], sizeof(data2));

    /*
      uart_putbuff(USART_8,"g_fRealSpeed: ",18);
      UART_Putchar(USART_8,(uint8)g_fRealSpeed);
      UART_Putchar(USART_8,'\n');

      uart_putbuff(USART_8,"g_fSpeedControlOut: ",18);
      UART_Putchar(USART_8,(uint8)g_fSpeedControlOut);
      UART_Putchar(USART_8,'\n');

      uart_putbuff(USART_8,"g_nLeftPWM: ",14);
      UART_Putchar(USART_8,g_nLeftPWM);
      UART_Putchar(USART_8,'\n');

      uart_putbuff(USART_8,"g_nRighPWM: ",14);
      UART_Putchar(USART_8,g_nRighPWM);
      UART_Putchar(USART_8,'\n');

      UART_Putchar(USART_8,'\n');
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

    // RT1024 version
    oled_fill(0x00);  // clear
    oled_p8x16str(0, 6, DirP);
    oled_p8x16str(0, 4, DirD);

    // need info about ports for this part
    if (gpio_get(H3) == 0) g_dirControl_P -= 10;
    if (gpio_get(F7) == 0) g_dirControl_P += 10;
    if (gpio_get(H4) == 0) g_dirControl_D -= 10;
    if (gpio_get(F5) == 0) g_dirControl_D += 10;
}
void myoled2()

{
    char TurnDirP[16];
    char TurnDirD[16];

    sprintf(TurnDirP, "TurnDirP:%d", (int16)Turn_dirControl_P);
    sprintf(TurnDirD, "TurnDirD:%d", (int16)Turn_dirControl_D);

    // OLED_Display_Config(1);
    // OLED_Clear(0x00);
    /*//KEA128 version
    OLED_Show_String(8, 13, 0, 63, 1, TurnDirP, 0);
    OLED_Show_String(8, 13, 0, 32, 1, TurnDirD, 0);
    OLED_Refresh_Gram();
    */

    // RT1064 version
    oled_fill(0x00);  // clear
    oled_p8x16str(0, 6, TurnDirP);
    oled_p8x16str(0, 4, TurnDirD);

    // need info about ports for this part
    if (gpio_get(H3) == 0) Turn_dirControl_P -= 10;
    if (gpio_get(F7) == 0) Turn_dirControl_P += 10;
    if (gpio_get(H4) == 0) Turn_dirControl_D -= 10;
    if (gpio_get(F5) == 0) Turn_dirControl_D += 10;
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

    // RT1064 version
    oled_fill(0x00);  // clear
    oled_p8x16str(0, 6, Env);

    if (gpio_get(H4) == 0) {
        systick_delay_ms(20);
        Environment -= 0.05;
    }
    if (gpio_get(F5) == 0) {
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
    UART_Getchar(USART_8,&ch);

    switch(ch)
    {
    case 's':
      Flag_Stop= !Flag_Stop;
      break;


    case 'a':
      g_speedControl_P+=10;
      //uart_putbuff(USART_8,"g_speedControl_P: ",18);
      UART_Putchar(USART_8,(int32)g_speedControl_P);
      //UART_Putchar(USART_8,'\n');
      break;

    case 'b':
      g_speedControl_P-=10;
      uart_putbuff(USART_8,"g_speedControl_P: ",18);
      UART_Putchar(USART_8,(char)g_speedControl_P);
      UART_Putchar(USART_8,'\n');

      break;

    case 'c':
      g_speedControl_I+=10;
       uart_putbuff(USART_8,"g_speedControl_I: ",18);
      UART_Putchar(USART_8,(uint8)g_speedControl_I);
      UART_Putchar(USART_8,'\n');
      break;
    case 'd':
      g_speedControl_I-=10;
       uart_putbuff(USART_8,"g_speedControl_I: ",18);
      UART_Putchar(USART_8,(uint8)g_speedControl_I);
      UART_Putchar(USART_8,'\n');
      break;

    case 'e':
      g_dirControl_P+=10;
      uart_putbuff(USART_8,"g_dirControl_P: ",14);
      UART_Putchar(USART_8,(uint8)g_dirControl_P);
      UART_Putchar(USART_8,'\n');
      break;

    case 'f':
      g_dirControl_P-=10;
      uart_putbuff(USART_8,"g_dirControl_P: ",14);
      UART_Putchar(USART_8,(uint8)g_dirControl_P);
      UART_Putchar(USART_8,'\n');
      break;

    case 'g':
      g_dirControl_D+=10;
       uart_putbuff(USART_8,"g_dirControl_D: ",14);
      UART_Putchar(USART_8,(uint8)g_dirControl_D);
      UART_Putchar(USART_8,'\n');
      break;

    case 'h':
      g_dirControl_D-=10;
       uart_putbuff(USART_8,"g_dirControl_D: ",14);
      UART_Putchar(USART_8,(uint8)g_dirControl_D);
      UART_Putchar(USART_8,'\n');
      break;
    case 'r':
      uart_putbuff(USART_8,"g_speedControl_P: ",18);
      UART_Putchar(USART_8,(uint8)g_speedControl_P);
      UART_Putchar(USART_8,'\n');

       uart_putbuff(USART_8,"g_speedControl_I: ",18);
      UART_Putchar(USART_8,(uint8)g_speedControl_I);
      UART_Putchar(USART_8,'\n');

       uart_putbuff(USART_8,"g_dirControl_P: ",14);
      UART_Putchar(USART_8,(uint8)g_dirControl_P);
      UART_Putchar(USART_8,'\n');

       uart_putbuff(USART_8,"g_dirControl_D: ",14);
      UART_Putchar(USART_8,(uint8)g_dirControl_D);
      UART_Putchar(USART_8,'\n');
    default:
      break;
    }
}
*/

int main(void) {
    DisableGlobalIRQ();
    board_init();
    systick_delay_ms(220);
    car_init();

    EnableGlobalIRQ(0);

    Flag_Stop = ON;

    while (1) {
        display();
        BlueTooth();
        GarageDirection = gpio_get(D27);
        TurnAD0 = 2000, TurnAD1 = 2000, TurnAD2 = 1200,
        TurnAD3 = 1200;  //水平左右，垂直左右电感，判断是否到达环岛的阈值
        LeaveAD0 = 1300, LeaveAD1 = 1300, LeaveAD2 = 1000, LeaveAD3 = 1000;
        DownAD0 = 2000, DownAD1 = 2000, DownAD2 = 1200,
        DownAD3 = 1200;  //下坡判定电感值

        int Flag_0 = 1;
        if (Flag_0) {
            StraightExpectSpeed = 1500;  //直行期望速度
            TurnExpectSpeed = 1000;      //弯道期望速度
            DownSpeed = 1350;            //下坡期望速度

            g_dirControl_P = 3000;  //方向控制P
            g_dirControl_D = 3200;  //方向控制D

            Turn_dirControl_P = 3000;  //进岛方向控制P
            Turn_dirControl_D = 6000;  //进岛方向控制D

            TurnTimeDuring = 100;  //转向时间常量，若要修改转向时间，就修改这个
            FreezingTimeDuring = 350;  //冻结时间常量
            DownTimeDuring = 175;      //下坡时间常量

            Expect_P = 0.45;  // 1.25
            Expect_D = 0.55;
        }
    }

    /*
        // while ((1280 * ex_clk_khz) != (256 * ics_clk_khz));
       //确保时钟配置无误

        // UART_RX_IRQ_Enable(USART_8);
        Flag_Stop = ON;

        while (1) {
            // myoled();
            //五向开关调参

            BlueTooth();
            if (gpio_get(F4) == 0) {
                page++;
            }
            switch (page % 4) {
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

            // 0.5sLED闪烁
            static uint16 i = 0;
            i++;
            if (i >= 100) {
                // KEA VERSION
                // GPIO_Turn(LED_R);

                // RT1064 VERSION
                gpio_toggle(LED_R);
                i = 0;
            }

            //拨码开关换参
            //KEA VERSION
            // SW1 = gpio_get(C5);
            // SW2 = gpio_get(H7);
            // SW3 = gpio_get(H5);
            // SW4 = gpio_get(H2);


            // RT1064 VERSION
            SW1 = gpio_get(C5);  // C31
            SW2 = gpio_get(H7);  // B11
            SW3 = gpio_get(H5);  // C27
            SW4 = gpio_get(H2);  // C25

            TurnAD0 = 2000, TurnAD1 = 2000, TurnAD2 = 1200,
            TurnAD3 = 1200;  //水平左右，垂直左右电感，判断是否到达环岛的阈值
            LeaveAD0 = 1300, LeaveAD1 = 1300, LeaveAD2 = 1000, LeaveAD3 = 1000;
            DownAD0 = 2000, DownAD1 = 2000, DownAD2 = 1200,
            DownAD3 = 1200;  //下坡判定电感值

            int Flag_0 = 1;
            if (Flag_0) {
                if (SW1 && SW2 && SW3 && SW4)  //正常  摩擦不够可能漂移
                {
                    StraightExpectSpeed = 3700;  //直行期望速度
                    TurnExpectSpeed = 3600;      //弯道期望速度
                    DownSpeed = 3450;            //下坡期望速度

                    g_dirControl_P = 3000;  //方向控制P
                    g_dirControl_D = 5000;  //方向控制D

                    Turn_dirControl_P = 3000;  //进岛方向控制P
                    Turn_dirControl_D = 7000;  //进岛方向控制D

                    TurnTimeDuring =
                        100;  //转向时间常量，若要修改转向时间，就修改这个
                    FreezingTimeDuring = 250;  //冻结时间常量
                    DownTimeDuring = 175;      //下坡时间常量

                    Expect_P = 0.4;  // 1.25
                    Expect_D = 0.5;

                    TurnValue = (int)(275 * Environment);
                }
                if (!SW1 && SW2 && SW3 && SW4)  //稳
                {
                    StraightExpectSpeed = 3500;  //直行期望速度
                    TurnExpectSpeed = 3400;      //弯道期望速度9
                    DownSpeed = 3250;            //下坡期望速度

                    g_dirControl_P = 3000;  //方向控制P
                    g_dirControl_D = 3200;  //方向控制D

                    Turn_dirControl_P = 2500;  //进岛方向控制P
                    Turn_dirControl_D = 6000;  //进岛方向控制D

                    TurnTimeDuring =
                        100;  //转向时间常量，若要修改转向时间，就修改这个
                    FreezingTimeDuring = 250;  //冻结时间常量
                    DownTimeDuring = 175;      //下坡时间常量

                    Expect_P = 0.4;  // 1.25
                    Expect_D = 0.5;

                    TurnValue = (int)(275 * Environment);
                }
                if (SW1 && !SW2 && SW3 && SW4)  //更稳
                {
                    StraightExpectSpeed = 3200;  //直行期望速度
                    TurnExpectSpeed = 3100;      //弯道期望速度
                    DownSpeed = 2950;            //下坡期望速度

                    g_dirControl_P = 3000;  //方向控制P
                    g_dirControl_D = 3200;  //方向控制D

                    Turn_dirControl_P = 2500;  //进岛方向控制P
                    Turn_dirControl_D = 5500;  //进岛方向控制D

                    TurnTimeDuring =
                        100;  //转向时间常量，若要修改转向时间，就修改这个
                    FreezingTimeDuring = 300;  //冻结时间常量
                    DownTimeDuring = 175;      //下坡时间常量

                    Expect_P = 0.5;  // 1.25
                    Expect_D = 0.6;

                    TurnValue = (int)(275 * Environment);
                }
                if (SW1 && SW2 && !SW3 && SW4)  //最稳
                {
                    StraightExpectSpeed = 2800;  //直行期望速度
                    TurnExpectSpeed = 2700;      //弯道期望速度
                    DownSpeed = 2650;            //下坡期望速度

                    g_dirControl_P = 3000;  //方向控制P
                    g_dirControl_D = 3200;  //方向控制D

                    Turn_dirControl_P = 3000;  //进岛方向控制P
                    Turn_dirControl_D = 6000;  //进岛方向控制D

                    TurnTimeDuring =
                        100;  //转向时间常量，若要修改转向时间，就修改这个
                    FreezingTimeDuring = 350;  //冻结时间常量
                    DownTimeDuring = 175;      //下坡时间常量

                    Expect_P = 0.5;  // 1.25
                    Expect_D = 0.6;

                    TurnValue = (int)(275 * Environment);
                }
                if (!SW1 && !SW2 && SW3 && SW4)  //加速
                {
                    StraightExpectSpeed = 3800;  //直行期望速度
                    TurnExpectSpeed = 3700;      //弯道期望速度9
                    DownSpeed = 3500;            //下坡期望速度

                    g_dirControl_P = 3800;  //方向控制P
                    g_dirControl_D = 6800;  //方向控制D2069622222222262090

                    Turn_dirControl_P = 4500;  //进岛方向控制P
                    Turn_dirControl_D = 8500;  //进岛方向控制D

                    TurnTimeDuring =
                        100;  //转向时间常量，若要修改转向时间，就修改这个
                    FreezingTimeDuring = 220;  //冻结时间常量
                    DownTimeDuring = 175;      //下坡时间常量

                    Expect_P = 0.5;  // 1.25
                    Expect_D = 0.65;

                    TurnValue = (int)(275 * Environment);
                }
                if (!SW1 && SW2 && !SW3 && SW4)  //加速+1
                {
                    StraightExpectSpeed = 4200;  //直行期望速度
                    TurnExpectSpeed = 3900;      //弯道期望速度9
                    DownSpeed = 3900;            //下坡期望速度

                    g_dirControl_P = 3500;  //方向控制P
                    g_dirControl_D = 6000;  //方向控制D

                    Turn_dirControl_P = 4500;  //进岛方向控制P
                    Turn_dirControl_D = 9000;  //进岛方向控制D

                    TurnTimeDuring =
                        100;  //转向时间常量，若要修改转向时间，就修改这个
                    FreezingTimeDuring = 200;  //冻结时间常量
                    DownTimeDuring = 175;      //下坡时间常量

                    Expect_P = 0.5;  // 1.25
                    Expect_D = 0.65;

                    TurnValue = (int)(275 * Environment);
                }
                Flag_0--;
            }

            if (!SW4) Flag_Stop = ON;
        }*/
}
