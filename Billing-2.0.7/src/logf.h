#ifndef _LOGF_LOGF_H
#define _LOGF_LOGF_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_STLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_TIME_H
#include <time.h>
#endif

#include <mnlib3.h>

#define ERREXIT(status, rc)	{isc_print_status(status); return rc;}

#include <stdio.h>
#include <ibase.h>
//#include "port_typ.h"

#define Db_name argv[1]
#define uname argv[2]
#define upass argv[3]
#define own_ip argv[4] 

#endif
