#ifndef LOODS3_H
#define LOODS3_H
#include "stdio.h"
#include "stdlib.h"

typedef struct container container;

struct container {
	container *next;
	char *content;
};

typedef struct {
	container *begin;
} loods2;

typedef struct {
	loods2 *loods1;
	loods2 *loods2;
} loods3;


loods2 *maak_loods(void);
loods3 *maak_loods3(void);
container *maak_container(void);
int leeg(loods2 *);
void opslaan(loods3 *, char *);
void opslaan_oud(loods2 *, char *);
char *leveren(loods3 *);
char *leveren_oud(loods2 *);
int sloop_loods(loods3 *);
void verplaatsen(loods3 *);
void verplaats_alles(loods3 *);

#endif
