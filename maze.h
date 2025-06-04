/*
============================================================
  Fichero: maze.h
  Creado: 02-06-2025
  Ultima Modificacion: dimecres, 4 de juny de 2025, 07:39:27
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include <stdlib.h>
#include <stdio.h>

#define NOUT 0
#define NORTH 1
#define WEST 2
#define EAST 4
#define SOUTH 8

typedef unsigned char u1;
typedef unsigned short u2;
typedef unsigned int u4;

typedef u1* Maze;

Maze mazenew(u2 w,u2 h);

u1 mazeget(Maze maze,u1 x,u1 y);

void mazedel(Maze* maze);
