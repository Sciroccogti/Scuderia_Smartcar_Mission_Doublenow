#ifndef __MY_OLED_H
#define __MY_OLED_H
#include "common.h"

void oled_p6x8char(uint8 x, uint8 y, const int8 ch);
void oled_p6x8char_highlight(uint8 x, uint8 y, const int8 ch);

void oled_p6x8int8(uint8 uc_posx, uint8 uc_posy, int8 c_data);
void oled_p6x8int8_highlight(uint8 uc_posx, uint8 uc_posy, int8 c_data);

void oled_p6x8int16_highlight(uint8 x, uint8 y, int16 num);

void oled_p6x8str_highlight(uint8 x,uint8 y,const int8 ch[]);

void oled_p8x16char(uint8 x,uint8 y,const int8 ch);
void oled_p8x16char_highlight(uint8 x,uint8 y,const int8 ch);

void oled_p8x16int8(uint8 uc_posx, uint8 uc_posy, int8 c_data);
void oled_p8x16int8_highlight(uint8 uc_posx, uint8 uc_posy, int8 c_data);

void oled_p8x16str_highlight(uint8 x,uint8 y,const int8 ch[]);

void oled_p8x16int16_highlight(uint8 x, uint8 y, int16 num);

#endif