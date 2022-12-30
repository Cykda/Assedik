#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

position getRandomMove(plateau p)
{
    
    position pos;

    if(!checkBoardEmpty(p))
    {
        pos.x = -1;
        pos.y = -1;
        return pos;
    }

    
    do
    {
        pos.x = rand() % p.N;
        pos.y = rand() % p.N;      
    } while (p.plateau[pos.y][pos.x].couleur != NONE);
    
    return pos;
    
}


bool checkBoardEmpty(plateau p)
{
    for(int i = 0; i < p.N; ++i)
    {
        for(int j = 0; j < p.N; ++j)
        {
            if(p.plateau[i][j].couleur == NONE)
            {
                return true;
            }
        }
    }
    
    return false;
    
}


int endGame(plateau *p, int X, int CurrentPawnNumber)
{

    int PawnNumber = CurrentPawnNumber;
    long SecurityIndex = 0;
    while(true)
    {


        
        position pos = getRandomMove(*p);
        if(pos.x < 0 && pos.y < 0)
        {
            return 0;
        }

        directMove(p, WHITE, pos.x, pos.y);
        
        pos = getRandomMove(*p);
        if(pos.x < 0 && pos.y < 0)
        {
            return 0;
        }


        directMove(p, RED, pos.x, pos.y);

        if(check_win(*p, X) == RED || PawnNumber <= 0)
        {
            return 0;
        }
        else if(check_win(*p, X) == WHITE)
        {
            return 1;
        }
        
        //printf("SecurityIndex: %d\n", SecurityIndex);
        
        PawnNumber--;
        SecurityIndex++;


    }
    
    
    
}



position Monte_Carlo(plateau *p, int X, int CurrentPawnNumber, int interation)
{
    
    int maxScore = -INFINITY;
    int score = 0;
    int index = 0;
    
    position pos;
    
    
    plateau p2;
    initPlateau(&p2, p->N);
    copyBoard(*p, &p2);
    
    for(int i = 0; i < p->N; ++i)
    {
        for(int j = 0; j < p->N; ++j)
        {
            printf("AI %%: %f\n", (float)(100.f * ((float)index / ((float)p->N * (float)p->N))));
            if(p->plateau[i][j].couleur == NONE)
            {
                directMove(&p2, RED, j, i);
                score = 0;
                for(int k = 0; k < interation; ++k)
                {
                    score += endGame(&p2, X, CurrentPawnNumber);
                    copyBoard(*p, &p2);
                }
                
                if(score > maxScore)
                {
                    maxScore = score;
                    pos.x = j;
                    pos.y = i;
                }
                directMove(&p2, NONE, j, i);       
            }
            index++;
        }
    }
    printf("AI %%: %f\n", (float)(100.f * ((float)index / ((float)p->N * (float)p->N))));
    
    freeboard(&p2);
    
        
    return pos;
    
    
}






