/*********************************************************************************************************************
 * 
 * @file       		flash_param.h
 *  				flash������ȡ
 * @core			S9KEA128
 * @date       		2018
 ********************************************************************************************************************/
#ifndef _flash_param_
#define _flash_param_


#include "bsp_global_var.h"

#define PARAM_INIT_FLAG     (159)   //���ر�־λ

extern void param_in(void);   //��flash�ж��������õ�������
extern void param_load(struct PARAM * p_param);
extern void set_param(struct PARAM *p_param);   //�ṹ�������
extern void param_save(struct PARAM * p_param); //�ṹ�屣�������flash

#endif  /*_flash_param_*/