// STM32F4Disco: DO NOT use USART1 which is also used by USB OTG
// http://www.micromouseonline.com/2013/05/05/using-usart1-on-the-stm32f4discovery/

#define usart1
#include "uart.h"

int main()
{int msk;
 msk=(1<<11)|(1<<12)|(1<<13);
 clock_setup();
 init_gpio();
 usart_setup();
 while(1)
  {led_set(msk);
   my_putchar(sizeof(int)+'0');
   my_putchar('\r');
   my_putchar('\n');
   delay(0xffff);
  }
 return 0;
}
