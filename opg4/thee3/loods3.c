/*
 * File: loods3.c
 *
 * Auteur: Tijmen Zwaan
 * UvA ID: 10208917
 *
 * Dit programma creeert een command promt dat een thee-silo van een
 * theehandel bedrijf nadoet.
 * Deze file bevat alle functies die worden aangeroepen door thee.c.
 * Verder bevat het ook 2 'silos' die worden gecombineerd waardoor
 * het voor 'thee.c' lijkt alsof er maar 1 silo is.
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
#include "loods3.h"
#include "string.h"

loods2 *maak_loods(void) {
	loods2 *loods = calloc(1, sizeof(loods2));
	return loods;
}

loods3 *maak_loods3(void) {
	loods3 *loods = calloc(1, sizeof(loods3));
	loods->loods1 = maak_loods();
	loods->loods2 = maak_loods();
	return loods;
}

container *maak_container(void) {
	container *container = calloc(1, sizeof(container));
	return container;
}

int leeg(loods2 *loods) {
	return !loods->begin;
}

void opslaan(loods3 *loods, char *content) {
	container *container = maak_container();
	container->next = loods->loods1->begin;
	loods->loods1->begin = container;
	container->content = malloc(strlen(content) * sizeof(char));
	strcpy(container->content, content);
	printf("%s wordt opgeslagen in loods 1.\n", content);
}

void opslaan_oud(loods2 *loods, char *content) {
	container *container = maak_container();
	container->next = loods->begin;
	loods->begin = container;
	container->content = malloc(strlen(content) * sizeof(char));
	strcpy(container->content, content);
}

char *leveren(loods3 *loods) {
	if (!leeg(loods->loods2)) {
		printf("%s wordt geleverd uit loods 2\n", loods->loods2->begin->content);
		return leveren_oud(loods->loods2);
	}
	else if (!leeg(loods->loods1)) {
		verplaats_alles(loods);
		printf("%s wordt geleverd uit loods 2\n", loods->loods2->begin->content);
		return leveren_oud(loods->loods2);
	}
	else {
		return NULL;
	}
}

char *leveren_oud(loods2 *loods) {
	if (leeg(loods))
		return NULL;
	container *container = loods->begin;
	char *content = loods->begin->content;
	loods->begin = container->next;
	free(container);
	return content;
}

int sloop_loods(loods3 *loods) {
	while(leveren(loods));
	free(loods->loods1);
	free(loods->loods2);
	free(loods);
	return 0;
}

void verplaatsen(loods3 *loods) {
	char *content;
	content = leveren_oud(loods->loods1);
	if (content) {
		opslaan_oud(loods->loods2, content);
	}
	printf("%s wordt verplaatst van loods 1 naar loods 2.\n", content);
	free(content);
}

void verplaats_alles(loods3 *loods) {
	while (!leeg(loods->loods1)) {
		verplaatsen(loods);
	}
}
