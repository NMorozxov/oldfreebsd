#include "mnlib3.h"
#include <math.h>
//---------------------------------------------------------------------------
double _cdecl pow10i (int x)
 {
 double res=1.0;
 int i;
 if (x>0) for (i=1;i<=x;i++) res*=10;
 if (x<0) for (i=1;i<=(-x);i++) res/=10;
 return res;
 }
//---------------------------------------------------------------------------
double _cdecl round_ex(double round_val,int digits) 
 {
 double i3;
 i3=((double)floor(round_val*pow10i(digits)))/((double)pow10i(digits));
 if  ((round_val*pow10i(digits)-floor(round_val*pow10i(digits)))>=0.5) i3+=pow10i(-digits);
 return i3;
 }
