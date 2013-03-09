/*
 * File: maze.h
 *
 * Auteur: Tijmen Zwaan
 * UvA ID: 10208917
 *
 * initialisatie van de maze methodes.
 */

#ifndef MAZE_H
#define MAZE_H

#include "stdio.h"
#include "stdlib.h"
#include "structs.h"


maze_t* init_maze(int length, int width);
maze_t* read_maze(char *maze_file_name);
void print_maze(maze_t *maze, walker_t *walker);
void cleanup_maze(maze_t *maze);

#endif
