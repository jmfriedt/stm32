#include "fixed.h"

long addfix(long in1,long in2) {return(in1+in2);}

long mulfix(long in1,long in2)
{long long tmp;
 tmp=(long long)in1*(long long)in2;
 tmp/=SCALE;
 return((int)tmp);
}

long divfix(long in1,long in2)
{long long tmp=(long long)in1*SCALE;
 if (in2!=0)
    tmp/=(long long)in2;
 else tmp=0;
 return((long)tmp);
}
