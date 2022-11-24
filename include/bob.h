#ifndef BOB_H
#define BOB_H


#include "../include/plateau.h"
#include "../include/moves.h"
#include "../include/rules.h"



void copyBoard(plateau p, plateau* p2);

int getPossibleMovesNumber(plateau p);
int getPossibilityNumber(plateau p);
position getPossibleMoves(plateau* p, int MoveNumber, short color);
int intMax(int* arr, int size);
int getBoardScore(plateau p, short color);
float get_heuristic_value(plateau* p);
int explore(plateau* p, int depth, bool minimizing);
#endif /*BOB_H*/