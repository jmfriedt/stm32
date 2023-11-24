#include <stdio.h>
#include "racine.h"
#include "fixed.h"

int main()
{int i=2*SCALE;
 long x=2*SCALE,y=3*SCALE;
 long z=27*SCALE;
 long res;
 printf("integer sqrt:\t%d\n",jmf_sqrt(i));
 res=jmf_sqrtfixed(i);
 printf("square root fixed:\t%d.%04d\n",res/SCALE,res-(res/SCALE)*SCALE);
 res=jmf_sqrt3fixed(z);
 printf("cube root %d: %d.%04d\n",z,res/SCALE,res-(res/SCALE)*SCALE);
 res=jmf_sqrt3fixed(9*SCALE);
 printf("cube root %d: %d.%04d\n",9*SCALE,res/SCALE,res-(res/SCALE)*SCALE);
}
