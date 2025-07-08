CC		= gcc
CFLAGS		= -g -O2
INCLUDE		= -I.
LIBS            = 
CFLAGS_ALL	= $(CFLAGS) -DHAVE_CONFIG_H $(INCLUDE)

OBJS	= checkmail.o
SRCS	= checkmail.c

.c.o:
	$(CC) -c $(CFLAGS_ALL) $<

checkmail: $(OBJS)
	$(CC) -o checkmail $(OBJS) $(LIBS)

all: checkmail

clean:
	rm -f config.log core *.o checkmail

# DO NOT DELETE THIS LINE -- make depend depends on it.
