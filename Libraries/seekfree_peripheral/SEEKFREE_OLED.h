/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		OLED
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 * @note		
					接线定义：
					------------------------------------ 
					    OLED液晶    单片机                        
    					D0          查看SEEKFREE_OLED文件内的OLED_SCL_PIN   宏定义
    					D1          查看SEEKFREE_OLED文件内的OLED_SDA_PIN   宏定义            
    					RES         查看SEEKFREE_OLED文件内的OLED_RST_PIN   宏定义    
    					DC          查看SEEKFREE_OLED文件内的OLED_DC_PIN    宏定义
						CS          查看SEEKFREE_OLED文件内的OLED_CS_PIN    宏定义
					------------------------------------ 
 ********************************************************************************************************************/



#ifndef _SEEKFREE_OLED_h
#define _SEEKFREE_OLED_h


#include "common.h"




//----宏定义OLED引脚----	 
#define  OLED_SCL_PIN	B0
#define  OLED_SDA_PIN	B1
#define  OLED_RST_PIN	B2
#define  OLED_DC_PIN	C19
#define  OLED_CS_PIN	B3

                            
                            
//定义显示方向
//0 横屏模式
//1 横屏模式  旋转180
#define OLED_DISPLAY_DIR 0

#if (0==OLED_DISPLAY_DIR || 1==OLED_DISPLAY_DIR)
#define X_WIDTH         128
#define Y_WIDTH         64

#else
#error "OLED_DISPLAY_DIR 定义错误"
     
#endif
                            
#define	Brightness	    0x7f    //设置OLED亮度  越大越亮    范围0-0XFF                            
#define XLevelL		    0x00
#define XLevelH		    0x10
#define XLevel		    ((XLevelH&0x0F)*16+XLevelL)
#define Max_Column	    128
#define Max_Row		    64

// 内部调用，用户无需关心
void oled_wrdat(uint8 data);
void oled_hexascii(uint16 hex,int8 * Print);

void oled_init(void);     
void oled_fill(uint8 dat);
void oled_set_pos(uint8 x, uint8 y);
void oled_putpixel(uint8 x,uint8 y,uint8 data1);
void oled_clrpixel(uint8 x,uint8 y);
void oled_p6x8str(uint8 x,uint8 y,const int8 ch[]);
void oled_p8x16str(uint8 x,uint8 y,const int8 ch[]);
void oled_uint16(uint8 x, uint8 y, uint16 num);
void oled_int16(uint8 x, uint8 y, int16 num);
void oled_printf_int32(uint16 x,uint16 y,int32 dat,uint8 num);
void oled_printf_float(uint16 x,uint16 y,double dat,uint8 num,uint8 pointnum);
void oled_dis_bmp(uint16 high, uint16 width, uint8 *p,uint8 value);
void oled_print_chinese(uint8 x, uint8 y, uint8 size, const uint8 *p, uint8 len);


/********************************************************************/

#endif
