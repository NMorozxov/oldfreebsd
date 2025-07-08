#ifndef _MNLIB_H
#define _MNLIB_H

#if HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#ifndef _cdecl
#define _cdecl
#endif

#ifndef HAVE_STRICMP
#ifdef HAVE_STRCASECMP
#define stricmp strcasecmp
#endif
#endif

/* Token Table */
typedef struct _TokenTable 
               {
               const char *item;
               int  token;
               } TokenTable;


/* Functions Prototypes */
#ifdef __cplusplus
extern "C" {
#endif
int  _cdecl IsInteger(const char *c);
int  _cdecl IsFloat(const char *c);
int  _cdecl is_digit(const char c);
int  _cdecl substr(const char *st,char *s,unsigned int index,char sp);
int  _cdecl substr_ex(const char *st,char *s,unsigned int index,const char *sp);
int  _cdecl substr_ex_par(const char *st,char *s,unsigned int index,const char *sp);
int  _cdecl GetToken(TokenTable tab[],char *tok,const int DefaultToken,const int CaseSen);
int  _cdecl year42(unsigned int y);
void _cdecl GetMonth(unsigned int m,char *buf);
void _cdecl GetDayOfWeek(unsigned int m,char *buf);
double _cdecl pow10i (int x);
double _cdecl round_ex(double round_val,int digits);
#ifdef __cplusplus
};
#endif
#endif
