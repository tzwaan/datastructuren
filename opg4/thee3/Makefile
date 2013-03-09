PROGNAME=opgave4
VERSION=1.0

MKDIR=mkdir
PACK=tar -jcvf
CC=gcc
CFLAGS=-Wall -pedantic -std=c99
CP=cp
RM=rm -rf
OFILES=$(subst .c,.o,$(wildcard *.c))

$(PROGNAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(PROGNAME)

%.0: %.c
	$(CC) $(CFLAGS) -c $< -0 $@

clean:
	$(RM) *.o $(PROGNAME) $(PROGNAME)-$(VERSION).tbz

tarball: $(PROGNAME)
	$(MAKE) clean
	$(MKDIR) $(PROGNAME)-$(VERSION)
	$(CP) * $(PROGNAME)-$(VERSION) || true
	$(PACK) $(PROGNAME)-$(VERSION).tbz $(PROGNAME)-$(VERSION)/*
	$(RM) $(PROGNAME)-$(VERSION)

run:
	@$(MAKE) && ./$(PROGNAME) $(ARGS)
