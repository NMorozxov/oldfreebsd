DIRS	= mnlib3 src

all:
	for i in $(DIRS); do (cd $$i && $(MAKE) $@) || exit 1; done

clean:
	rm -rf autom4te.cache config.log
	rm -f *~
	for i in $(DIRS); do (cd $$i && $(MAKE) $@) || exit 1; done

distclean: clean
	for i in $(DIRS); do (cd $$i && $(MAKE) $@) || exit 1; done
	rm -f config.cache config.status config.h config.log config.h.in configure
