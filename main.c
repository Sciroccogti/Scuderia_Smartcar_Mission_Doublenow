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

//int mode = 1;

void display()
{
    // need adc_init(ADC_1,ADC1_CH3_B14,ADC_8BIT); //初始化B14为ADC功能
    // 分辨率为8位 and adc_init(ADC_1,ADC1_CH4_B15,ADC_8BIT);
    // uint16 ad5 = adc_convert(ADC_1, ADC1_CH3_B14);
    // uint16 ad4=ADC_Read(ADC0_SE9);
    // uint16 ad3 = adc_convert(ADC_1, ADC1_CH4_B15);

    // 拨码开关 D4 控制显示摄像头还是数据
    // static uint8 last_D4 = 0;
    // if (gpio_get(D4) != last_D4) {
    //     last_D4 = 1 - last_D4;
    //     lcd_clear(WHITE);
    // }
    // if (gpio_get(D4)) {
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
    char Garagedirection[10];

    sprintf(Left, "L:%04d", g_ValueOfAD[0]);         //水平左电感
    sprintf(Right, "R:%04d", g_ValueOfAD[1]);        //水平右电感
    sprintf(LeftMiddle, "LM:%04d", g_ValueOfAD[2]);  //水平左电感
    sprintf(RightMiddle, "RM:%04d", g_ValueOfAD[3]); //水平右电感
    sprintf(LeftPwm, "LP:%05d", g_nLeftPWM);
    sprintf(RightPwm, "RP:%05d", g_nRighPWM);
    sprintf(LeftSpeed, "LS:%06d", (int16)g_fLeftRealSpeed);  //左轮脉冲
    sprintf(RightSpeed, "RS:%06d", (int16)g_fRighRealSpeed); //右轮脉冲
    sprintf(SpeedOut, "SO:%05d", (int)g_fSpeedControlOut);
    sprintf(DirOut, "DO:%05d", (int)g_fDirectionControlOut);
    sprintf(Sonic, "sonic:%04dmm", distance); // 超声波

    if (garage_count == 0)
    {
        sprintf(Garage, "in gar"); // 车库内
    }
    else if (garage_count == 1)
    {
        sprintf(Garage, "gar turn"); // 出车库中
    }
    else
    {
        sprintf(Garage, "out gar"); // 已出车库
    }

    if (GarageDirection)
    {
        sprintf(Garagedirection, "RIGHT");
    }
    else
    {
        sprintf(Garagedirection, "LEFT ");
    }

    lcd_showstr(0, 0, Left);
    lcd_showstr(80, 0, Right);
    lcd_showstr(0, 1, LeftMiddle);
    lcd_showstr(80, 1, RightMiddle);
    lcd_showstr(0, 2, LeftPwm);
    lcd_showstr(80, 2, RightPwm);
    lcd_showstr(0, 3, LeftSpeed);
    lcd_showstr(80, 3, RightSpeed);
    lcd_showstr(0, 4, SpeedOut);
    lcd_showstr(80, 4, DirOut);
    lcd_showstr(0, 5, Sonic);
    lcd_showstr(0, 6, Garage);
    lcd_showstr(80, 6, Garagedirection);
    lcd_showint8(0, 7, mode);
    lcd_showfloat(80, 7, TurnTime, 6, 0);
    // } else {
    //     if (scc8660_csi_finish_flag)  //图像采集完成
    //     {
    //         scc8660_csi_finish_flag = 0;  //清除采集完成标志位

    //         //使用缩放显示函数，根据原始图像大小
    //         //以及设置需要显示的大小自动进行缩放或者放大显示
    //         //本例程默认采集分辨率为160*120，显示分辨率为160*128，纵向拉伸全屏
    //         lcd_displayimage8660_zoom(scc8660_csi_image[0], SCC8660_CSI_PIC_W,
    //                                   SCC8660_CSI_PIC_H, 160, 128);
    //     }
    // }
}

