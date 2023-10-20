#include "uart.h"

void fonction(short s)
{int k;
 char c;
 for (k=0;k<4;k++)
   {c=(s>>(3-k)*4)&0x0f;
    if (c<10) c+='0'; else c+='A'-10;
    my_putchar(c);
   }
}

