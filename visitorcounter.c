#include<lpc21xx.h>

#include"lcd.h"

#define IRIN 0

#define IROUT 1

#define LED 1<<17

void INTEGER(unsigned int);

void START(void);

unsigned char current[5];

unsigned int in=0;

unsigned int out=0;

int main()

{

	START();

	while(1)

	{

		if((IOPIN0>>IRIN&1)==0)

		  {

		  ++in;

		  delay_ms(500);

		  LCD_COMMAND(0XC1);

		  INTEGER(in);

		  }

		 else if((IOPIN0>>IROUT&1)==0)

		 {

		if(in!=out)

		++out;

		delay_ms(500);

		LCD_COMMAND(0XC6);

		INTEGER(out);

		  }

		  LCD_COMMAND(0XCB);

		  INTEGER(in-out);

		if(in-out!=0)

		IOCLR0= LED;

		else

		IOSET0=LED;

	}			 


}


void INTEGER(unsigned int i)

{

	current[0]=(i/10)+48;

	current[1]=(i%10)+48;

	LCD_STR(current);


}





void START(void)

{

 	LCD_INIT();

	IODIR0|=LED;

	IOSET0=LED;

	LCD_NAME("BIDIRECTIONAL VISITOR COUNTER");

	LCD_COMMAND(0X81);

	LCD_STR("IN");

	LCD_COMMAND(0X85);

	LCD_STR("OUT");

	LCD_COMMAND(0X8A);

	LCD_STR("TOTAL");

}
