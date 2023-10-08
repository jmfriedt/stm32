// gcc -o lorenz_fixed lorenz_fixed.c fixed.c
#define usart1
#include "uart.h"
#include "fixed.h"

void affiche(long p)
{long n=1000000;
 while (n>1)
   {my_putchar(p/n+'0');
    p=p-(p/n)*n;
    n=n/10;
   }
}

int main()
{double x=0.1,y=0.,z=0.,sigma,R,B,dx,dy,dz;
 double dt=.001,t;
 int cp;
 clock_setup();
 init_gpio();
 usart_setup();
 sigma=10.;
 B=8./3.;
 R=470./19.;
for (cp=0;cp<20;cp++)
{x=0.1,y=0.,z=0.;
 for (t=0;t<50.;t+=dt)
   {dx=sigma*(y-x)*dt;
    dy=(x*(R-z)-y)*dt;
    dz=(x*y-B*z)*dt;
    x=x+dx;
    y=y+dy;
    z=z+dz;
   }
}
   affiche((int)(x*10000.));my_putchar(' ');
   affiche((int)(y*10000.));my_putchar(' ');
   affiche((int)(z*10000.));my_putchar('\r');my_putchar('\n');
}



