#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

int getPossibleMovesNumber(plateau p)
{
    
    int possibleMovesNumber = 0;

    
    for(int i = 0; i < p.N; ++i)
    {
        for(int j = 0; j < p.N; ++j)
        {
            if(p.plateau[i][j].couleur == NONE)
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
            if(p->plateau[i][j].couleur == NONE)
            {
                CurrentMove--;
            }
            if(CurrentMove <= 0)
            {
                pos.x = j;
                pos.y = i;
                p->plateau[pos.y][pos.x].couleur = color;
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


int getBoardScore(plateau p, short color)
{
    
    int score = 0;
    
    
    for(int i = 0; i < p.N; ++i)
    {
        for(int j = 0; j < p.N; ++j)
        {
            if(p.plateau[i][j].couleur == color)
            {
                score++;
            }
            
        }
    }
    
    return score;
}

float get_heuristic_value(plateau* p)
{
    return (float)getBoardScore(*p, RED) / (float)getBoardScore(*p, WHITE);
}

int explore(plateau* p, int depth, bool minimizing)
{

    if(depth <= 0)
    {
        //printf("Hello World3\n");
        int val = get_heuristic_value(p);
        printf("SCORE: %d\n", val);
        return val;
    }

    int value;

    if(minimizing == true)
    {
        printf("max\n");
        //printf("Hello World2\n");
        value = -INFINITY;

        // listing possible moves
        pion emptypawn;
        
        emptypawn.couleur = NONE;
        
        for(int i = 1; i < getPossibleMovesNumber(*p) + 1; ++i)
        {
            emptypawn.pos = getPossibleMoves(p, i, RED);

            if(emptypawn.pos.x == -1 && emptypawn.pos.y == -1)
            {
                printf("Error At Pawn Place\n");
                return -1;
            }




            
            value = fmax(value, explore(p, depth - 1, false));
            //printf("MAXIMIZING: %d\n", value);
            move(p, emptypawn);
        }

    }
    else if(minimizing == false)
    {
        printf("min\n");
        // listing possible moves
        pion emptypawn;
        value = INFINITY;
        emptypawn.couleur = NONE;
        
        for(int i = 1; i < getPossibleMovesNumber(*p) + 1; ++i)
        {
            emptypawn.pos = getPossibleMoves(p, i, WHITE);

            if(emptypawn.pos.x == -1 && emptypawn.pos.y == -1)
            {
                printf("Error At Pawn Place\n");
                return -1;
            }





            //printf("MINIMIZING: %d\n", value);
            value = fmin(value, explore(p, depth - 1, true));
            move(p, emptypawn);
        }
  
    }
    //printf("Hello World\n");
    return value;



    

}