/*
 * File: thee2.c
 *
 * Auteur: Tijmen Zwaan
 * UvA ID: 10208917
 *
 * Dit programma creeert een command promt dat een thee-silo van een
 * theehandel bedrijf nadoet.
 * Deze file zal alleen opslaan, leveren en stoppen in verschillende silos.
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
#define BUFFERSIZE 200

int main(void) {
	char input[BUFFERSIZE], *command, *thee;

	loods2* loods1 = maak_loods();
	loods2* loods2 = maak_loods();
	printf("Welkom bij ons theebedrijf. Geef opdrachten:");

	while(1) {
		printf("\n> ");

		/* gets user input */
		if (fgets(input, sizeof input, stdin) == NULL){
			printf("Dat is natuurlijk geen input");
		}

		/* strips input of trailing linebreak */
		if (input[strlen(input) - 1] == '\n') {
			input[strlen(input) - 1] = '\0';
		}

		command = strtok(input, " \0");

		if (!strcmp("stop", command)) {
			printf("Tot ziens.\n");
			sloop_loods(loods1);
			return 0;
		}
		else if (!strcmp("opslaan1", command)) {
			thee = strtok(NULL, "\0");
			opslaan(loods1, thee);
			printf("%s wordt opgeslagen in loods 1.", thee);
		}
		else if (!strcmp("opslaan2", command)) {
			thee = strtok(NULL, "\0");
			opslaan(loods2, thee);
			printf("%s wordt opgeslagen in loods 2.", thee);
		}
		else if (!strcmp("leveren1", command)) {
			thee = leveren(loods1);
			if(thee) {
				printf("%s wordt geleverd uit loods 1.", thee);
				/* free the leftover string from te container struct */
				free(thee);
			}
			else {
				printf("Er is geen thee meer in voorraad in loods 1.");
			}
		}
		else if (!strcmp("leveren2", command)) {
			thee = leveren(loods2);
			if (thee) {
				printf("%s wordt geleverd uit loods 2.", thee);
				/* free the leftover string from te container struct */
				free(thee);
			}
			else {
				printf("Er is geen thee meer in voorraad in loods 2.");
			}
		}
		else if (!strcmp("verplaatsen12", command)) {
			thee = verplaatsen(loods1, loods2);
			if (thee) {
				printf("%s wordt verplaatst van loods 1 naar loods 2", thee);
				/* free the leftover string from the container struct */
				free(thee);
			}
			else {
				printf("Er is geen thee meer in voorraad in loods 1.");
			}
		}
		else if (!strcmp("verplaatsen21", command)) {
			thee = verplaatsen(loods2, loods1);
			if (thee) {
				printf("%s wordt verplaatst van loods 2 naar loods 1", thee);
				/* free the leftover string from the container struct */
				free(thee);
			}
			else {
				printf("Er is geen thee meer in voorraad in loods 2.");
			}
		}
		else {
			printf("Dit is geen geldig commando");
		}
	}
}
