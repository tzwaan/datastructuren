/*
 * File: solvers.c
 *
 * Auteur: Tijmen Zwaan
 * UvA ID: 10208917
 *
 * De verschillende solver algoritmes
 */

#include "stdlib.h"
#include "stdio.h"
#include "maze.h"
#include "walker.h"
#include "solvers.h"


int random_solver(maze_t *maze, walker_t *walker) {
   int dir = (rand() % 4);
   while(!move_walker(maze, walker, dir)) {
      dir = (rand() % 4);
   }
   return dir;
}

int wall_follower_right(maze_t *maze, walker_t *walker, int dir) {
   dir = ((dir+1) % 4);
   while(!move_walker(maze, walker, dir)) {
      dir = ((dir+3) % 4);
   }
   return dir;
}

int wall_follower_left(maze_t *maze, walker_t *walker, int dir) {
   dir = ((dir+3) % 4);
   while(!move_walker(maze, walker, dir)) {
      dir = ((dir+1) % 4);
   }
   return dir;
}

/*
 * creeert een pad achter zich waaraan hij kan zien waar hij
 * al is geweest. Bij het tegenkomen van een oud pad beschouwd
 * hij dit als een doodlopend eind en maakt rechtsomkeert.
 * een pad waar 2 keer overheen wordt gelopen wordt veranderd in
 * een nieuwe muur.
 *
 * Kan alle doolhoven oplossen.
 */
int tremaux_solver(maze_t *maze, walker_t *walker, int dir) {
   int counter=0, i, new_path=0;
   printf("start_dir:%d\n", dir);
   
   if(maze->maze[walker->row][walker->col] == 32 ||
      maze->maze[walker->row][walker->col] == 83)
      new_path = 1;
   else
      new_path = 0;

   for(i=0; i<4; i++) {
      if(check_clear_move(maze, walker, ((dir + i) % 4))) {
         counter++;
      }
   }
   printf("counter:%d\n", counter);

   if(!counter && new_path) {
      dir = ((dir + 2) % 4);
      lay_breadcrumb(maze, walker);
      lay_breadcrumb(maze, walker);
      move_walker(maze, walker, dir);
      return dir;
   }

   if(!counter && !new_path) {
      lay_breadcrumb(maze, walker);
      while(!move_walker(maze, walker, dir))
         dir = ((dir + 1) % 4);
   }

   if(counter && new_path) {
      lay_breadcrumb(maze, walker);
      while(!clear_move_walker(maze, walker, dir))
         dir = ((dir + 1) % 4);
      return dir;
   }

   if(counter && !new_path) {
      while(!clear_move_walker(maze, walker, dir))
         dir = ((dir + 1) % 4);
      return dir;
   }

   return dir;
}
