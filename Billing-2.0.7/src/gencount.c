#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv)
{
int rule,i;
char addr[15];

if (argc>2) strcpy(addr,argv[2]);
else strcpy(addr,"192.168.1");

for (((argc>1)?(rule=atoi(argv[1])):(rule=50)),i=1;i<255;i++)
 {
 printf("${fwcmd} add %u  count ip  from any to %s.%u\n",rule++,addr,i);
 printf("${fwcmd} add %u  count tcp from ${iip1} pop3 to %s.%u\n",rule++,addr,i);
 printf("${fwcmd} add %u  count tcp from ${iip1} 3128 to %s.%u\n",rule++,addr,i);
 printf("${fwcmd} add %u  count ip  from ${iip1} to %s.%u\n",rule++,addr,i);
 printf("${fwcmd} add %u  count ip  from %s.%u to %s.0/24\n",rule++,addr,i,addr);
 printf("${fwcmd} add %u  count ip  from %s.%u to any\n\n",rule++,addr,i);
 }
return;
}
