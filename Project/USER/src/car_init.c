#include "myheader.h"

// TODO: 上电时序
void car_init() {
    DisableGlobalIRQ();

    // ADC初始化
    // adc_init(AD1,ADC_12BIT);
    adc_init(ADC_1, AD2, ADC_12BIT);  // 垂直右
    adc_init(ADC_1, AD3, ADC_12BIT);  // 水平左
    adc_init(ADC_1, AD4, ADC_12BIT);  // 垂直左
    adc_init(ADC_1, AD5, ADC_12BIT);  // 水平右

    //五向开关初始化
    // gpio_init(H4, GPI, 1, GPIO_PIN_CONFIG);  //上
    // gpio_init(F5, GPI, 1, GPIO_PIN_CONFIG);  //下
    // gpio_init(H3, GPI, 1, GPIO_PIN_CONFIG);  //左
    // gpio_init(F7, GPI, 1, GPIO_PIN_CONFIG);  //右
    // gpio_init(F4, GPI, 1, GPIO_PIN_CONFIG);  //中
    // OLED初始化
    // oled_init();
    lcd_init();

    // flash初始化
    flash_init();

    /*红外线初始化
    ir_init();
    set_irq_priority(IRQ_IRQn, 0);
    //设置优先级,根据自己的需求设置可设置范围为 0 - 3 enable_irq(IRQ_IRQn);*/

    //蜂鸣器初始化
    gpio_init(B11, GPO, 0, GPIO_PIN_CONFIG);

    //停车干簧管初始化
    // gpio_init(I0, GPI, 1, GPIO_PIN_CONFIG);
    // gpio_init(H1, GPO, 0, GPIO_PIN_CONFIG);
    //环岛指示灯初始化
    // gpio_init(H0, GPO, 0, GPIO_PIN_CONFIG);
    // gpio_init(E6, GPO, 0, GPIO_PIN_CONFIG);

    // LED初始化
    gpio_init(B9, GPO, 0, GPIO_PIN_CONFIG);  // 核心板蓝色

    //蓝牙串口初始化
    uart_init(USART_8, 115200, UART8_TX_D16, UART8_RX_D17);

    // UART_Init(uart0,9600,RXTX_B0B1);

    //拨码开关或备用接口初始化(复用为拨码开关或备用接口)，K1-4若用于备用接口则改为GPO;
    gpio_init(C5, GPI, 1, GPIO_PIN_CONFIG);  // 1
    gpio_init(H7, GPI, 1, GPIO_PIN_CONFIG);  // 2
    gpio_init(H5, GPI, 1, GPIO_PIN_CONFIG);  // 3
    gpio_init(H2, GPI, 1, GPIO_PIN_CONFIG);  // 4

    //电机初始化
    pwm_init(PWM1_MODULE3_CHB_D1, 14000, 0);
    pwm_init(PWM1_MODULE3_CHA_D0, 14000, 0);
    pwm_init(PWM2_MODULE3_CHB_D3, 14000, 0);
    pwm_init(PWM2_MODULE3_CHA_D2, 14000, 0);

    //左编码器初始化
    //右编码器初始化

    // FTM 脉冲计数
    //一个QTIMER可以 创建两个正交解码
    //初始化 QTIMER_1 A相使用QTIMER1_TIMER0_C0 B相使用QTIMER1_TIMER1_C1
    qtimer_quad_init(QTIMER_1, QTIMER1_TIMER0_C0, QTIMER1_TIMER1_C1);

    //初始化 QTIMER_1 A相使用QTIMER1_TIMER2_C2 B相使用QTIMER1_TIMER3_C24
    qtimer_quad_init(QTIMER_1, QTIMER1_TIMER2_C2, QTIMER1_TIMER3_C24);
    gpio_init(E1, GPI, HIGH, GPIO_PIN_CONFIG);
    gpio_init(H6, GPI, HIGH, GPIO_PIN_CONFIG);

    // 摄像头初始化
    scc8660_csi_init();
    //延时2s
    systick_delay_ms(500);
    gpio_set(B9, 1);

    //定时器初始化
    pit_init();                       //初始化pit外设
    pit_interrupt_ms(PIT_CH0, 5);  //初始化pit通道0 周期
    // PIT_SetCallback(PIT_Interrupt);
    NVIC_SetPriority(PIT_IRQn,15);      ///设置中断优先级 范围0-15
    // 越小优先级越高 四路PIT共用一个PIT中断函数
    EnableGlobalIRQ(0);  //使能中断

}