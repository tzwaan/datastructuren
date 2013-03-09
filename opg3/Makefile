PROGNAME=opgave3
VERSION=1.0
ARG1=mazes/map1.txt
ARG2=mazes/map2.txt
ARG3=mazes/map3.txt
ARG4=mazes/disjoint1.txt

MKDIR=mkdir
PACK=tar -jcvf
CC=gcc
CFLAGS=-Wall -pedantic -std=c99
CP=cp
RM=rm -rf
OFILES=$(subst .c,.o,$(wildcard *.c))

$(PROGNAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(PROGNAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o $(PROGNAME) $(PROGNAME)-$(VERSION).tbz

tarball: $(PROGNAME)
	$(MAKE) clean
	$(MKDIR) $(PROGNAME)-$(VERSION)
	$(CP) * $(PROGNAME)-$(VERSION) || true
	$(PACK) $(PROGNAME)-$(VERSION).tbz $(PROGNAME)-$(VERSION)/*
	$(RM) $(PROGNAME)-$(VERSION)

run:
	@$(MAKE) && ./$(PROGNAME) $(ARG1) $(ARG2) $(ARG3) $(ARG4)
