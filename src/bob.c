/*#include <stdio.h>
#include <stdlib.h>
#include "../include/bob.h"



void copyBoard(plateau p, plateau* p2)
{
    for(int i = 0; i < p.N; ++i)
    {
        for(int j = 0; j < p.N; ++j)
        {
            p2->plateau[i][j].info.couleur = p.plateau[i][j].info.couleur;
            p2->plateau[i][j].pos = p.plateau[i][j].pos;
        }
    }
}

int getPossibleMovesNumber(plateau p)
{

    int possibleMovesNumber = 0;


    for(int i = 0; i < p.N; ++i)
    {
        for(int j = 0; j < p.N; ++j)
        {
            if(p.plateau[i][j].info.couleur == NONE)
            {
                possibleMovesNumber++;
            }
        }
    }

    return possibleMovesNumber;
}

position getPossibleMoves(plateau* p, int MoveNumber, short color)
{



    int CurrentMove = MoveNumber;
    position pos;
    pos.x = -1;
    pos.y = -1;

    for(int i = 0; i < p->N; ++i)
    {
        for(int j = 0; j < p->N; ++j)
        {
            if(p->plateau[i][j].info.couleur == NONE)
            {
                CurrentMove--;
            }
            if(CurrentMove <= 0)
            {
                pos.x = j;
                pos.y = i;
                p->plateau[pos.y][pos.x].info.couleur = color;
                return pos;
            }

        }

    }
    return pos;

}

int intMax(int* arr, int size)
{
    int max_element = arr[0];
    for(int i = 0; i < size; ++i)
    {
        if(arr[i] > max_element)
        {
            max_element = arr[i];
        }
    }

    return max_element;
}




void explore(plateau* p, int depth, int i, short color)
{
    if(i >= depth)
    {
        return;
    }

    // listing possible moves
    pion emptypawn;

    emptypawn.info.couleur = NONE;

    for(int i = 1; i < getPossibleMovesNumber(*p) + 1; ++i)
    {
        emptypawn.pos = getPossibleMoves(p, i, color);

        if(emptypawn.pos.x == -1 && emptypawn.pos.y == -1)
        {
            printf("Error At Pawn Place\n");
            return;
        }

        //showBoard(*p);
        //printf("\n\n\n");
        if(color == RED)
        {
            explore(p, depth, i+1, WHITE);
        }
        else
        {
            explore(p, depth, i+1, RED);
        }

    }



}*/
