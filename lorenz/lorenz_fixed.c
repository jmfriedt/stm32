// 25"
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
{long x=(long)(0.1*SCALE),y=0,z=0,sigma,R,B,dx,dy,dz;
 long dt=(long)(.001*SCALE),t,cp;
 clock_setup();
 init_gpio();
 usart_setup();
 sigma=(10*SCALE);
 B=(long)((8./3.)*SCALE);
 R=(long)(470./19.*SCALE);
// printf("%d %d %d\n",x,dt,B);
for (cp=0;cp<20;cp++)
{x=(long)(0.1*SCALE),y=0,z=0;
 for (t=0;t<(50*SCALE);t+=dt)
   {dx=mulfix(sigma,mulfix(addfix(y,-x),dt));
    dy=mulfix(addfix(mulfix(x,addfix(R,-z)),-y),dt);
    dz=mulfix(addfix(mulfix(x,y),-mulfix(B,z)),dt);
    x=addfix(x,dx);
    y=addfix(y,dy);
    z=addfix(z,dz);
   }
}
   affiche(x);my_putchar(' ');
   affiche(y);my_putchar(' ');
   affiche(z);my_putchar('\r');my_putchar('\n');
}



