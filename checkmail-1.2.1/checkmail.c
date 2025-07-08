#include "checkmail.h"
int main (int argvc, char **argv)
{
FILE *fout;
static char fname[255],buf[1024],dname[255],msg_from[255],msg_to[255];
int i,ret_stat=0;

#ifdef HAVE_SRANDOMDEV
srandomdev();
#elif HAVE_SRANDOM
srandom(time(NULL));
#endif


printf("Checkmail 1.2.1 (For KAV 4.5) AntiVirus Mail Checker Copyright (C) 2002 by Nicol Morozov\n");

if (argvc<3) {printf("Missing Arguments from to\n");exit(EX_USAGE);}

for (i=1;i<argvc;i++) 
 {
 if (!strcmp(argv[i],"-r")) strcpy(msg_from,argv[i+1]);
 if (!strcmp(argv[i],"-d")) strcpy(msg_to,argv[i+1]);
 }

sprintf(fname,"/tmp/mail.check%lu.%lu",time(NULL),random());
sprintf(dname,"/tmp/mail.check.dir%lu.%lu",time(NULL),random());
fout=fopen(fname,"w");
while (!feof(stdin)) 
 {
 fgets(buf,254,stdin);
 fputs(buf,fout);
 }
fclose(fout);
sprintf(buf,"mkdir %s ; /usr/local/bin/uudeview -i -p %s %s",dname,dname,fname);
system(buf);
sprintf(buf,"/usr/local/share/kav/bin/kavscanner -eP -eA -eS -eB  -eM -r -q -i0 %s %s > /dev/null",dname,fname);
i=system(buf);
switch (i) {
case 0:
 sprintf(buf,"/usr/libexec/mail.local -d %s < %s",msg_to,fname);
 break;
case 6400:
 syslog(LOG_MAIL,"This message contains a virus");
 printf("\n\n\t\t\t*** VIRUS ALERT ***\n\nThis message contains a virus, and will be delivered to 'virused' mailbox.\n");
 sprintf(buf,"/usr/libexec/mail.local -d virused < %s",fname);
 break;
case 5120:
case 5376:
 syslog(LOG_MAIL,"This message is virus suspicious");
 printf("\n\n\t\t\t*** VIRUS SUSPICIOUS ***\n\nThis message is virus suspicious, and will be delivered to 'virused' mailbox.\n");
 sprintf(buf,"/usr/libexec/mail.local -d virused < %s",fname);
 break;
case 7680:
 sprintf(buf,"\nSystem Error during Antivirus Scan\n");
 printf(buf);
 syslog(LOG_MAIL,buf);
 sprintf(buf,"/usr/libexec/mail.local -d %s < %s",msg_to,fname);
 break;
default:
 sprintf(buf,"\nUnknown Error, Antivirus returns error code = %lu\n",i);
 printf(buf);
 syslog(LOG_MAIL,buf);
 sprintf(buf,"/usr/libexec/mail.local -d %s < %s",msg_to,fname);
}
ret_stat=system(buf); 
unlink(fname);
sprintf(buf,"rm -rf %s",dname);
system(buf);
return ret_stat;
}
