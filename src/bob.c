#include <stdio.h>
#include <stdlib.h>
#include "../include/bob.h"



void copyBoard(plateau p, plateau* p2)
{
    for(int i = 0; i < p.N; ++i)
    {
        for(int j = 0; j < p.N; ++j)
        {
            p2->plateau[i][j].couleur = p.plateau[i][j].couleur;
            p2->plateau[i][j].pos = p.plateau[i][j].pos;
        }
    }
}

int possibleMovesNumber(plateau p)
{
    int possible_moves = 0;
    for(int i = 0; i < p.N; ++i)
    {
        for(int j = 0; j < p.N; ++j)
        {
            if(p.plateau[i][j].couleur == NONE)
            {
                possible_moves++;
            }
        }
    }
    return possible_moves;
}

position applyMove(plateau* p, int moveNumber, short color)
{

    position pos;
    pos.x = 0;
    pos.y = 0;
    int currentMoveNumber = moveNumber;
    for(int i = 0; i < p->N; ++i)
    {
        for(int j = 0; j < p->N; ++j)
        {
            if(p->plateau[i][j].couleur == NONE)
            {
                currentMoveNumber--;
            }
            if(currentMoveNumber <= 0)
            {
                p->plateau[i][j].couleur = color;
                pos.x = j;
                pos.y = i;
                return pos;
            }
        }
    }
}


void explore(plateau* p, int depth, int i)
{
    if(i >= depth)
    {
        return;
    }

    // listing possible moves

    for(int i = 0; i < possibleMovesNumber(*p); ++i)
    {

    }



}