#include "mnlib3.h"
#include <stdio.h>

#ifdef HAVE_STRING_H
#include <string.h>
#endif

/* Transfer 4 digit year number to 2 digit number */
int _cdecl year42(unsigned int y)
{
static char buf[6];
sprintf(buf,"%u",y);
return atoi(buf+2);
}
/* Get Word Name Of Month from number */
void _cdecl GetMonth(unsigned int m,char *buf)
{
switch(m)
 {
 case 1:strcpy(buf,"Jan");break;
 case 2:strcpy(buf,"Feb");break;
 case 3:strcpy(buf,"Mar");break;
 case 4:strcpy(buf,"Apr");break;
 case 5:strcpy(buf,"May");break;
 case 6:strcpy(buf,"Jun");break;
 case 7:strcpy(buf,"Jul");break;
 case 8:strcpy(buf,"Aug");break;
 case 9:strcpy(buf,"Sep");break;
 case 10:strcpy(buf,"Oct");break;
 case 11:strcpy(buf,"Nov");break;
 case 12:strcpy(buf,"Dec");break;
 default: *buf=0;
}
}
/* Get Name Day Of Week from number */
void _cdecl GetDayOfWeek(unsigned int m,char *buf)
{
switch(m)
 {
 case 0:strcpy(buf,"Sun");break;
 case 1:strcpy(buf,"Mon");break;
 case 2:strcpy(buf,"Tue");break;
 case 3:strcpy(buf,"Wed");break;
 case 4:strcpy(buf,"Thu");break;
 case 5:strcpy(buf,"Fri");break;
 case 6:strcpy(buf,"Sat");break;
 default: *buf=0;
 }
}
