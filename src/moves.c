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
    char color;
    fflush(stdin);
    printf("%s", color_message);
    scanf("%c", &color);
    if(color == 'r')
    {
        pawn.couleur = RED;
    }
    else if(color == 'b')
    {
        pawn.couleur = WHITE;
    }
    else if(color == 'e')
    {
        pawn.pos.x = -1;
        pawn.pos.y = -1;
        return pawn;
    }

    printf("%s", pos_message);
    scanf("%d %d", &pawn.pos.x, &pawn.pos.y);

    return pawn;
}