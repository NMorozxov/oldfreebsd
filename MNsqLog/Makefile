CC		= gcc
CFLAGS		= -g -O2
INCLUDE		= -I. -I..
LIBS            = -lmn -lm
#CFLAGS_ALL	= $(CFLAGS) -DHAVE_CONFIG_H $(INCLUDE)
CFLAGS_ALL	= $(CFLAGS) $(INCLUDE)

MNSQLOG_OBJS	= mnsqlog.o
MNSQLOG_SRCS	= mnsqlog.c 

.c.o:
	$(CC) -c $(CFLAGS_ALL) $<

all: mnsqlog

mnsqlog: $(MNSQLOG_OBJS)
	$(CC) -o mnsqlog $(MNSQLOG_OBJS) $(LIBS)

clean:
	rm -f core *.o mnsqlog

distclean: clean
	rm -f Makefile *~
	rm -rf .pcomp

# DO NOT DELETE THIS LINE -- make depend depends on it.
