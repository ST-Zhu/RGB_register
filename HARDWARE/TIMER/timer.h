#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板V3
//定时器 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/1/10
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//********************************************************************************
//V1.1 20150110
//1,增加TIM3_PWM_Init函数。
//2,增加LED0_PWM_VAL宏定义，控制TIM3_CH2脉宽									  
//////////////////////////////////////////////////////////////////////////////////  

//通过改变TIM3->CCR2的值来改变占空比，从而控制LED0的亮度
#define LED_R_PWM_VAL TIM4->CCR1  
#define LED_G_PWM_VAL TIM4->CCR2
#define LED_B_PWM_VAL TIM4->CCR3

void TIM4_PWM_Init(u16 arr,u16 psc);
#endif























