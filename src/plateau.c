#include <stdlib.h>
#include <stdio.h>
#include "../include/plateau.h"




int initPlateau(plateau* p, int N)
{
    p->plateau = malloc(sizeof(pion *) * N);

    if(p->plateau == NULL)
    {
        fprintf(stderr, "Out of memory\n");
        return 1;
    }

    for(int i = 0; i < N; ++i)
    {
        p->plateau[i] = malloc(sizeof(pion) * N);
        if(p->plateau[i] == NULL)
        {
            fprintf(stderr, "Out of memory\n");
            return 1;
        }
    }


    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            p->plateau[i][j].couleur = NONE;
            p->plateau[i][j].pos.x = j;
            p->plateau[i][j].pos.y = i;


        }
    }
    p->N = N;


    return 0;



}


void freeborad(plateau* p)
{
    for(int i = 0; i < p->N; ++i)
    {
        free(p->plateau[i]);
    }
    free(p->plateau);
}


void showBoard(plateau p)
{
    printf("     ");
    for(int i = 0; i < p.N; ++i)
    {
        printf("  %d ", i);
    }

    printf("\n\n");


    for(int i = 0; i < p.N; ++i)
    {
        for(int j = 0; j < p.N; ++j)
        {
            if(j == 0)
            {
                printf("%d    ", i);
            }

            if(p.plateau[i][j].couleur == 1)
            {
                printf("| R ");
            }
            else if(p.plateau[i][j].couleur == 0)
            {
                printf("| B ");
            }
            else
            {
                printf("| O ");
            }
        }
        printf("|\n\n");
    }
}

bool BoardEqu(plateau p1, plateau p2)
{
    if(p1.N != p2.N)
    {
        fprintf(stderr, "Boards does not match size\n");
        return false;
    }


    for(int i = 0; i < p1.N; ++i)
    {
        for(int j = 0; j < p1.N; ++j)
        {
            if(p1.plateau[i][j].couleur != p2.plateau[i][j].couleur)
            {
                return false;
            }
        }
    }
    return true;

}


position setPosition(int x,  int y)
{
    position p;
    
    p.x = x;
    p.y = y;
    
    return p;
}