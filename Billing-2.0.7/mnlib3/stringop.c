#include <string.h>
#include "mnlib3.h"
//---------------------------------------------------------------------------
int _cdecl  substr(const char *st,char *s,unsigned int index,char sp)
/*
 st - string
 s - substring
*/
{
unsigned int i;
if (!st[0]) 
 {
 *s=0;
 return index;
 }
if (index>(strlen(st)-1)) {*s=0;return index;}
while (st[index]==sp) index++;
for(i=index;i<strlen(st);i++)
 if (st[i]==sp) break; 
 else s[i-index]=st[i];
s[i-index]=0;
while(i<strlen(st) && st[i]==sp) i++;
return i;
}
//---------------------------------------------------------------------------
int CheckSp(const char sp,const char *st)
{
char *c=(char *)st;
while (*c)
 if (sp==*c) return true;
 else c++;
return false;
}
//---------------------------------------------------------------------------
int _cdecl substr_ex(const char *st,char *s,unsigned int index,const char *sp)
{
unsigned int i;
if (!st[0]) {*s=0;return index;}
if (index>(strlen(st)-1)) {*s=0;return index;}
while (CheckSp(st[index],sp)) index++;
for(i=index;i<strlen(st);i++)
 if (CheckSp(st[i],sp)) break; 
 else s[i-index]=st[i];
s[i-index]=0;
while(i<strlen(st) && CheckSp(st[i],sp)) i++;
return i;
}
//---------------------------------------------------------------------------
int _cdecl substr_ex_par(const char *st,char *s,unsigned int index,const char *sp)
{
unsigned int i,no_par=true;
if (!st[0]) {*s=0;return index;}
if (index>(strlen(st)-1)) {*s=0;return index;}
//while (CheckSp(st[index],sp)) index++;
for(i=index;i<strlen(st);i++)
 {
 if (st[i]=='\"') no_par=!no_par;
 if (no_par && CheckSp(st[i],sp)) break; 
 s[i-index]=st[i];
 }
s[i-index]=0;
i++;
//while(i<strlen(st) && CheckSp(st[i],sp)) i++;
return i;
}
//---------------------------------------------------------------------------
