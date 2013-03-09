#ifndef LOODS1_H
#define LOODS1_H
#include "stdio.h"
#include "stdlib.h"

typedef struct container container;

struct container {
	container *next;
	char *content;
};

typedef struct {
	container *begin;
} loods1;


loods1 *maak_loods(void);
container *maak_container(void);
int leeg(loods1 *);
void opslaan(loods1 *, char *);
char *leveren(loods1 *);
int sloop_loods(loods1 *);

#endif
