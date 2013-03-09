/*
 * File: opgave.c
 * benadert het getal Pi door middel van het genereren van random
 * punten binnen een 1x1 vlak. hierna wordt gecheckt of de punten
 * binnen de cirkel met middelpunt 0.0, en straal 1 vallen.
 * de verhouding tussen het totaal aantal punten en het aantal
 * punten binnen de cirkel worden omgerekend tot de benadering
 * van Pi
 *
 * Usage: opgave1 [number of random dots]
 *
 * Auteur: Tijmen Zwaan
 * Uva-id: 10208917
 * 8 Feb 2013
 *
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double pythagoras(double x, double y){
   return((x*x) + (y*y));
}

int main(int argc, char *argv[]){
   if(argc<=1){
      printf("no argument given\n\n");
      return(0);
   }
   int input = atoi(argv[1]);
   int i=input, inCircle=0;
   double pi, x, y, z;
   srand(1);
   for (; i; i--) {
      x = (double)rand()/(double)RAND_MAX;
      y = (double)rand()/(double)RAND_MAX;
      z = pythagoras(x,y);
      if(z<1)
         inCircle++;
   }
	printf("total points: %i\npoints in circle: %i\n", input, inCircle);
	pi = (inCircle/(double)input) * 4;
	printf("pi: %f \n", pi);
	return(0);
}
