#ifndef MAIN_H
#define MAIN_H

#include "gba.h"

// TODO: Create any necessary structs

/*
* For example, for a Snake game, one could be:
*
* struct snake {
*   int heading;
*   int length;
*   int row;
*   int col;
* };
*
* Example of a struct to hold state machine data:
*
* struct state {
*   int currentState;
*   int nextState;
* };
*
*/
typedef struct dart{
  int row;
  int col;
  int width;
  int height;
  //int timer;
} Dart;
typedef struct balloon{
  int row;
  int col;

} Balloon;

int collision(Dart d);

void move(Dart *d, int directionLR, int directionUD);


//struct state{
//  enum gba_state state;
//  int size;
//  struct balloon balloons;
//
#endif
