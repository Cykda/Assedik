#ifndef BOB_H
#define BOB_H


#include "../include/plateau.h"
#include "../include/moves.h"


void copyBoard(plateau p, plateau* p2);

int getPossibleMovesNumber(plateau p);
int getPossibilityNumber(plateau p);
position getPossibleMoves(plateau* p, int MoveNumber, short color);



void explore(plateau* p, int depth, int i, short color);

#endif /*BOB_H*/