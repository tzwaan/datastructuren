/*
 * File: walker.c
 *
 * Auteur: Tijmen Zwaan
 * UvA ID: 10208917
 * 
 * methodes voor het initialiseren van de walker, het checken
 * van mogelijke moves en het uitvoeren van deze moves.
 */

#include "maze.h"
#include "walker.h"


int check_move(maze_t *maze, walker_t *walker, int dir) {
   switch(dir) {
      case 0 : if(maze->maze[walker->row - 1][walker->col] != 35) {return 1;};
               break;
      case 1 : if(maze->maze[walker->row][walker->col + 1] != 35) {return 1;};
               break;
      case 2 : if(maze->maze[walker->row + 1][walker->col] != 35) {return 1;};
               break;
      case 3 : if(maze->maze[walker->row][walker->col - 1] != 35) {return 1;};
               break;
      default: return 0;
   }
   return 0;
}

/* verschil met check_move is dat deze ook checkt op "." */
int check_clear_move(maze_t *maze, walker_t *walker, int dir) {
   switch(dir) {
      case 0 : if(maze->maze[walker->row - 1][walker->col] != 35 &&
                  maze->maze[walker->row - 1][walker->col] != 46) {return 1;};
               break;
      case 1 : if(maze->maze[walker->row][walker->col + 1] != 35 &&
                  maze->maze[walker->row][walker->col + 1] != 46) {return 1;};
               break;
      case 2 : if(maze->maze[walker->row + 1][walker->col] != 35 &&
                  maze->maze[walker->row + 1][walker->col] != 46) {return 1;};
               break;
      case 3 : if(maze->maze[walker->row][walker->col - 1] != 35 &&
                  maze->maze[walker->row][walker->col - 1] != 46) {return 1;};
               break;
      default: return 0;
   }
   return 0;
}

int at_exit(maze_t *maze, walker_t *walker) {
   if(maze->maze[walker->row][walker->col] == 69)
      return 1;
   return 0;
}

walker_t* init_walker(maze_t *maze) {
   int i, j;
   walker_t *walker = calloc(1, sizeof(walker_t));

   for(i=0; i<maze->length; i++) {
      for(j=0; j<maze->width; j++) {
         if(maze->maze[i][j] == 83) {
            walker->row = i;
            walker->col = j;
         }
         if(maze->maze[i][j] == 69) {
            walker->fin_row = i;
            walker->fin_col = j;
         }
      }
   }

   return walker;
}

int move_walker(maze_t *maze, walker_t *walker, int dir) {
   if(check_move(maze, walker, dir)) {
      switch(dir) {
         case 0 : walker->row--; return 1;
         case 1 : walker->col++; return 1;
         case 2 : walker->row++; return 1;
         case 3 : walker->col--; return 1;
         default: break;
      }
   }
   return 0;
}

int clear_move_walker(maze_t *maze, walker_t *walker, int dir) {
   if(check_clear_move(maze, walker, dir)) {
      switch(dir) {
         case 0 : walker->row--; return 1;
         case 1 : walker->col++; return 1;
         case 2 : walker->row++; return 1;
         case 3 : walker->col--; return 1;
         default: break;
      }
   }
   return 0;
}

/* veranderd "." in "#"
 * veranderd " " in "."
 */
void lay_breadcrumb(maze_t *maze, walker_t *walker) {
   if(maze->maze[walker->row][walker->col] == 46) {
      maze->maze[walker->row][walker->col] = 35;
   }
   if(maze->maze[walker->row][walker->col] == 32 ||
      maze->maze[walker->row][walker->col] == 83) {
      maze->maze[walker->row][walker->col] = 46;
   }
}

void cleanup_walker(walker_t *walker) {
   free(walker);
   walker = NULL;
}