//蓝牙参数监控
void BlueTooth()
{
    // uint8 i;
    // for(i = 0; i < 4; i++){
    //     OutData[i] = g_ValueOfAD[i];
    // }

    // OutPut_Data();
    // data_conversion(g_ValueOfAD[0], g_ValueOfAD[1], g_ValueOfAD[2],
    // g_ValueOfAD[3], virtual_scope_data); int8 data[2] = {0,0x5a};
    // sprintf(data, "L:%d\n", (uint8)g_ValueOfAD[0]);
    // uart_putbuff(USART_8, data, 8);
    // uart_putstr(USART_8, "12");

    // char data2[16];
    // sprintf(data2, "R:%d\n", (uint8)g_ValueOfAD[1]);
    // uart_putbuff(USART_8, &data2[0], sizeof(data2));
    // uart_putstr(USART_8, data2);

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

int main(void)
{
    DisableGlobalIRQ();
    board_init();
    systick_delay_ms(220);
    car_init();

    EnableGlobalIRQ(0);

    Flag_Stop = ON;

    while (1)
    {
        display();
        BlueTooth();
        GarageDirection = gpio_get(C31);
        TurnAD0 = 2900, TurnAD1 = 2900, TurnAD2 = 3400,
        TurnAD3 = 3400; //水平左右，垂直左右电感，判断是否到达环岛的阈值
        LeaveAD0 = 2600, LeaveAD1 = 2600, LeaveAD2 = 2000, LeaveAD3 = 2000;
        DownAD0 = 4000, DownAD1 = 4000, DownAD2 = 2400,
        DownAD3 = 2400; //下坡判定电感值

        // 转向时间常量，若要修改转向时间，就修改这个

        if (gpio_get(B23))
        {
            mode++;
        }
        else if (gpio_get(B21))
        {
            mode--;
        }

        switch (mode)
        {
        case 3:
        {
            StraightExpectSpeed = 3800; //直行期望速度
            TurnExpectSpeed = 3300;     //弯道期望速度 3400
            DownSpeed = 2650;           //下坡期望速度
            // outPWM1 = 250;
            // outPWM2 = 300;
            // diffPWM = 700;
            //TurnValue =
            g_dirControl_P = 3000; //方向控制P
            g_dirControl_D = 3200; //方向控制D

            Turn_dirControl_P = 3000; //进岛方向控制P
            Turn_dirControl_D = 6000; //进岛方向控制D

            TurnTimeDuring = 320000 / (g_fRealSpeed);
            FreezingTimeDuring = 350; //冻结时间常量
            DownTimeDuring = 175;     //下坡时间常量

            //TurnValue = 800;

            Expect_P = (g_fSpeedError > -50) ? 0.8 : 27; // 1.25
            Expect_I = (g_fSpeedError > 3000 || g_fSpeedError < -300 ? 0.2 : 0);
            Expect_D = 0.8;

            Kdirection = 1.2;

            TurnValue = (int)(215 * Environment);

//            Expect_P = 0.8; // 1.25  0.8
//                            //             Expect_I = (g_fSpeedError > 2400 ||g_fSpeedError < -2400? 0.002 : 0);
//            Expect_I = 0;
//            Expect_D = 1.1; //1.1

//            Kdirection = 1;

//            TurnValue = (int)(275 * Environment);
        }
        break;
        case 2:
        {
            StraightExpectSpeed = 3500; //直行期望速度
            TurnExpectSpeed = 2800;     //弯道期望速度
            DownSpeed = 2650;           //下坡期望速度
            // outPWM1 = 250;
            // outPWM2 = 300;
            // diffPWM = 700;
            //TurnValue =
            g_dirControl_P = 3000; //方向控制P
            g_dirControl_D = 3200; //方向控制D

            Turn_dirControl_P = 3000; //进岛方向控制P
            Turn_dirControl_D = 6000; //进岛方向控制D

            TurnTimeDuring = 300000 / (g_fRealSpeed);
            FreezingTimeDuring = 350; //冻结时间常量
            DownTimeDuring = 175;     //下坡时间常量

            TurnValue = 800;

            Expect_P = (g_fSpeedError > 0) ? 0.8 : 4; // 1.25
            Expect_I = (g_fSpeedError > 3000 || g_fSpeedError < -200 ? 0.1 : 0);
            Expect_D = 0.8;

            Kdirection = 1;

            TurnValue = (int)(275 * Environment);
        }
        break;
        case 1:
        {
            StraightExpectSpeed = 2800; //直行期望速度
            TurnExpectSpeed = 2500;     //弯道期望速度
            DownSpeed = 2650;           //下坡期望速度
            // outPWM1 = 250;
            // outPWM2 = 300;
            // diffPWM = 700;

            g_dirControl_P = 3000; //方向控制P
            g_dirControl_D = 3200; //方向控制D

            Turn_dirControl_P = 3000; //进岛方向控制P
            Turn_dirControl_D = 6000; //进岛方向控制D

            TurnTimeDuring = 300000 / (StraightExpectSpeed);
            FreezingTimeDuring = 350; //冻结时间常量
            DownTimeDuring = 175;     //下坡时间常量

            Expect_P = 0.6;                                // 1.25
            Expect_I = (g_fSpeedError > 2000 ? 0.002 : 0); //限制只有上坡的时候才会用到I，I的值为0.0015
            Expect_D = 0.8;

            Kdirection = 1;

            TurnValue = (int)(300 * Environment);
        }
        break;
        case 0:
        default:
        {                               // 最稳
            StraightExpectSpeed = 1500; //直行期望速度
            TurnExpectSpeed = 1000;     //弯道期望速度
            DownSpeed = 1350;           //下坡期望速度
            // outPWM1 = 200;
            // outPWM2 = 300;
            // diffPWM = 700;

            g_dirControl_P = 3000; //方向控制P
            g_dirControl_D = 3200; //方向控制D

            Turn_dirControl_P = 3000; //进岛方向控制P
            Turn_dirControl_D = 6000; //进岛方向控制D

            TurnTimeDuring = 300000 / (StraightExpectSpeed);
            FreezingTimeDuring = 350; //冻结时间常量
            DownTimeDuring = 175;     //下坡时间常量

            Expect_P = 0.45; // 1.25
            Expect_I = 0.0015;
            Expect_D = 0.8;
            Kdirection = 0.2;
        }
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
