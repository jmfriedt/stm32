//#include <stdio.h>
//#include <stdlib.h>

#include "uart.h"

int fact(int n)
{volatile int __attribute__((unused)) tmp=n;
 if (n>1)
    return(fact(n-1)*n);
 else return(1);
}

int main() // int argc, char** argv)
{volatile static int __attribute__((unused)) variable1=0x42;
 volatile static int __attribute__((unused)) variable2=0x55;
 volatile int __attribute__((unused)) val=5;
 int k;
 clock_setup();
 init_gpio();
// if (argc>1) val=atoi(argv[1]);
// printf("resultat %d\n",fact(val));
 val=fact(val);
 while(1)
 {led_set(1);led_clr(0);
  for (k=0;k<5;k++) delay(0xffff);
  led_set(0);led_clr(1);
  for (k=0;k<5;k++) delay(0xffff);
 }
 return(0);
}
