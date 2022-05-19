// ------------------------------------------------------------
// IO��ģ��I2Cͨ��
// SCL��PB0
// SDA��PB1
// ------------------------------------------------------------

#ifndef __LQ12864_H
#define __LQ12864_H	 
#include "sys.h"

#define SCL PBout(0)	//����ʱ��
#define SDA PBout(1)	//��������

#define high 1
#define low 0

#define	Brightness	0xCF 
#define X_WIDTH 	128
#define Y_WIDTH 	64

void OLED_CLS(void);
void OLED_Init(void);
void OLED_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[]);
	 				    
#endif
