#ifndef BOB_H
#define BOB_H


#include "plateau.h"

void copyBoard(plateau p, plateau* p2);

int possibleMovesNumber(plateau p);
position applyMove(plateau* p, int moveNumber, short color);
void explore(plateau* p, int depth, int i);

#endif /*BOB_H*/