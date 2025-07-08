#define SQUID_LOG_FILE "/usr/local/squid/var/logs/access.log"
#define N_YEAR 2004
#define N_MONTH 9
#define N_IP 13
#include <stdio.h>
#include <mnlib.h>
#include <time.h>

typedef struct _LogRec 
 {
 int ip1,ip2,ip3,ip4,size,hit;
 char site[1024];
 struct _LogRec *next;
 } LogRec;

LogRec *FR=NULL;

LogRec *FindRecord(int ip1,int ip2,int ip3,int ip4,char *site)
{
LogRec *PR=FR;
while(PR!=NULL)
 {
 if (PR->ip1==ip1 && PR->ip2==ip2 && PR->ip3==ip3 && PR->ip4==ip4 && !strcmp(PR->site,site))
  return PR;
 PR=PR->next;
 }
return NULL; 
}
main()
{
static char logline[4096],workbuf[4096];
int linepos;
FILE *log;
struct tm *rec_time;
time_t timer;
int ip1,ip2,ip3,ip4,size;
LogRec *NR,*PR;

log=fopen(SQUID_LOG_FILE,"r");
PR=FR;NR=FR;
while(fgets(logline,sizeof(logline)-1,log)!=NULL)
 { 
 linepos=substr(logline,workbuf,0,'.'); //Time
 timer=(time_t)atoi(workbuf);
 rec_time = localtime(&timer); 
 if ((rec_time->tm_year+1900)!=N_YEAR || (rec_time->tm_mon+1)!=N_MONTH) continue;
 linepos=substr(logline,workbuf,linepos,' '); // ???
 linepos=substr(logline,workbuf,linepos,' '); // Elapsed
 linepos=substr(logline,workbuf,linepos,'.'); // IP
 ip1=atoi(workbuf);
 linepos=substr(logline,workbuf,linepos,'.');
 ip2=atoi(workbuf);
 linepos=substr(logline,workbuf,linepos,'.');
 ip3=atoi(workbuf);
 linepos=substr(logline,workbuf,linepos,' ');
 ip4=atoi(workbuf);
 if (ip4!=N_IP) continue;
 linepos=substr(logline,workbuf,linepos,'/'); // Action
 if (!strcmp(workbuf,"TCP_DENIED")) continue;
 linepos=substr(logline,workbuf,linepos,' '); // Code
 linepos=substr(logline,workbuf,linepos,' '); // Size
 size=atoi(workbuf);
 linepos=substr(logline,workbuf,linepos,' '); // Metod
// printf(workbuf);printf("\n"); 
// GET, HEAD, POST, PUT, DELETE, CONNECT, OPTIONS, PATCH, PROPFIND, PROPPATCH, MKCOL, COPY, MOVE, LOCK, UNLOCK, TRACE
 if (strcmp(workbuf,"CONNECT")) 
  {
  linepos=substr(logline,workbuf,linepos,':'); // http:
  linepos=substr(logline,workbuf,linepos,'/'); // site
  }
 else
  {
  linepos=substr(logline,workbuf,linepos,' '); // site
  } 
 NR=FindRecord(ip1,ip2,ip3,ip4,workbuf);
 if (NR==NULL)
  {
  PR=FR; 
  if (PR!=NULL) while(PR->next!=NULL) PR=PR->next;
  NR=(LogRec *)calloc(sizeof(LogRec),1);
  if (PR==NULL)
   FR=NR;
  else
   PR->next=NR;
  NR->size=0;
  NR->hit=0;  
  NR->next=NULL;
  strcpy(NR->site,workbuf);
  NR->ip1=ip1;
  NR->ip2=ip2;
  NR->ip3=ip3;
  NR->ip4=ip4;
  }
 NR->hit++;  
 NR->size+=size;
// break; // Temporary 
 }
fclose(log); 
PR=FR;
while(PR!=NULL)
 {
 printf("IP=%lu.%lu.%lu.%lu Site='%s' Size=%lu Hit=%lu\n",PR->ip1,PR->ip2,PR->ip3,PR->ip4,PR->site,PR->size,PR->hit);
 PR=PR->next;
 }
}
