#ifndef BOB_H
#define BOB_H


#include "../include/plateau.h"
#include "../include/moves.h"
#include "../include/rules.h"


#define PHASE_PLACEMENT 1
#define PHASE_DEPLACEMENT 0




void copyBoard(plateau p, plateau* p2);


position getRandomMove(plateau p);
int countPawns(plateau p, short color);
int endGamePlacement(plateau* p, int X);
bool checkBoardEmpty(plateau p);
position Monte_Carlo(plateau *p, int X, int interation, short phase);





#endif /*BOB_H*/