#ifndef MOVES_H
#define MOVES_H

#include "plateau.h"




void move(plateau* p, pion pawn,int *pNBB, int *pNBR);
void directMove(plateau* p, int color, int x, int y);
pion inputPawn(char* color_message, char* pos_message,int tour);

#endif /*MOVES_H*/
