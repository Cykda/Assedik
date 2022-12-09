#ifndef MOVES_H
#define MOVES_H

#include "plateau.h"




void placement(plateau* p, pion pawn,int *pNBB, int *pNBR);
void directMove(plateau* p, int color, int x, int y);
pion inputPawn(char* color_message, char* pos_message,int tour);
int choix_deplacement(plateau* p,pion pawn);
int coup_special(plateau* p,int tour,int N);
int deplacement_pion(plateau* p,pion pawn,int tour,int N);

#endif /*MOVES_H*/
