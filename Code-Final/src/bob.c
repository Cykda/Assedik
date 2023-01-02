#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/bob.h"



void copyBoard(plateau p, plateau* p2) // Fonction pour dupliquer un plateau de jeu
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

position getRandomMove(plateau p) // Fonction pour avoir une position aléatoire du plateau
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
    } while (p.plateau[pos.y][pos.x].info.couleur != NONE);
    
    return pos;
    
}


bool checkBoardEmpty(plateau p) // Fonction qui regarde si le plateau a au moin une case de vide
{
    for(int i = 0; i < p.N; ++i)
    {
        for(int j = 0; j < p.N; ++j)
        {
            if(p.plateau[i][j].info.couleur == NONE)
            {
                return true;
            }
        }
    }
    
    return false;
    
}
int countPawns(plateau p, short color) // Fonction qui compte les pions d'une certaine couleur sur le plateau
{
    int pawnsCount = 0;
    for(int i = 0; i < p.N; ++i)
    {
        for(int j = 0; j < p.N; ++j)
        {
            if(p.plateau[i][j].info.couleur == color)
            {
                pawnsCount++;
            }
        }
    }
    return pawnsCount;
}

int endGamePlacement(plateau *p, int X) // fonction qui finis la phase de placement de jeu de manière aléatoire
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

position getRandomPawnPos(plateau p, short color, int X) // Fonction qui renvoie une poisition aléatoire d'un pion sur le plateau
{


    int ColorNumber = 0;
    for(int i = 0; i < p.N; ++i)
    {
        for(int j = 0; j < p.N; ++j)
        {
            if(p.plateau[i][j].info.couleur == color)
            {
                ColorNumber++;
            }
        }
    }

    
    position *BufferPosArray = malloc(sizeof(position) * ColorNumber);
    int index = 0;
    
    for(int i = 0; i < p.N; ++i)
    {
        for(int j = 0; j < p.N; ++j)
        {
            if(p.plateau[i][j].info.couleur == color)
            {
                BufferPosArray[index].x = j;
                BufferPosArray[index].y = i;
                index++;
            }
        }
    }    
    
    
    position RandomPos = BufferPosArray[rand() % index];
    free(BufferPosArray);
    
    return RandomPos;
    
    
    
    
    
}

position getRandomDisplacement(plateau p, position pawn) // Fonction qui revoire un déplacement aléatoire d'un pion
{
   
   
   
   
    position adjencyPos[8];
   
    for(int i = 0; i < 8; ++i)
    {
        adjencyPos[i].x = -1;
        adjencyPos[i].y = -1;
    }
    
    int adjencyIndex = 0;
    
    for(int k = pawn.y - 1; k < pawn.y + 2; ++k)
    {
        for(int l = pawn.x - 1; l < pawn.x + 2; ++l)
        {
            if(k == pawn.y && l == pawn.x)
            {
                continue;
            }
            
            if(0 <= k && k < p.N && 0 <= l && l < p.N)
            {

                adjencyPos[adjencyIndex].x = l;
                adjencyPos[adjencyIndex].y = k;
                adjencyIndex++;
            }
        }
    }
   
    adjencyIndex = 0;
    int PossibiltyIndex = 0;
    do
    {
        PossibiltyIndex++;
        adjencyIndex = rand() % 8;
        if(adjencyPos[adjencyIndex].x != -1 && adjencyPos[adjencyIndex].y != -1)
        {
            if(p.plateau[adjencyPos[adjencyIndex].y][adjencyPos[adjencyIndex].x].info.couleur == NONE)
            {
                break;
            }
        }

        if(PossibiltyIndex >= 8)
        {
            adjencyPos[0].x = -1;
            adjencyPos[0].y = -1;
            return adjencyPos[0];
        }

    } while (true);
    
    
    
    return adjencyPos[adjencyIndex];
    
}

position* getDisplacementPossibilities(plateau p, position pos) // Fonction qui revoie toutes les possiblilités de déplacement sur le plateau
{
    position* adjencyPos = malloc(sizeof(position) * 8);
    for(int i = 0; i < 8; ++i)
    {
        adjencyPos[i] = (position){-1, -1};
    }

    int adjencyIndex = 0;
    
    for(int k = pos.y - 1; k < pos.y + 2; ++k)
    {
        for(int l = pos.x - 1; l < pos.x + 2; ++l)
        {
            if(k == pos.y && l == pos.x)
            {
                continue;
            }
            
            if(0 <= k && k < p.N && 0 <= l && l < p.N)
            {

                adjencyPos[adjencyIndex].x = l;
                adjencyPos[adjencyIndex].y = k;
                adjencyIndex++;
            }
        }
    }
    
    return adjencyPos;
    
    
    
}



