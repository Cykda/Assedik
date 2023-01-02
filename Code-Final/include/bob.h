#ifndef BOB_H
#define BOB_H


#include "../include/plateau.h"
#include "../include/moves.h"
#include "../include/rules.h"


#define PHASE_PLACEMENT 1
#define PHASE_DEPLACEMENT 0

#define MAX_DISPLACEMENT_ITERATION 100



typedef struct
{
    position displacementPos;
    position pos_to_move;
    
    
    short state;

} MonteCarlo;
void copyBoard(plateau p, plateau* p2);


position getRandomMove(plateau p);
position getRandomPawnPos(plateau p, short color, int X);
position getRandomDisplacement(plateau p, position pawn);
position* getDisplacementPossibilities(plateau p, position pos);

int countPawns(plateau p, short color);
int endGamePlacement(plateau* p, int X);
int endGameDisplacement(plateau* p, int X);

bool checkBoardEmpty(plateau p);
MonteCarlo Monte_Carlo(plateau *p, int X, int interation, short phase);





#endif /*BOB_H*/