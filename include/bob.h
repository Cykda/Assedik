#ifndef BOB_H
#define BOB_H


#include "../include/plateau.h"
#include "../include/moves.h"
#include "../include/rules.h"





void copyBoard(plateau p, plateau* p2);


position getRandomMove(plateau p);
int endGame(plateau* p, int X, int CurrentPawnNumber);
bool checkBoardEmpty(plateau p);
position Monte_Carlo(plateau *p, int X, int CurrentPawnNumber, int interation);





#endif /*BOB_H*/