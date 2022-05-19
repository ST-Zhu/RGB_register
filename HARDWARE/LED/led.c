#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板V3
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/1/9
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
	RCC->APB2ENR|=1<<3;    //使能PORTB时钟	   	 	
	   	 
	GPIOB->CRL&=0XF0FFFFFF; 
	GPIOB->CRL|=0X03000000;//PB.6 推挽输出   	 
    GPIOB->ODR|=0<<6;      //PB.6 输出低
	GPIOB->CRL&=0X0FFFFFFF; 
	GPIOB->CRL|=0X30000000;//PB.7 推挽输出   	 
    GPIOB->ODR|=0<<7;      //PB.7 输出低
	GPIOB->CRH&=0XFFFFFFF0; 
	GPIOB->CRH|=0X00000003;//PB.8 推挽输出   	 
    GPIOB->ODR|=0<<8;      //PB.8 输出低
}






