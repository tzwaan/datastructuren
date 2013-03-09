/*
 * File: loods1.c
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
 * opslaan <iets>
 * leveren
 * stop
 */

#include "stdlib.h"
#include "stdio.h"
#include "loods1.h"
#include "string.h"

loods1 *maak_loods(void) {
	loods1 *loods = calloc(1, sizeof(loods1));
	return loods;
}

container *maak_container(void) {
	container *container = calloc(1, sizeof(container));
	return container;
}

int leeg(loods1 *loods) {
	return !loods->begin;
}

void opslaan(loods1 *loods, char *content) {
	container *container = maak_container();
	container->next = loods->begin;
	loods->begin = container;
	container->content = malloc(strlen(content) * sizeof(char));
	strcpy(container->content, content);
}

char *leveren(loods1 *loods) {
	if (leeg(loods))
		return NULL;
	container *container = loods->begin;
	char *content = loods->begin->content;
	loods->begin = container->next;
	free(container);
	return content;
}

int sloop_loods(loods1 *loods) {
	while(!leeg(loods)) {
		leveren(loods);
	}
	free(loods);
	return 0;
}
