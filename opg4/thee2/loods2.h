#ifndef LOODS2_H
#define LOODS2_H
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


loods2 *maak_loods(void);
container *maak_container(void);
int leeg(loods2 *);
void opslaan(loods2 *, char *);
char *leveren(loods2 *);
int sloop_loods(loods2 *);
char *verplaasten(loods2 *, loods2 *);

#endif
