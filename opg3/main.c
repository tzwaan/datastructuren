/*
 * File: main.c
 *
 * Auteur: Tijmen Zwaan
 * UvA ID: 10208917
 *
 * Dit programma kan meerdere doolhoven inladen, waarna
 * het een aantal oplossers erop los laat.
 * het print het doolhof en de tussenstappen uit, en
 * vertelt in hoeveel stappen het doolhof kan worden
 * opgelost met de verscheidene oplossers.
 */

#include "maze.h"
#include "walker.h"
#include "solvers.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define MAX_STEPS 5000
#define NUMBER_OF_SOLVERS 4
#define START_AT 0

int main (int argc, char *argv[]) {
   srand(time(NULL));
   int maze_counter;

   if(argc < 2) {
      printf("geef het doolhof mee als argument dommerik!\n\n");
      return 0;
   }
   
   for(maze_counter=1; maze_counter<argc; maze_counter++) {
      int global_counter;
      for(global_counter=START_AT; global_counter<NUMBER_OF_SOLVERS; global_counter++) {
         maze_t *maze;
         walker_t *walker;
         int count=0, dir = 0;

         maze = read_maze(argv[maze_counter]);
         walker = init_walker(maze);
         print_maze(maze, walker);

         while (count < MAX_STEPS) {
            count++;
            switch(global_counter) {
               case 0 : dir = random_solver(maze, walker); break;
               case 1 : dir = wall_follower_right(maze, walker, dir); break;
               case 2 : dir = wall_follower_left(maze, walker, dir); break;
               case 3 : dir = tremaux_solver(maze, walker, dir); break;
               default: return 0;
           }

         /* uncomment dit als je een groot doolhof hebt, en je dus niet iedere
          * tussenstap wilt printen. hierdoor gaat het geheel veel sneller.
          */
          //  if (!(count % 300)){
               print_maze(maze, walker);
               printf("%d\n", count);
          //  }
            if (at_exit(maze, walker))
               break;
            }

         if (count < MAX_STEPS)
            printf("Found exit after %d steps\n", count);
         if (count == MAX_STEPS)
            printf("It seems this maze is unsolvable within %d steps with this certain method.\n", count);
            printf("Press enter to continue\n");
            getchar();

         cleanup_maze(maze);
         cleanup_walker(walker);
      }
   }
   return 0;

}
