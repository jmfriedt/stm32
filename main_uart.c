// NE PAS utiliser USART1 qui est aussi utilis'e pour USB OTG
// http://www.micromouseonline.com/2013/05/05/using-usart1-on-the-stm32f4discovery/

#include "uart.h"

int main()
{
	//char  buf[20]="Hello world\r\n\0";
	clock_setup();
	init_gpio();
	usart_setup();
	while(1)
	{
		led_set();
	  	mon_putchar('r');
	  	mon_putchar('\r');
	  	mon_putchar('\n');
	}
	return 0;
}
