/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		isr
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/

#ifndef _isr_h
#define _isr_h

//外部使用本文件的全局变量在此申明
/**************全局变量外部申明*****************/

extern uint8 Flag_Stop;
extern uint8 sonic_rx_buffer;
extern uint16 distance;
extern lpuart_transfer_t   sonic_receivexfer;
extern lpuart_handle_t     sonic_g_lpuartHandle;


extern uint8 bluetooth_rx_buffer;
extern lpuart_transfer_t   bluetooth_receivexfer;
extern lpuart_handle_t     bluetooth_g_lpuartHandle;

void PIT_Interrupt(void);
void Interrupt_Test(uint8 h);
void sonic_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData);
void bluetooth_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData);

#endif