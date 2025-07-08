#include <stdio.h>
#include <string.h>
#include "mnlib3.h"
int _cdecl GetToken(TokenTable tab[],char *tok,const int DefaultToken,const int CaseSen)
{
int i;
for(i=0;tab[i].token!=0;i++)
 if (CaseSen) {if (!strcmp(tab[i].item,tok)) return tab[i].token;}
 else if (!stricmp(tab[i].item,tok)) return tab[i].token;
return DefaultToken;
}
