#include "rules.h"
int time_h_del,time_m_del,time_h_add,time_m_add;
struct tm *tmm;
time_t timer;
//----------------------------------------------------------------------------
int check_time(void)
{
static float time_add,time_del,time_cur;
time_add=time_h_add+0.01*time_m_add;
time_del=time_h_del+0.01*time_m_del;
time_cur=tmm->tm_hour+0.01*tmm->tm_min;
if (time_del>time_add && (time_cur<time_add || time_cur>=time_del)) return false;
if (time_del<time_add && (time_cur<time_add && time_cur>=time_del)) return false;
return true;
}
//----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
isc_db_handle    DB = 0L;             /* database handle */
isc_tr_handle    trans = NULL;          /* transaction handle */
long             status[20];            /* status vector */
XSQLDA  ISC_FAR *       sqlda;
isc_stmt_handle         stmt = NULL;                /* statement handle */

char ISC_FAR *  dpb = NULL;    /* DB parameter buffer */
short dpb_length = 0;

static char buf[512],l,email[255];
char *d;
static int ip,limit,start_rule,have_internet,have_icq,have_mail,time_limit;
short  flag0=0,flag1=0,flag2=0,flag3=0,flag4=0,flag5=0,flag6=0,flag7=0,flag8=0,flag9=0,flag10=0,flag11=0;
long fetch_stat;
static long long int traf;

if (argc<7)
 {
 printf("ipfw Rules Checker ver. 2.0.7 Copyright (C) Nicol Morozov 2002-2003\nUsage logf <dbname> <username> <password> <start rule number> <prefix> <server address>\n");
 return 1;
 }

start_rule=atoi(argv[4]);

/* Creating DPB */

dpb = (char *) malloc(1);
*dpb = '\1';

/* Add user name and password to DPB. */
isc_expand_dpb(&dpb, (short ISC_FAR *)&dpb_length,
isc_dpb_user_name, uname,
isc_dpb_password, upass,
NULL);

if (isc_attach_database(status, strlen(Db_name), Db_name, &DB, dpb_length, dpb)) ERREXIT(status,1)

// Start transaction
if (isc_start_transaction(status, &trans, 1, &DB, 0, NULL))  ERREXIT(status, 1)

/* Allocate an output SQLDA. */
sqlda = (XSQLDA ISC_FAR *) calloc(XSQLDA_LENGTH(15),1);
sqlda->sqln = 15;
//sqlda->sqld = 2;
sqlda->version = 1;

/* Allocate a statement. */
timer=time(NULL);
tmm=localtime(&timer);
sprintf(buf,"SELECT IP,SUM_TRAF,LIMIT,EMAIL,HAVE_INTERNET,HAVE_ICQ,HAVE_MAIL,TIME_LIMIT,TIME_H_DEL,TIME_M_DEL,TIME_H_ADD,TIME_M_ADD FROM TRAF_VIEW1 WHERE DATE_YEAR=%lu AND DATE_MONTH=%lu",tmm->tm_year+1900,tmm->tm_mon+1);
if (isc_dsql_allocate_statement(status, &DB, &stmt))
 {
 ERREXIT(status, 1)
 }

/* Prepare the statement. */
if (isc_dsql_prepare(status, &trans, &stmt, 0, buf, 3, sqlda))
 {
 ERREXIT(status, 1)
 }

sqlda->sqlvar[0].sqldata = (char *)&ip;
sqlda->sqlvar[0].sqltype = SQL_LONG;
sqlda->sqlvar[0].sqlind  = &flag0;

sqlda->sqlvar[1].sqldata = (char *)&traf;
sqlda->sqlvar[1].sqltype = SQL_INT64;
sqlda->sqlvar[1].sqlind  = &flag1;

sqlda->sqlvar[2].sqldata = (char *)&limit;
sqlda->sqlvar[2].sqltype = SQL_LONG;
sqlda->sqlvar[2].sqlind  = &flag2;

sqlda->sqlvar[3].sqldata = (char *)email;
sqlda->sqlvar[3].sqltype = SQL_TEXT;
sqlda->sqlvar[3].sqlind  = &flag3;

sqlda->sqlvar[4].sqldata = (char *)&have_internet;
sqlda->sqlvar[4].sqltype = SQL_LONG;
sqlda->sqlvar[4].sqlind  = &flag4;

sqlda->sqlvar[5].sqldata = (char *)&have_icq;
sqlda->sqlvar[5].sqltype = SQL_LONG;
sqlda->sqlvar[5].sqlind  = &flag5;

