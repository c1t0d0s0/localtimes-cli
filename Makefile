CC=gcc
GIT_DATE := $(shell git log -1 --format=%cd --date=format:"%Y%m%d.%H%M%S" 2>/dev/null || echo "unknown")
CFLAGS=-Wall -O3 -DVERSION_STRING="\"$(GIT_DATE)\""
INCLUDE=-I.
PREFIX=$(HOME)
BINDIR=$(PREFIX)/bin

all: localtimes

clean::
	rm -f *.o localtimes zones.inc

install: localtimes
	mkdir -p $(BINDIR)
	cp localtimes $(BINDIR)/localtimes

localtimes: localtimes.o
	${CC} ${CFLAGS} -o localtimes localtimes.o

localtimes.o: localtimes.c zones.inc
	${CC} ${CFLAGS} ${INCLUDE} -c localtimes.c

zones.inc: config.yml
	printf "static const char *embedded_zones[] = {\n" > zones.inc
	sed -n '/^timezones:/,/^[a-z]/ s/^  - "\(.*\)"/      "\1",/p' config.yml >> zones.inc
	printf "};\nstatic const int num_embedded_zones = %d;\n" $$(sed -n '/^timezones:/,/^[a-z]/ s/^  - "\(.*\)"/\1/p' config.yml | wc -l) >> zones.inc
	printf "static const char *current_zone = \"%s\";\n" $$(sed -n 's/^  current: "\(.*\)"/\1/p' config.yml) >> zones.inc
	printf "static const char *important_zones[] = {\n" >> zones.inc
	sed -n '/^  important:/,/^[a-z]/ s/^    - "\(.*\)"/      "\1",/p' config.yml >> zones.inc
	printf "};\nstatic const int num_important_zones = %d;\n" $$(sed -n '/^  important:/,/^[a-z]/ s/^    - "\(.*\)"/\1/p' config.yml | wc -l) >> zones.inc

