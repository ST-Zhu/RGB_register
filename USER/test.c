#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 
#include "timer.h" 
#include "LQ12864.h"
#include "adc.h"
//ALIENTEKս��STM32������ʵ��9
//PWM��� ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
u8 t;
u8 len;
u8 SBUFF[20];

void INIT()
{
	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,115200);	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
  	TIM4_PWM_Init(255,0);	//����Ƶ��PWMƵ��=72000/(899+1)=80Khz
	Adc_Init();		  		//ADC��ʼ��	
	OLED_Init(); 			//OLED��ʼ��
	delay_ms(10);
}

void CHANGE(u8 X,u8 Y,u8 a)
{
	switch(a)
	{
		case '0':OLED_P8x16Str(X,Y,"0");break;
		case '1':OLED_P8x16Str(X,Y,"1");break;
		case '2':OLED_P8x16Str(X,Y,"2");break;
		case '3':OLED_P8x16Str(X,Y,"3");break;
		case '4':OLED_P8x16Str(X,Y,"4");break;
		case '5':OLED_P8x16Str(X,Y,"5");break;
		case '6':OLED_P8x16Str(X,Y,"6");break;
		case '7':OLED_P8x16Str(X,Y,"7");break;
		case '8':OLED_P8x16Str(X,Y,"8");break;
		case '9':OLED_P8x16Str(X,Y,"9");break;
	}
}

void SHOW(u8 R1,u8 R2,u8 R3,u8 G1,u8 G2,u8 G3,u8 B1,u8 B2,u8 B3)
{
	OLED_CLS();//����
	OLED_P8x16Str(0,0,"R:");//��һ�� -- 8x16����ʾ��Ԫ��ʾASCII��
	CHANGE(24,0,R1);
	CHANGE(32,0,R2);
	CHANGE(40,0,R3);
	OLED_P8x16Str(0,2,"G:");
	CHANGE(24,2,G1);
	CHANGE(32,2,G2);
	CHANGE(40,2,G3);
	OLED_P8x16Str(0,4,"B:");
	CHANGE(24,4,B1);
	CHANGE(32,4,B2);
	CHANGE(40,4,B3);
}

void STAR1()//��ʼģʽһ�����ڽ�������
{
	if(USART_RX_STA&0x8000)//���ͽ���
	{	
		len=USART_RX_STA&0x3FFF;//�õ��˴ν��յ������ݳ���
		printf("\r\n�����͵���ϢΪ:\r\n");
		for(t=0;t<len;t++)
		{
			SBUFF[t]=USART_RX_BUF[t];
			USART1->DR=USART_RX_BUF[t];
			while((USART1->SR&0X40)==0);//�ȴ����ͽ���
		}
		USART_RX_STA=0;
		if(SBUFF[12]=='!')
		{
			LED_R_PWM_VAL=(SBUFF[1]-0x30)*100+(SBUFF[2]-0x30)*10+(SBUFF[3]-0x30);
			LED_G_PWM_VAL=(SBUFF[5]-0x30)*100+(SBUFF[6]-0x30)*10+(SBUFF[7]-0x30);
			LED_B_PWM_VAL=(SBUFF[9]-0x30)*100+(SBUFF[10]-0x30)*10+(SBUFF[11]-0x30);
			SHOW(SBUFF[1],SBUFF[2],SBUFF[3],SBUFF[5],SBUFF[6],SBUFF[7],SBUFF[9],SBUFF[10],SBUFF[11]);
		}
	}
}

void STAR2()
{
	if(USART_RX_STA&0x8000)//���ͽ���
	{	
		len=USART_RX_STA&0x3FFF;//�õ��˴ν��յ������ݳ���
		printf("\r\n�����͵���ϢΪ:\r\n");
		for(t=0;t<len;t++)
		{
			SBUFF[t]=USART_RX_BUF[t];
			USART1->DR=USART_RX_BUF[t];
			while((USART1->SR&0X40)==0);//�ȴ����ͽ���
		}
		USART_RX_STA=0;
		if((SBUFF[0]=='a')&&(SBUFF[1]=='d')&&(SBUFF[2]=='c'))
		{
			LED_R_PWM_VAL=Get_Adc_Average(ADC_CH0,10);
			LED_G_PWM_VAL=Get_Adc_Average(ADC_CH1,10);
			LED_B_PWM_VAL=Get_Adc_Average(ADC_CH2,10);
			SHOW(Get_Adc_Average(ADC_CH0,10)/100+0x30,Get_Adc_Average(ADC_CH0,10)/10%10+0x30,Get_Adc_Average(ADC_CH0,10)%10+0x30,Get_Adc_Average(ADC_CH1,10)/100+0x30,Get_Adc_Average(ADC_CH1,10)/10%10+0x30,Get_Adc_Average(ADC_CH1,10)%10+0x30,Get_Adc_Average(ADC_CH2,10)/100+0x30,Get_Adc_Average(ADC_CH2,10)/10%10+0x30,Get_Adc_Average(ADC_CH2,10)%10+0x30);
		}
	}
}

void END()
{
	OLED_CLS();//����
	OLED_P8x16Str(0,0,"END!");
}

int main(void)
{		
	INIT();
   	while(1)
	{ 
		if(USART_RX_STA&0x8000)//���ͽ���
		{	
			len=USART_RX_STA&0x3FFF;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n");
			for(t=0;t<len;t++)
			{
				SBUFF[t]=USART_RX_BUF[t];
				USART1->DR=USART_RX_BUF[t];
				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
			}
			USART_RX_STA=0;
			if((SBUFF[0]=='s')&&(SBUFF[1]=='t')&&(SBUFF[2]=='a')&&(SBUFF[3]=='r')&&(SBUFF[4]=='1'))
			{
				LED_R_PWM_VAL=0;
				LED_G_PWM_VAL=100;
				LED_B_PWM_VAL=0;
				OLED_CLS();//����
				OLED_P8x16Str(0,0,"STAR1!");
				delay_ms(1000);
				LED_G_PWM_VAL=0;
				while(!((SBUFF[0]=='e')&&(SBUFF[1]=='n')&&(SBUFF[2]=='d')))
					STAR1();
			}
			if((SBUFF[0]=='s')&&(SBUFF[1]=='t')&&(SBUFF[2]=='a')&&(SBUFF[3]=='r')&&(SBUFF[4]=='2'))
			{
				LED_R_PWM_VAL=0;
				LED_G_PWM_VAL=0;
				LED_B_PWM_VAL=100;
				OLED_CLS();//����
				OLED_P8x16Str(0,0,"STAR2!");
				delay_ms(1000);
				LED_B_PWM_VAL=0;
				while(!((SBUFF[0]=='e')&&(SBUFF[1]=='n')&&(SBUFF[2]=='d')))
					STAR2();
			}
			if((SBUFF[0]=='e')&&(SBUFF[1]=='n')&&(SBUFF[2]=='d'))
			{
				LED_R_PWM_VAL=100;
				LED_G_PWM_VAL=0;
				LED_B_PWM_VAL=0;
				END();
				delay_ms(1000);
				LED_R_PWM_VAL=0;
			}	
		}
	}
}
