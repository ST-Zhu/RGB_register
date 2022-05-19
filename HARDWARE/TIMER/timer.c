#include "timer.h"
#include "led.h"
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

//TIM4 PWMCH1~3初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM4_PWM_Init(u16 arr,u16 psc)
{		 					 
	//此部分需手动修改IO口设置
	RCC->APB1ENR|=1<<2; 	//TIM4时钟使能
    
	RCC->APB2ENR|=1<<3;    	//使能PORT B时钟
	GPIOB->CRL&=0XF0FFFFFF;	//PB6输出
	GPIOB->CRL|=0X0B000000;	//复用功能输出 	  				//改IO口P 	
	GPIOB->CRL&=0X0FFFFFFF;	//PB7输出
	GPIOB->CRL|=0XB0000000;	//复用功能输出 	  				//改IO口P 
	GPIOB->CRH&=0XFFFFFFF0;	//PB8输出
	GPIOB->CRH|=0X0000000B;	//复用功能输出 	  				//改IO口P 

	RCC->APB2ENR|=1<<0;     //开启辅助时钟	   
	AFIO->MAPR&=0XFFFFEFFF; //清除MAPR的12
	AFIO->MAPR|=0<<12;      //无重映像						//重映像
	
	TIM4->ARR=arr;			//设定计数器自动重装值 
	TIM4->PSC=psc;			//预分频器//不分频
	
	TIM4->CCMR1|=6<<4;  	//CH1 PWM2模式//111(7)大于时输出高电平//110(6)小于时输出高电平		 
	TIM4->CCMR1|=1<<3; 		//CH1预装载使能	   
	TIM4->CCER|=1<<0;   	//OC1 输出使能					//改CH
	TIM4->CCMR1|=6<<12;  	//CH2 PWM2模式//111(7)大于时输出高电平//110(6)小于时输出高电平		 
	TIM4->CCMR1|=1<<11; 	//CH2预装载使能	   
	TIM4->CCER|=1<<4;   	//OC2 输出使能					//改CH
	TIM4->CCMR2|=6<<4;  	//CH3 PWM2模式//111(7)大于时输出高电平//110(6)小于时输出高电平		 
	TIM4->CCMR2|=1<<3; 		//CH3预装载使能	   
	TIM4->CCER|=1<<8;   	//OC3 输出使能					//改CH
	
	TIM4->CR1=0x0080;   	//ARPE使能 
	TIM4->CR1|=0x01;    	//使能定时器3 											  
}  	 
