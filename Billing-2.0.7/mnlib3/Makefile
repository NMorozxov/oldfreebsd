CC		= gcc
CFLAGS		= -g -O2
INCLUDE		= -I. -I..
CFLAGS_ALL	= $(CFLAGS) -DHAVE_CONFIG_H $(INCLUDE)
prefix		= /usr/local

MNLIB_OBJS	= stringop.o token.o checks.o month.o round.o
MNLIB_SRCS	= stringop.c token.c checks.c month.c round.c
MNLIB_LIBNAME	= libmn.so.3

.c.o:
	$(CC) -c $(CFLAGS_ALL) $< 

all: libmn.a $(MNLIB_LIBNAME)

$(MNLIB_LIBNAME): $(MNLIB_OBJS)
#	ld -shared -o $(MNLIB_LIBNAME) -f $(MNLIB_LIBNAME) $(MNLIB_OBJS)
	ld -shared -o $(MNLIB_LIBNAME) -soname=$(MNLIB_LIBNAME) $(MNLIB_OBJS)
	ln -sf $(MNLIB_LIBNAME) libmn.so

libmn.a: $(MNLIB_OBJS)
	rm -f libmn.a
	ar -rc libmn.a $(MNLIB_OBJS)

clean:
	rm -f *.o 
	rm -f libmn.a
	rm -f libmn.so
	rm -f $(MNLIB_LIBNAME)

install:
	cp mnlib2.h $(prefix)/include
	cp $(MNLIB_LIBNAME) $(prefix)/lib
	cp libmn.a $(prefix)/lib
	cd $(prefix)/lib;ln -sf $(MNLIB_LIBNAME) libmn.so

# DO NOT DELETE THIS LINE -- make depend depends on it.
