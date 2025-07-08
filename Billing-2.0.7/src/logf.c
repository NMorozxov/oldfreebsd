#include "logf.h"
static TokenTable tokens1[]={
           {"3128",1},
           {"110",2},
           {"to",3},
           {"",0}};
int get_ip_from_buf(char *buf)
{
static char buf1[255];
int i;
i=substr(buf,buf1,0,'.');
i=substr(buf,buf1,i,'.');
i=substr(buf,buf1,i,'.');
i=substr_ex(buf,buf1,i,"\n\r ");
return atoi(buf1);
}
int main(int argc, char* argv[])
{
isc_db_handle    DB = 0L;             /* database handle */
isc_tr_handle    trans = NULL;          /* transaction handle */
long             status[20];            /* status vector */
//char             Db_name[128],uname[256], upass[256];
char ISC_FAR *  dpb = NULL;    /* DB parameter buffer */
short dpb_length = 0;
static int bytes,cl_ip;
static char exec_str[256],buf[255],buf1[255];
static int i,dy=0,dm=0,first_time=0;
static long int iptraf[257],ipmail[257],ip_in_traf[257];
FILE *f;
struct tm *tmm;
time_t timer;

if (argc<5)
 {
 printf("ipfw Log Filer ver. 2.0.7 Copyright (C) Nicol Morozov 2002-2003\nUsage logf <dbname> <username> <password> <ip>\n");
 return 1;
 }

bzero(iptraf,sizeof(iptraf));
bzero(ipmail,sizeof(ipmail));
bzero(ip_in_traf,sizeof(ip_in_traf));

f=fopen("/var/log/logf.state","rb");
timer=time(NULL);
tmm=localtime(&timer);
if (f!=NULL)
 {
 fread(&dy,1,sizeof(int),f);
 fread(&dm,1,sizeof(int),f);
 fclose(f);
 }

if (dy!=tmm->tm_year || dm!=tmm->tm_mon)
 {
 first_time=1;
 dy=tmm->tm_year;
 dm=tmm->tm_mon;
 f=fopen("/var/log/logf.state","wb");
 fwrite(&dy,1,sizeof(int),f);
 fwrite(&dm,1,sizeof(int),f);
 fclose(f);
 }

//strcpy(Db_name,"192.168.0.4:d:\\db\\inet.gdb");

// Creating DPB

dpb = (char *) malloc(1);
*dpb = '\1';

/* Add user name and password to DPB. */
isc_expand_dpb(&dpb, (short ISC_FAR *)&dpb_length,
isc_dpb_user_name, uname,
isc_dpb_password, upass,
NULL);

// Connect to database
if (isc_attach_database(status, strlen(Db_name), Db_name, &DB, dpb_length, dpb)) ERREXIT(status,1)

// Start transaction
if (isc_start_transaction(status, &trans, 1, &DB, 0, NULL))  ERREXIT(status, 1)


while (!feof(stdin))
 {
 fgets(buf,255,stdin);
 if (feof(stdin)) break;
 while(buf[strlen(buf)-1]==0xd || buf[strlen(buf)-1]==0xa) buf[strlen(buf)-1]=0;
 i=substr_ex(buf,buf1,0," \t");
 i=substr_ex(buf,buf1,i," \t");
 i=substr_ex(buf,buf1,i," \t");
 bytes=atoi(buf1);
 i=substr_ex(buf,buf1,i," \t");
 if (strcmp(buf1,"count")) continue;
 i=substr_ex(buf,buf1,i," \t");
 if (strcmp(buf1,"ip") && strcmp(buf1,"tcp")) continue;
 i=substr_ex(buf,buf1,i," \t");
 if (strcmp(buf1,"from")) continue;
 i=substr_ex(buf,buf1,i," \t");
 if (strcmp(buf1,"any")) 
  {  
  if (strcmp(buf1,own_ip))
   { 
   /* Outgoing traf */
   cl_ip=get_ip_from_buf(buf1);
   i=substr_ex(buf,buf1,i," \t"); // to
   if (strcmp(buf1,"to")) continue;
   i=substr_ex(buf,buf1,i," \t");
   if (strcmp(buf1,"any"))
    {
    /* local out */
    ip_in_traf[cl_ip]-=bytes;
    }
   else    
    {
    /* total out */
    ip_in_traf[cl_ip]+=bytes;
    }
   }
  else
   {
   /*  Incoming traf */
   i=substr_ex(buf,buf1,i," \t");
   switch(GetToken(tokens1,buf1,0,0))
    {
    case 1: //squid
     i=substr_ex(buf,buf1,i," \t");
     
     if (strcmp(buf1,"to")) continue;
     i=substr_ex(buf,buf1,i,"\n\r ");
     cl_ip=get_ip_from_buf(buf1);
     iptraf[cl_ip]+=bytes;
    break;
    case 2: //pop3
     i=substr_ex(buf,buf1,i," \t");
     if (strcmp(buf1,"to")) continue;
     i=substr_ex(buf,buf1,i,"\n\r ");
     cl_ip=get_ip_from_buf(buf1);
     ipmail[cl_ip]=bytes;    
    break;
    case 3: // total local incoming
     i=substr_ex(buf,buf1,i,"\n\r ");
     cl_ip=get_ip_from_buf(buf1);
     iptraf[cl_ip]-=bytes;       
    break;
    }
   } 
  }
 else
  {
  /* Total incoming rule */
  i=substr_ex(buf,buf1,i," \t");
  if (strcmp(buf1,"to")) continue;
  i=substr(buf,buf1,i,'.');
  i=substr(buf,buf1,i,'.');
  i=substr(buf,buf1,i,'.');
  i=substr_ex(buf,buf1,i,"\n\r ");
  iptraf[atoi(buf1)]+=bytes;
  } 
 }

for (i=1;i<255;i++) 
 if (iptraf[i]+ipmail[i]+ip_in_traf[i]+first_time)
  {
  sprintf(buf,"INSERT INTO LOG(NN,INS_DATE,IP,TRAF,MAIL,TRAF_OUT) VALUES(gen_id(log_gen,1),'now',%ld,%ld,%ld,%ld);",i,iptraf[i],ipmail[i],ip_in_traf[i]);
  if(isc_dsql_execute_immediate(status, &DB, &trans, 0, buf, 1, 0L)) ERREXIT(status, 1)
  }

// Commint transaction
if (isc_commit_transaction(status, &trans)) ERREXIT(status, 1)

// Disconnect
if (isc_detach_database(status, &DB)) ERREXIT(status, 1)

return 0;
}

