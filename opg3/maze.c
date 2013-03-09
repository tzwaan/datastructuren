/*
 * File: maze.c
 *
 * Auteur: Tijmen Zwaan
 * UvA ID: 10208917
 *
 * methodes voor het initialiseren van de maze, inlezen en printen.
 */

#include "maze.h"
#include "walker.h"
#include "stdio.h"
#include "stdlib.h"


maze_t* init_maze(int length, int width) {
   int i;
   maze_t *maze = calloc(1, sizeof(maze_t));
   maze->length = length;
   maze->width = width;
   maze->maze = calloc(length, sizeof(char*));
   for (i=0; i<length; i++) {
      maze->maze[i] = calloc(width, sizeof(char*));
   }
   return maze;
}

maze_t* read_maze(char *maze_file_name) {
   int i, j, length, width;
   maze_t *maze;
   FILE *maze_file;
   if ((maze_file = fopen(maze_file_name, "r")) == NULL) {
      perror("fopen");
      exit(0);
   }
   
   fscanf(maze_file,"%d,%d\n", &length, &width);
   maze = init_maze(length, width);

   for (i=0; i<length; i++) {
      for (j=0; j<width; j++) {
         maze->maze[i][j] = fgetc(maze_file);
      }
      if(fgetc(maze_file) ==EOF)
         break;
   }
   return maze;
}

void print_maze(maze_t *maze, walker_t *walker) {
   int i, j;
   printf("length:%d\nwidth:%d\nrow:%d\ncollum:%d\n",
           maze->length, maze->width, walker->row, walker->col);
   for(i=0; i<maze->length; i++) {
      for(j=0; j<maze->width; j++) {
         if((i == walker->row) && (j == walker->col)) {
            printf("X");
         }
         else {
            printf("%c", maze->maze[i][j]);
         }
      }
      printf("\n");
   }
}

void cleanup_maze (maze_t *maze) {
   free(maze);
   maze = NULL;
}
