#include "myoled.h"

#include "headfile.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED显示字符(6*8字体)
//  @param      x			x轴坐标设置0-127
//  @param      y           y轴坐标设置0-7
//  @param      ch          字符
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void oled_p6x8char(uint8 x, uint8 y, const int8 ch) {
    uint8 c = 0, i = 0;

    c = ch - 32;
    if (x > 126) {
        x = 0;
        y++;
    }
    oled_set_pos(x, y);
    for (i = 0; i < 6; i++) oled_wrdat(oled_6x8[c][i]);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED高亮显示字符(6*8字体)
//  @param      x			x轴坐标设置0-127
//  @param      y           y轴坐标设置0-7
//  @param      ch          字符
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void oled_p6x8char_highlight(uint8 x, uint8 y, const int8 ch) {
    uint8 c = 0, i = 0;

    c = ch - 32;
    if (x > 126) {
        x = 0;
        y++;
    }
    oled_set_pos(x, y);
    for (i = 0; i < 6; i++) oled_wrdat(~oled_6x8[c][i]);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED高亮显示字符串(6*8字体)
//  @param      x			x轴坐标设置0-127
//  @param      y           y轴坐标设置0-7
//  @param      ch[]        字符串
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void oled_p6x8str_highlight(uint8 x, uint8 y, const int8 ch[]) {
    uint8 c = 0, i = 0, j = 0;
    while (ch[j] != '\0') {
        c = ch[j] - 32;
        if (x > 126) {
            x = 0;
            y++;
        }
        oled_set_pos(x, y);
        for (i = 0; i < 6; i++) oled_wrdat(~oled_6x8[c][i]);
        x += 6;
        j++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED显示字符(8*16字体)
//  @param      x			x轴坐标设置0-127
//  @param      y           y轴坐标设置0-7
//  @param      ch          字符
//  @return     void
//  @since      v1.0
//  Sample usage:			务必注意，本函数字符列高位16，因此y应该是每次递增2
//-------------------------------------------------------------------------------------------------------------------
void oled_p8x16char(uint8 x, uint8 y, const int8 ch) {
    uint8 c = 0, i = 0;

    c = ch - 32;
    if (x > 120) {
        x = 0;
        y++;
    }

    oled_set_pos(x, y);
    for (i = 0; i < 8; i++) oled_wrdat(oled_8x16[c * 16 + i]);

    oled_set_pos(x, y + 1);
    for (i = 0; i < 8; i++) oled_wrdat(oled_8x16[c * 16 + i + 8]);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED高亮显示字符(8*16字体)
//  @param      x			x轴坐标设置0-127
//  @param      y           y轴坐标设置0-7
//  @param      ch          字符
//  @return     void
//  @since      v1.0
//  Sample usage:			务必注意，本函数字符列高位16，因此y应该是每次递增2
//-------------------------------------------------------------------------------------------------------------------
void oled_p8x16char_highlight(uint8 x, uint8 y, const int8 ch) {
    uint8 c = 0, i = 0;

    c = ch - 32;
    if (x > 120) {
        x = 0;
        y++;
    }

    oled_set_pos(x, y);
    for (i = 0; i < 8; i++) oled_wrdat(~oled_8x16[c * 16 + i]);

    oled_set_pos(x, y + 1);
    for (i = 0; i < 8; i++) oled_wrdat(~oled_8x16[c * 16 + i + 8]);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED高亮显示字符串(8*16字体)
//  @param      x			x轴坐标设置0-127
//  @param      y           y轴坐标设置0-7
//  @param      ch[]        字符串
//  @return     void
//  @since      v1.0
//  Sample usage:			务必注意，本函数字符列高位16，因此y应该是每次递增2
//-------------------------------------------------------------------------------------------------------------------
void oled_p8x16str_highlight(uint8 x, uint8 y, const int8 ch[]) {
    uint8 c = 0, i = 0, j = 0;

    while (ch[j] != '\0') {
        c = ch[j] - 32;
        if (x > 120) {
            x = 0;
            y++;
        }

        oled_set_pos(x, y);
        for (i = 0; i < 8; i++) oled_wrdat(~oled_8x16[c * 16 + i]);

        oled_set_pos(x, y + 1);
        for (i = 0; i < 8; i++) oled_wrdat(~oled_8x16[c * 16 + i + 8]);

        x += 8;
        j++;
    }
}

/**
 *  @ brief   oled_p6x8int8
 *
 *  @ param   uint8 uc_posx  显示的横坐标0~122
 *    		  uint8 uc_posy  页范围0～7
 *    		  int8  c_data   需要转化显示的数值 -128~127
 *
 *	@ note    将一个Char型数字转换成3位数字进行显示
 *
 *	@ return  void
 */
void oled_p6x8int8(uint8 uc_posx, uint8 uc_posy, int8 c_data) {
    uint16 i, j, k, us_data;

    if (c_data < 0) {
        oled_p6x8char(uc_posx, uc_posy, '-');
        us_data = (uint16)(-c_data);
    } else {
        oled_p6x8char(uc_posx, uc_posy, '+');
        us_data = (uint16)c_data;
    }

    i = us_data / 100;
    j = (us_data % 100) / 10;
    k = us_data % 10;

    oled_p6x8char(uc_posx + 6, uc_posy, i + 48);
    oled_p6x8char(uc_posx + 12, uc_posy, j + 48);
    oled_p6x8char(uc_posx + 18, uc_posy, k + 48);

    return;
}

/**
 *  @ brief   oled_p6x8int8_highlight
 *
 *  @ param   uint8 uc_posx  显示的横坐标0~122
 *    		  uint8 uc_posy  页范围0～7
 *    		  int8  c_data   需要转化显示的数值 -128~127
 *
 *	@ note    将一个Char型数字转换成3位数字进行显示
 *
 *	@ return  void
 */
void oled_p6x8int8_highlight(uint8 uc_posx, uint8 uc_posy, int8 c_data) {
    uint16 i, j, k, us_data;

    if (c_data < 0) {
        oled_p6x8char_highlight(uc_posx, uc_posy, '-');
        us_data = (uint16)(-c_data);
    } else {
        oled_p6x8char_highlight(uc_posx, uc_posy, '+');
        us_data = (uint16)c_data;
    }

    i = us_data / 100;
    j = (us_data % 100) / 10;
    k = us_data % 10;

    oled_p6x8char_highlight(uc_posx + 6, uc_posy, i + 48);
    oled_p6x8char_highlight(uc_posx + 12, uc_posy, j + 48);
    oled_p6x8char_highlight(uc_posx + 18, uc_posy, k + 48);

    return;
}

/**
 *  @ brief   oled_p8x16int8
 *
 *  @ param   uint8 uc_posx  显示的横坐标0~122
 *    		  uint8 uc_posy  页范围0～7
 *    		  int8  c_data   需要转化显示的数值 -128~127
 *
 *	@ note    将一个Char型数字转换成3位数字进行显示
 *
 *	@ return  void
 */
void oled_p8x16int8(uint8 uc_posx, uint8 uc_posy, int8 c_data) {
    uint16 i, j, k, us_data;

    if (c_data < 0) {
        oled_p8x16char(uc_posx, uc_posy, '-');
        us_data = (uint16)(-c_data);
    } else {
        oled_p6x8char(uc_posx, uc_posy, '+');
        us_data = (uint16)c_data;
    }

    i = us_data / 100;
    j = (us_data % 100) / 10;
    k = us_data % 10;

    oled_p8x16char(uc_posx + 8, uc_posy, i + 48);
    oled_p8x16char(uc_posx + 16, uc_posy, j + 48);
    oled_p8x16char(uc_posx + 24, uc_posy, k + 48);

    return;
}

/**
 *  @ brief   oled_p8x16int8_highlight
 *
 *  @ param   uint8 uc_posx  显示的横坐标0~122
 *    		  uint8 uc_posy  页范围0～7
 *    		  int8  c_data   需要转化显示的数值 -128~127
 *
 *	@ note    将一个Char型数字转换成3位数字进行显示
 *
 *	@ return  void
 */
void oled_p8x16int8_highlight(uint8 uc_posx, uint8 uc_posy, int8 c_data) {
    uint16 i, j, k, us_data;

    if (c_data < 0) {
        oled_p8x16char(uc_posx, uc_posy, '-');
        us_data = (uint16)(-c_data);
    } else {
        oled_p6x8char(uc_posx, uc_posy, '+');
        us_data = (uint16)c_data;
    }

    i = us_data / 100;
    j = (us_data % 100) / 10;
    k = us_data % 10;

    oled_p8x16char_highlight(uc_posx + 8, uc_posy, i + 48);
    oled_p8x16char_highlight(uc_posx + 16, uc_posy, j + 48);
    oled_p8x16char_highlight(uc_posx + 24, uc_posy, k + 48);

    return;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED高亮显示有符号数(6*8字体)
//  @param      x			x轴坐标设置0-127
//  @param      y           y轴坐标设置0-7
//  @param      num         有符号数
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void oled_p6x8int16_highlight(uint8 x, uint8 y, int16 num) {
    int8 ch[7];
    if (num < 0) {
        num = -num;
        oled_p6x8str(x, y, "-");
    } else
        oled_p6x8str(x, y, " ");
    x += 6;

    oled_hexascii(num, ch);
    oled_p6x8str_highlight(x, y, &ch[1]);  //高亮显示数字  6*8字体
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED高亮显示有符号数(8*16字体)
//  @param      x			x轴坐标设置0-127
//  @param      y           y轴坐标设置0-7
//  @param      num         有符号数
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void oled_p8x16int16_highlight(uint8 x, uint8 y, int16 num) {
    int8 ch[7];
    if (num < 0) {
        num = -num;
        oled_p8x16str(x, y, "-");
    } else
        oled_p8x16str(x, y, " ");
    x += 8;

    oled_hexascii(num, ch);
    oled_p8x16str_highlight(x, y, &ch[1]);  //高亮显示数字  8*16字体
}