#include <stdlib.h>
#include <stdio.h>
#include "../include/moves.h"



void move(plateau* p, pion pawn,int *pNBB, int *pNBR)
{

    p->plateau[pawn.pos.y][pawn.pos.x].info.couleur = pawn.info.couleur;
    if (pawn.info.couleur==WHITE)
    {
        *pNBB=*pNBB-1;
        pawn.info.quantite=*pNBB;
    }
    if (pawn.info.couleur==RED)
    {
        *pNBR=*pNBR-1;
        pawn.info.quantite=*pNBR;
    }

}


void directMove(plateau* p, int color, int x, int y)
{
    //couleur c = color;
    p->plateau[y][x].info.couleur = color;
}

pion inputPawn(char* color_message, char* pos_message,int tour)
{
    int quitter=0;
    pion pawn;
    printf("%s", color_message);
    scanf("%d", &quitter);
    if(quitter == 1)
    {
        pawn.info.couleur=-2;
        pawn.pos.x = -1;
        pawn.pos.y = -1;

        return pawn;
    }
    pawn.info.couleur=tour;
    printf("%s", pos_message);
    scanf("%d %d", &pawn.pos.x, &pawn.pos.y);

    return pawn;
}
