/*
 * File: loods2.c
 *
 * Auteur: Tijmen Zwaan
 * UvA ID: 10208917
 *
 * Dit programma creeert een command promt dat een thee-silo van een
 * theehandel bedrijf nadoet.
 * Deze file bevat alle functies die worden aangeroepen door thee.c.
 *
 * gebruik:
 * run de file
 *
 * commands in prompt:
 * opslaan1 <iets>
 * opslaan2 <iets>
 * leveren1
 * leveren2
 * verplaatsen12
 * verplaatsen21
 * stop
 */

#include "stdlib.h"
#include "stdio.h"
#include "loods2.h"
#include "string.h"

loods2 *maak_loods(void) {
	loods2 *loods = calloc(1, sizeof(loods2));
	return loods;
}

container *maak_container(void) {
	container *container = calloc(1, sizeof(container));
	return container;
}

int leeg(loods2 *loods) {
	return !loods->begin;
}

void opslaan(loods2 *loods, char *content) {
	container *container = maak_container();
	container->next = loods->begin;
	loods->begin = container;
	container->content = malloc(strlen(content) * sizeof(char));
	strcpy(container->content, content);
}

char *leveren(loods2 *loods) {
	if (leeg(loods))
		return NULL;
	container *container = loods->begin;
	char *content = loods->begin->content;
	loods->begin = container->next;
	free(container);
	return content;
}

int sloop_loods(loods2 *loods) {
	while(!leeg(loods)) {
		leveren(loods);
	}
	free(loods);
	return 0;
}

char *verplaatsen(loods2 *loods1, loods2 *loods2) {
	char *content;
	content = leveren(loods1);
	if (content) {
		opslaan(loods2, content);
	}
	else {
		return NULL;
	}
	return content;
}
