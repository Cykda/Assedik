#include <stdio.h>
#include <stdlib.h>
#include "../include/rules.h"


int check_win(plateau p, int X)
{

    // lignes
    int RedSum = 0;
    int WhiteSum = 0;

    for(int i = 0; i < p.N; ++i)
    {
        for(int j = 0; j < p.N; ++j)
        {
            if(p.plateau[i][j].couleur == RED)
            {
                RedSum++;
                WhiteSum=0;
                if(RedSum >= X)
                {
                    return RED;
                }
            }
            else if(p.plateau[i][j].couleur == WHITE)
            {
                WhiteSum++;
                RedSum=0;
                if(WhiteSum >= X)
                {
                    return WHITE;
                }
            }
            else if (p.plateau[i][j].couleur == NONE)
            {
                RedSum=0;
                WhiteSum=0;
            }
        }
        WhiteSum = 0;
        RedSum = 0;


    }


    WhiteSum = 0;
    RedSum = 0;


    // colones
    for(int i = 0; i < p.N; ++i)
    {
        for(int j = 0; j < p.N; ++j)
        {
            if(p.plateau[j][i].couleur == RED)
            {
                RedSum++;
                WhiteSum=0;
                if(RedSum >= X)
                {
                    return RED;
                }
            }
            else if(p.plateau[j][i].couleur == WHITE)
            {
                WhiteSum++;
                RedSum=0;
                if(WhiteSum >= X)
                {
                    return WHITE;
                }
            }
            else if (p.plateau[j][i].couleur == NONE)
            {
                RedSum=0;
                WhiteSum=0;
            }
        }


        if(RedSum >= X)
        {
            return RED;
        }
        else if(WhiteSum >= X)
        {
            return WHITE;
        }
        WhiteSum = 0;
        RedSum = 0;
    }
    // diagonales haut gache bas droit







    return NONE;
}
