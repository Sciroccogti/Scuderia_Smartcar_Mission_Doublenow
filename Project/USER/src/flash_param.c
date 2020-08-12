/*********************************************************************************************************************
 * 
 * @file       		flash_param.c
 *  				flash参数存取
 * @core			S9KEA128
 * @date       		2018
 ********************************************************************************************************************/
#include "common.h"
#include "zf_flash.h"
#include "myheader.h"

void param_in(void)
{
  param_load(&parameter);  //从flash里读数据存到结构体里面去
  set_param(&parameter);   //再从结构体中读出数据
}

void param_load(struct PARAM * p_param)    //把flash数据存到结构体里面去
{
    p_param->int01  = flash_read(255, 0,uint32);
    p_param->int02  = flash_read(255, 4,uint32);
    p_param->int03  = flash_read(255, 8,uint32);
    p_param->int04  = flash_read(255,12,uint32);
    p_param->int05  = flash_read(255,16,uint32);
    p_param->int06  = flash_read(255,20,uint32);
    p_param->int07  = flash_read(255,24,uint32);
    p_param->int08  = flash_read(255,28,uint32);
    p_param->int09  = flash_read(255,32,uint32);
    p_param->int10  = flash_read(255,36,uint32);
    p_param->int11  = flash_read(255,40,uint32);
    p_param->int12  = flash_read(255,44,uint32);    
    
    p_param->float01  = flash_read(255,48,uint32);
    p_param->float02  = flash_read(255,52,uint32);
    p_param->float03  = flash_read(255,56,uint32);
    p_param->float04  = flash_read(255,60,uint32);
    p_param->float05  = flash_read(255,64,uint32);
    p_param->float06  = flash_read(255,68,uint32);
    p_param->float07  = flash_read(255,72,uint32);
    p_param->float08  = flash_read(255,76,uint32);
    p_param->float09  = flash_read(255,80,uint32);
    p_param->float10  = flash_read(255,84,uint32);
    p_param->float11  = flash_read(255,88,uint32);
    p_param->float12  = flash_read(255,92,uint32);
    
    p_param->param_flag =flash_read(253,0,uint32);
    
}

void set_param(struct PARAM *p_param)   //从结构体中读数据存到相应的变量中
{
    int01=(p_param->int01);
    int02=(p_param->int02);
    int03=(p_param->int03);
    int04=(p_param->int04);
    int05=(p_param->int05);
    int06=(p_param->int06);
    int07=(p_param->int07);
    int08=(p_param->int08);
    int09=(p_param->int09);
    int10=(p_param->int10);
    int11=(p_param->int11);
    int12=(p_param->int12);
    
    float01=(float)(p_param->float01);
    float02=(float)(p_param->float02);
    float03=(float)(p_param->float03);
    float04=(float)(p_param->float04);
    float05=(float)(p_param->float05);
    float06=(float)(p_param->float06);
    float07=(float)(p_param->float07);
    float08=(float)(p_param->float08);
    float09=(float)(p_param->float09);
    float10=(float)(p_param->float10);
    float11=(float)(p_param->float11);
    float12=(float)(p_param->float12);
    
}


void param_save(struct PARAM *p_param)    //把结构体中的数据存到flash里面去
{
    flash_erase_sector(255); //擦除第255页数据
    flash_erase_sector(253);

    flash_page_program( 255,0,(const uint8*)&(p_param->int01),4);
    flash_page_program( 255,1,(const uint8*)&(p_param->int02),4);
    flash_page_program( 255,2,(const uint8*)&(p_param->int03),4);
    flash_page_program( 255,3,(const uint8*)&(p_param->int04),4);
    flash_page_program( 255,4,(const uint8*)&(p_param->int05),4);
    flash_page_program( 255,5,(const uint8*)&(p_param->int06),4);
    flash_page_program( 255,6,(const uint8*)&(p_param->int07),4);
    flash_page_program( 255,7,(const uint8*)&(p_param->int08),4);
    flash_page_program( 255,8,(const uint8*)&(p_param->int09),4);
    flash_page_program( 255,9,(const uint8*)&(p_param->int10),4);
    flash_page_program( 255,10,(const uint8*)&(p_param->int11),4);
    flash_page_program( 255,11,(const uint8*)&(p_param->int12),4);

    flash_page_program( 255,12,(const uint8*)&(p_param->float01),4);
    flash_page_program( 255,13,(const uint8*)&(p_param->float02),4);
    flash_page_program( 255,14,(const uint8*)&(p_param->float03),4);
    flash_page_program( 255,15,(const uint8*)&(p_param->float04),4);
    flash_page_program( 255,16,(const uint8*)&(p_param->float05),4);
    flash_page_program( 255,17,(const uint8*)&(p_param->float06),4);
    flash_page_program( 255,18,(const uint8*)&(p_param->float07),4);
    flash_page_program( 255,19,(const uint8*)&(p_param->float08),4);
    flash_page_program( 255,20,(const uint8*)&(p_param->float09),4);
    flash_page_program( 255,21,(const uint8*)&(p_param->float10),4);
    flash_page_program( 255,22,(const uint8*)&(p_param->float11),4);
    flash_page_program( 255,23,(const uint8*)&(p_param->float12),4);
    
    flash_page_program( 253,0,(const uint8*)&(p_param->param_flag),4);
    // TODO: 源代码的offset和逐飞库里面的page是一个东西吗？此处假定page=offset/4
    // RE: 好像是
}