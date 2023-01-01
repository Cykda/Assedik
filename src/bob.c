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
int countPawns(plateau p, short color)
{
    int pawnsCount = 0;
    for(int i = 0; i < p.N; ++i)
    {
        for(int j = 0; j < p.N; ++j)
        {
            if(p.plateau[i][j].couleur == color)
            {
                pawnsCount++;
            }
        }
    }
    return pawnsCount;
}

int endGamePlacement(plateau *p, int X)
{

    
    int WhitePawnsNumber = X - countPawns(*p, WHITE);
    int RedPawnNumber = X - countPawns(*p, RED);
    position pos;
    while(true)
    {


        if(WhitePawnsNumber > 0)
        {
            pos = getRandomMove(*p);
            if(pos.x < 0 && pos.y < 0)
            {
                return 0;
            }
            directMove(p, WHITE, pos.x, pos.y);
        }

        if(RedPawnNumber > 0)
        {
                
            pos = getRandomMove(*p);
            if(pos.x < 0 && pos.y < 0)
            {
                return 0;
            }
            directMove(p, RED, pos.x, pos.y);

        }



        if(WhitePawnsNumber <= 0 && RedPawnNumber <= 0)
        {
            return 0;
        }
        else if(check_win(*p, X) == RED)
        {
            return 0;
        }
        else if(check_win(*p, X) == WHITE)
        {
            return 1;
        }
        
        
        WhitePawnsNumber--;
        RedPawnNumber--;



    }
    
    
    
}



position Monte_Carlo(plateau *p, int X, int interation, short phase)
{

    int maxScore = -INFINITY;
    int score = 0;
    int index = 0;
    
    position pos;
    
    if(PHASE_PLACEMENT)
    {

        
        plateau p2;
        initPlateau(&p2, p->N);
        copyBoard(*p, &p2);
        
        for(int i = 0; i < p->N; ++i)
        {
            for(int j = 0; j < p->N; ++j)
            {
                printf("AI : %.1f %%\n", (float)(100.f * ((float)index / ((float)p->N * (float)p->N))));
                if(p->plateau[i][j].couleur == NONE)
                {
                    directMove(&p2, RED, j, i);
                    score = 0;
                    for(int k = 0; k < interation; ++k)
                    {
                        score += endGamePlacement(&p2, X);
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
        printf("AI : %.1f %%\n", (float)(100.f * ((float)index / ((float)p->N * (float)p->N))));
        
        freeboard(&p2);
        
            
    }
    
    
    return pos;
    
    
}






