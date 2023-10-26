PREFIX  := /usr/local
CC      := cc
CFLAGS  := -pedantic -Wall -Wno-deprecated-declarations -Os

all: mustat

mustat: mustat.c config.h
	${CC} -o $@ mustat.c ${CFLAGS}

config.h:
	cp config.def.h $@

clean:
	rm -f *.o mustat

install: mustat
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f mustat ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/mustat

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/mustat

.PHONY: all clean install uninstall
