/*
 * File: walker.h
 *
 * Auteur: Tijmen Zwaan
 * UvA ID: 10208917
 *
 * Initialisatie van de walker methodes.
 */

#ifndef WALKER_H
#define WALKER_H
#include "stdio.h"
#include "stdlib.h"
#include "structs.h"


walker_t* init_walker(maze_t *maze);
int move_walker(maze_t *maze, walker_t *walker, int dir);
int clear_move_walker(maze_t *maze, walker_t *walker, int dir);
int at_exit(maze_t *maze, walker_t *walker);
int check_move(maze_t *maze, walker_t *walker, int dir);
int check_clear_move(maze_t *maze, walker_t *walker, int dir);
void lay_breadcrumb(maze_t *maze, walker_t *walker);
void cleanup_walker(walker_t *walker);

#endif
