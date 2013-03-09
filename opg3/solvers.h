/*
 * File: solvers.h
 *
 * Auteur: Tijmen Zwaan
 * UvA ID: 10208917
 *
 * initialisatie van de solver methodes.
 */

#ifndef SOLVERS_H
#define SOLVERS_H


int random_solver(maze_t *maze, walker_t *walker);

int wall_follower_right(maze_t *maze, walker_t *walker, int dir);

int wall_follower_left(maze_t *maze, walker_t *walker, int dir);

int tremaux_solver(maze_t *maze, walker_t *walker, int dir);

#endif
