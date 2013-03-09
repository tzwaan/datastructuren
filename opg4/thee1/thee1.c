/*
 * File: thee1.c
 *
 * Auteur: Tijmen Zwaan
 * UvA ID: 10208917
 *
 * Dit programma creeert een command promt dat een thee-silo van een
 * theehandel bedrijf nadoet.
 * Deze file zal alleen opslaan, leveren en stoppen.
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
#include "thee1.h"
#include "string.h"
#define BUFFERSIZE 200

int main(void) {
	char input[BUFFERSIZE], *command, *thee;

	loods1* loods = maak_loods();
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
			sloop_loods(loods);
			return 0;
		}
		else if (!strcmp("opslaan", command)) {
			thee = strtok(NULL, "\0");
			opslaan(loods, thee);
			printf("%s wordt opgeslagen.", thee);
		}
		else if (!strcmp("leveren", command)) {
			thee = leveren(loods);
			if(thee) {
				printf("%s wordt geleverd.", thee);
				/* free the leftover string from te container struct */
				free(thee);
			}
			else {
				printf("Er is geen thee meer in voorraad.");
			}
		}
		else {
			printf("Dit is geen geldig commando");
		}
	}
}
