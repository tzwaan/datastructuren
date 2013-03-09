/*
 * File: structs.h
 *
 * Auteur: Tijmen Zwaan
 * UvA ID: 10208917
 *
 * initialisatie van de structs.
 */

#ifndef STRUCTS_H
#define STRUCTS_H
#include "stdio.h"
#include "stdlib.h"

typedef struct {
   int row,
       col,
       fin_row,
       fin_col;
} walker_t;

typedef struct {
   int length,
       width;
   char **maze;
} maze_t;

#endif
