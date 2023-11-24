#include "racine.h"
#include "fixed.h"

long jmf_sqrt(long A)
{long long x,xp; // ,n=0;
 {if (A==0) return(0);
  if (A==1) return(1); // pourquoi Newton ne marche pas en 1 ?
  xp=A>>1;             // initialisation : A/2
  do {
    x=xp;
    if (x!=0) xp=(x+A/x)>>1;   // x(n+1)=1/2*(x(n)+A/x(n))
    else break;
//   n++;
  } while ((x-xp)!=0);
 }
// printf("n=%d:\t",n);
 return(xp);
}

long jmf_sqrtfixed(long A)
{long long x,xp; // ,n=0;
 {if (A==0) return(0);
  if (A==1) return(1); // pourquoi Newton ne marche pas en 1 ?
  xp=A>>1;             // initialisation : A/2
  do {
    x=xp;
    if (x!=0) xp=(x+(A*SCALE/x))>>1;   // x(n+1)=1/2*(x(n)+A/x(n))
    else break;
//   n++;
  } while ((x-xp)!=0);
 }
// printf("n=%d:\t",n);
 return(xp);
}

long jmf_sqrt3fixed(long A)
{long long x,xp; // ,n=0;
 {if (A==0) return(0);
  if (A==1) return(1); 
  xp=A>>1;             // initialisation : A/2
  do {
    x=xp;
    if (x!=0) xp=divfix(mulfix(2*SCALE,x),3*SCALE)+divfix((divfix(A,mulfix(x,x))),3*SCALE);   // x(n+1)=2/3*x(n)+1/3*A/x(n)^2
    else break;
//   n++;
  } while ((x-xp)!=0);
 }
// printf("n=%d:\t",n);
 return(xp);
}
