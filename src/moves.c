#include <stdlib.h>
#include <stdio.h>
#include "../include/moves.h"



void move(plateau* p, pion pawn)
{

    p->plateau[pawn.pos.y][pawn.pos.x].couleur = pawn.couleur;

}


void directMove(plateau* p, int color, int x, int y)
{
    //couleur c = color;
    p->plateau[y][x].couleur = color;
}

pion inputPawn(char* color_message, char* pos_message)
{

    pion pawn;
    printf("%s", color_message);
    scanf("%d", &pawn.couleur);
    if(pawn.couleur == -2)
    {
        pawn.pos.x = -1;
        pawn.pos.y = -1;

        return pawn;
    }
    printf("%s", pos_message);
    scanf("%d %d", &pawn.pos.x, &pawn.pos.y);

    return pawn;
}