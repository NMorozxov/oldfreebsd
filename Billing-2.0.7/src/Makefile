CC		= gcc
CFLAGS		= -g -O2
INCLUDE		= -I. -I.. -I ../mnlib3
LIBS            = -lfbclient  -lm -lcrypt  ../mnlib3/libmn.a
CFLAGS_ALL	= $(CFLAGS) -DHAVE_CONFIG_H $(INCLUDE)

GENCOUNT_OBJS	= gencount.o
GENCOUNT_SRCS	= gencount.c 
LOGF_OBJS	= logf.o
LOGF_SRCS	= logf.c 

RULES_OBJS	= rules.o
RULES_SRCS	= rules.c

.c.o:
	$(CC) -c $(CFLAGS_ALL) $<

all: gencount logf logf.rules

logf.rules: $(RULES_OBJS)
	$(CC) -o logf.rules $(RULES_OBJS) $(LIBS)

logf: $(LOGF_OBJS)
	$(CC) -o logf $(LOGF_OBJS) $(LIBS)

gencount: $(GENCOUNT_OBJS)
	$(CC) -o gencount $(GENCOUNT_OBJS)

clean:
	rm -f core *.o logf gencount logf.rules

distclean: clean
	rm -f Makefile *~
	rm -rf .pcomp

# DO NOT DELETE THIS LINE -- make depend depends on it.