int endGameDisplacement(plateau* p, int X) // Fonction qui termine la phase de déplacement de façon aléatoire
{
    
    position randomPosW;
    position randomDisplacementW;
    
    
    position randomPosR;
    position randomDisplacementR;
    long SecurityIndex = 0;
    while(true)
    {
        
        bool canMove = true;
        
        do
        {
            randomPosW = getRandomPawnPos(*p, RED, X);
            randomDisplacementW = getRandomDisplacement(*p, setPosition(randomPosW.x, randomPosW.y));
            
            position* diffPos = getDisplacementPossibilities(*p, randomPosR);
            canMove = true;
            for(int i = 0; i < 8; ++i)
            {
                //printf("%d %d\n", diffPos[i].x, diffPos[i].y);
                if(diffPos[i].x != -1 && diffPos[i].y != -1)
                {
                    canMove = false;
                    break;
                }
            }
            
            if(!canMove)
            {
                return 0;
            }
            free(diffPos);
            //printf("1\n");
        } while (randomDisplacementW.x == -1 && randomDisplacementW.y == -1);



        directMove(p, NONE, randomPosW.x, randomPosW.y);
        directMove(p, RED, randomDisplacementW.x, randomDisplacementW.y);


        
        do
        {
            randomPosR = getRandomPawnPos(*p, WHITE, X);
            position* diffPos = getDisplacementPossibilities(*p, randomPosR);
            
            
            canMove = true;
            for(int i = 0; i < 8; ++i)
            {
                //printf("%d %d\n", diffPos[i].x, diffPos[i].y);
                if(diffPos[i].x != -1 && diffPos[i].y != -1)
                {
                    canMove = false;
                    break;
                }
            }
            
            if(!canMove)
            {
                return 0;
            }
            
            free(diffPos);
            
            //printf("2\n");
            randomDisplacementR = getRandomDisplacement(*p, setPosition(randomPosR.x, randomPosR.y));
            
        } while (randomDisplacementR.x == -1 && randomDisplacementR.y == -1);
        

        

        directMove(p, NONE, randomPosR.x, randomPosR.y);
        directMove(p, WHITE, randomDisplacementR.x, randomDisplacementR.y);


        if(SecurityIndex >= MAX_DISPLACEMENT_ITERATION)
        {
            printf("Security index triggerd\n");
            return 0;
        }
        if(check_win(*p, X) == RED)
        {
            return 0;
        }
        else if(check_win(*p, X) == WHITE)
        {
            return 1;
        }
        
        SecurityIndex++;
    }
    
    
    
    
}



MonteCarlo Monte_Carlo(plateau *p, int X, int interation, short phase) // Fonction qui joue le coup de l'IA pour les deux phases
{

    int maxScore = -__INT_MAX__;
    int score = 0;
    int index = 0;
    
    position pos;
    
    MonteCarlo result;
    
    if(phase == PHASE_PLACEMENT)
    {

        result.state = PHASE_PLACEMENT;
        plateau p2;
        initPlateau(&p2, p->N);
        copyBoard(*p, &p2);
        
        for(int i = 0; i < p->N; ++i)
        {
            for(int j = 0; j < p->N; ++j)
            {
                printf("AI : %.1f %%\n", (float)(100.f * ((float)index / ((float)p->N * (float)p->N))));
                if(p->plateau[i][j].info.couleur == NONE)
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
                        result.pos_to_move = (position){j, i};
                    }
                    directMove(&p2, NONE, j, i);       
                }
                index++;
            }
        }
        printf("AI : %.1f %%\n", (float)(100.f * ((float)index / ((float)p->N * (float)p->N))));
        
        freeboard(&p2);
        
        return result;
            
    }
    else if(phase == PHASE_DEPLACEMENT)
    {
        
        result.state == PHASE_DEPLACEMENT;
        
        
        plateau p2;
        initPlateau(&p2, p->N);
        copyBoard(*p, &p2);
        
        position bestDisplacement;
        position bestPos;
        int index = 0;
        for(int i = 0; i < p->N; ++i)
        {
            for(int j = 0; j < p->N; ++j)
            {
                
                if(p->plateau[i][j].info.couleur == RED)
                {
                    position *BufferPos = getDisplacementPossibilities(p2, (position){j, i});
                    for(int k = 0; k < 8; ++k)
                    {
                        
                        
                        if(BufferPos[k].x != -1 && BufferPos[k].y != -1)
                        {
                            
                            if(p->plateau[BufferPos[k].y][BufferPos[k].x].info.couleur == NONE)
                            {
                                
                                directMove(&p2, RED, BufferPos[k].x, BufferPos[k].y);
                            
                                
                                score = 0;
                                for(int l = 0; l < interation; ++l)
                                {
                                    score += endGameDisplacement(&p2, X);
                                    copyBoard(*p, &p2);
                                }

                                if(score > maxScore)
                                {
                                    
                                    bestPos = (position){j, i};
                                    bestDisplacement = (position){BufferPos[k].x, BufferPos[k].y};
                                    maxScore = score;
                                }
                                
                                
                                directMove(&p2, NONE, BufferPos[k].x, BufferPos[k].y);
                                index++;
                            }
                        }
                    }
                    free(BufferPos);
                    
                }
                
            }
        }
        
        
        
        freeboard(&p2);
        result.displacementPos = bestDisplacement;
        result.pos_to_move = bestPos;
        return result;
        
    }
    
    
    
    
}
