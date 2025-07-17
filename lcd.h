#include<lpc21xx.h>

#define LCD_D 0X0F<<20

#define RS 1<<17

#define RW 1<<18

#define E 1<<19

void LCD_INIT(void);

void LCD_COMMAND(unsigned char);

void LCD_DATA(unsigned char);

void LCD_STR(unsigned char*);

void LCD_NAME(unsigned char*);

void delay_ms(unsigned int);

void LCD_INIT(void)

{

   IODIR1|=LCD_D|RS|RW|E;

   LCD_COMMAND(0X01);

   LCD_COMMAND(0X02);

   LCD_COMMAND(0X0C);

   LCD_COMMAND(0X28);

   LCD_COMMAND(0X80);

}


void LCD_COMMAND(unsigned char c)

{

	IOCLR1=RS;

	IOCLR1=LCD_D;

	IOSET1=(c&0XF0)<<16;

	IOSET1=E;

	delay_ms(2);

	IOCLR1=E;


	IOCLR1=LCD_D;

	IOSET1=(c&0X0F)<<20;

	IOSET1=E;

	delay_ms(2);

	IOCLR1=E;

}


void LCD_DATA(unsigned char d)

{

	IOSET1=RS;

	IOCLR1=LCD_D;

	IOSET1=(d&0XF0)<<16;

	IOSET1=E;

	delay_ms(2);

	IOCLR1=E;


	IOCLR1=LCD_D;

	IOSET1=(d&0X0F)<<20;

	IOSET1=E;

	delay_ms(2);

	IOCLR1=E;

	

}


void LCD_STR(unsigned char *s)

{

	

   	while(*s)

   	LCD_DATA(*s++);

   

}


void LCD_NAME(unsigned char *n)

{

	unsigned char i;

	for(i=0;i<30;i++)

	{

	LCD_COMMAND(0XC0);

    LCD_STR("V24CE2A3");

	LCD_COMMAND(0X80);

	LCD_STR(n+i);

	delay_ms(200);

	LCD_COMMAND(0X01);

	}

}

void delay_ms(unsigned int ms)

{

	T0PR=15000-1;

	T0TCR=0X01;

	while(T0TC<ms);

	T0TCR=0X03;

	T0TCR=0X00;


}
