#include "mnlib3.h"
//---------------------------------------------------------------------------
int _cdecl IsInteger(const char *c)
{
char *d=(char *)c;
if (!*d) return false;
if (*d=='+' || *d=='-') d++;
while (*d) 
 {
 if (!is_digit(*d)) return false;
 d++;
 }
return true;
}
//---------------------------------------------------------------------------
int _cdecl IsFloat(const char *c)
{
char *d=(char *)c,point=true;
if (!*d) return false;
if (*d=='+' || *d=='-') d++;
while (*d) 
 {
 if ((*d=='.' || *d==',') && point)
  {
  point=false;
  }
 else
  {
  if (!is_digit(*d)) return false;
  }
 d++;
 }
return true;
}
//---------------------------------------------------------------------------
int _cdecl is_digit(const char c)
{
if (c<'0') return 0;
if (c>'9') return 0;
return 1;
}

