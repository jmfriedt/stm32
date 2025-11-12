#include <stdio.h>
#include "fixed.h"

signed long addfix(signed long in1,signed long in2) {return(in1+in2);}

signed long subfix(signed long in1,signed long in2) {return(in1-in2);}

signed long mulfix(signed long in1,signed long in2)
{signed long long tmp;
 tmp=(signed long long)in1*(signed long long)in2;
 tmp/=SCALE;
 return((int)tmp);
}

signed long divfix(signed long in1,signed long in2)
{signed long long tmp=(signed long long)in1*SCALE;
 if (in2!=0)
    tmp/=(signed long long)in2;
 else tmp=0;
 return((signed long)tmp);
}