sqlda->sqlvar[6].sqldata = (char *)&have_mail;
sqlda->sqlvar[6].sqltype = SQL_LONG;
sqlda->sqlvar[6].sqlind  = &flag6;

sqlda->sqlvar[7].sqldata = (char *)&time_limit;
sqlda->sqlvar[7].sqltype = SQL_LONG;
sqlda->sqlvar[7].sqlind  = &flag7;

sqlda->sqlvar[8].sqldata = (char *)&time_h_del;
sqlda->sqlvar[8].sqltype = SQL_LONG;
sqlda->sqlvar[8].sqlind  = &flag8;

sqlda->sqlvar[9].sqldata = (char *)&time_m_del;
sqlda->sqlvar[9].sqltype = SQL_LONG;
sqlda->sqlvar[9].sqlind  = &flag9;

sqlda->sqlvar[10].sqldata = (char *)&time_h_add;
sqlda->sqlvar[10].sqltype = SQL_LONG;
sqlda->sqlvar[10].sqlind  = &flag10;

sqlda->sqlvar[11].sqldata = (char *)&time_m_add;
sqlda->sqlvar[11].sqltype = SQL_LONG;
sqlda->sqlvar[11].sqlind  = &flag11;

/*  Execute */
if (isc_dsql_execute(status, &trans, &stmt, 3, NULL))
 {
 ERREXIT(status, 1)
 }

/* fetch */
while ((fetch_stat = isc_dsql_fetch(status, &stmt, 1, sqlda)) == 0)
//isc_dsql_fetch(status, &stmt, 1, sqlda);
 {
// printf("ip=%lu traf='%lu,%lu' limit=%lu email='%s'\n",ip,traf,limit,buf);
 sprintf(buf,"/sbin/ipfw -q delete %lu",start_rule+(ip-1)*5);
 system(buf);
 sprintf(buf,"/sbin/ipfw -q delete %lu",start_rule+(ip-1)*5+1);
 system(buf);
 sprintf(buf,"/sbin/ipfw -q delete %lu",start_rule+(ip-1)*5+2);
 system(buf);
 sprintf(buf,"/sbin/ipfw -q delete %lu",start_rule+(ip-1)*5+3);
 system(buf);  
 sprintf(buf,"/sbin/ipfw -q delete %lu",start_rule+(ip-1)*5+4);
 system(buf);  
 if (have_icq)
  {
  sprintf(buf,"/sbin/ipfw -q add %u pass tcp from %s.%u to any 5190",start_rule+(ip-1)*5,argv[5],ip);
  system(buf);
  }
 else
  {
  sprintf(buf,"/sbin/ipfw -q add %u deny tcp from %s.%u to any 5190",start_rule+(ip-1)*5,argv[5],ip);
  system(buf);
  } 
 if (have_mail)
  {
  sprintf(buf,"/sbin/ipfw -q add %u pass tcp from %s.%u to %s 25",start_rule+(ip-1)*5+1,argv[5],ip,argv[6]);
  system(buf);
  }
 else 
  {
  sprintf(buf,"/sbin/ipfw -q add %u deny tcp from %s.%u to %s 25",start_rule+(ip-1)*5+1,argv[5],ip,argv[6]);
  system(buf);
  }

 if (have_internet && (limit>traf || !limit) && (!time_limit || check_time()))
  {
  sprintf(buf,"/sbin/ipfw -q add %u fwd %s,3128 tcp from %s.%u to any 80",start_rule+(ip-1)*5+2,argv[6],argv[5],ip);
  system(buf);
  sprintf(buf,"/sbin/ipfw -q add %u pass ip from %s.%u to any",start_rule+(ip-1)*5+3,argv[5],ip);
  system(buf);
  sprintf(buf,"/sbin/ipfw -q add %u pass ip from any to %s.%u",start_rule+(ip-1)*5+4,argv[5],ip);
  system(buf);
  }
// if (!limit || traf<limit) continue;
// buf[sqlda->sqlvar[3].sqllen]=0;
// while(buf[strlen(buf)-1]==0x13 || buf[strlen(buf)-1]==0x10 || buf[strlen(buf)-1]==' ') buf[strlen(buf)-1]=0;
// printf("Flags: %lu %lu %lu %lu\n",flag0,flag1,flag2,flag3); 
 }

/* Free statement handle. */
if (isc_dsql_free_statement(status, &stmt, DSQL_close))
 {
 ERREXIT(status, 1)
 }

// Commint transaction
if (isc_commit_transaction(status, &trans)) ERREXIT(status, 1)

// Disconnect
if (isc_detach_database(status, &DB)) ERREXIT(status, 1)

free(sqlda);

return 0;
}
