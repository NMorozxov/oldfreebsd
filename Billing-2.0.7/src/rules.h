#ifndef _LOGF_RULES_H
#define _LOGF_RULES_H

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

#ifdef HAVE_TIME_H
#include <time.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#define ERREXIT(status, rc)	{isc_print_status(status); return rc;}
#define Db_name argv[1]
#define uname argv[2]
#define upass argv[3]

#include <stdio.h>
#include <ibase.h>

#ifndef false
#define false 0
#endif

#ifndef true
#define true 1
#endif

#endif
