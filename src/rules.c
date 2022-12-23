#include <stdio.h>
#include <stdlib.h>
#include "../include/rules.h"


int check_win(plateau p, int X)
{

    // lignes
    int RedSum = 0;
    int WhiteSum = 0;
    int Diago=0;

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
    for(int i = 0; i < p.N; ++i) {
        for (int j = 0; j < p.N; ++j) {
            if (p.plateau[j][i].couleur == RED) {
                RedSum++;
                WhiteSum = 0;
                if (RedSum >= X) {
                    return RED;
                }
            } else if (p.plateau[j][i].couleur == WHITE) {
                WhiteSum++;
                RedSum = 0;
                if (WhiteSum >= X) {
                    return WHITE;
                }
            } else if (p.plateau[j][i].couleur == NONE) {
                RedSum = 0;
                WhiteSum = 0;
            }
        }
    }

    RedSum=0;
    WhiteSum=0;

    // diagonales haut gache bas droite
    for(int i = 0; i < p.N; ++i) {
        for (int j = 0; j < p.N; ++j) {
            int I=i,J=j;
            //Rouge
            if (p.plateau[i][j].couleur == RED) {
                I=i;
                J=j;
                RedSum++;
                while (Diago == 0) {
                    if (I+1 > p.N-1 || J+1 > p.N-1){
                        RedSum=0;
                        break;
                    } else{
                        I++;
                        J++;
                    }
                    if (p.plateau[I][J].couleur == RED) {
                        RedSum++;
                        if (RedSum >= X) {
                            return RED;
                        }
                    }
                    if (p.plateau[I][J].couleur == WHITE) {
                        RedSum = 0;
                        Diago = 1;
                    }
                    if (p.plateau[I][J].couleur == NONE) {
                        RedSum = 0;
                        Diago = 1;
                    }
                }
            }
            Diago = 0;
            //Blanc
            if (p.plateau[i][j].couleur == WHITE) {
                I=i;
                J=j;
                WhiteSum++;
                while (Diago == 0) {
                    if (I+1 > p.N-1 || J+1 > p.N-1){
                        WhiteSum=0;
                        break;
                    } else{
                        I++;
                        J++;
                    }
                    if (p.plateau[I][J].couleur == WHITE) {
                        WhiteSum++;
                        if (WhiteSum >= X) {
                            return WHITE;
                        }
                    }

                    if (p.plateau[I][J].couleur == RED) {
                        WhiteSum = 0;
                        Diago = 1;
                    }
                    if (p.plateau[I][J].couleur == NONE) {
                        WhiteSum = 0;
                        Diago = 1;
                    }
                }
            }
            Diago = 0;
        }
    }

    WhiteSum=0;
    RedSum=0;

    // diagonales bas gauche haut droite
    for(int i = 0; i < p.N; ++i) {
        for (int j = 0; j < p.N; ++j) {
            int I=i,J=j;
            //Rouge
            if (p.plateau[i][j].couleur == RED) {
                I=i;
                J=j;
                RedSum++;
                while (Diago == 0) {
                    if (I+1 > p.N-1 || J-1 > p.N-1){
                        RedSum=0;
                        break;
                    } else{
                        I++;
                        J--;
                    }
                    if (p.plateau[I][J].couleur == RED) {
                        RedSum++;
                        if (RedSum >= X) {
                            return RED;
                        }
                    }
                    if (p.plateau[I][J].couleur == WHITE) {
                        RedSum = 0;
                        Diago = 1;
                    }
                    if (p.plateau[I][J].couleur == NONE) {
                        RedSum = 0;
                        Diago = 1;
                    }
                }
            }
            Diago = 0;
            //Blanc
            if (p.plateau[i][j].couleur == WHITE) {
                I=i;
                J=j;
                WhiteSum++;
                while (Diago == 0) {
                    if (I+1 > p.N-1 || J-1 > p.N-1){
                        WhiteSum=0;
                        break;
                    } else{
                        I++;
                        J--;
                    }
                    if (p.plateau[I][J].couleur == WHITE) {
                        WhiteSum++;
                        if (WhiteSum >= X) {
                            return WHITE;
                        }
                    }

                    if (p.plateau[I][J].couleur == RED) {
                        WhiteSum = 0;
                        Diago = 1;
                    }
                    if (p.plateau[I][J].couleur == NONE) {
                        WhiteSum = 0;
                        Diago = 1;
                    }
                }
            }
            Diago = 0;
        }
    }

    WhiteSum=0;
    RedSum=0;

    return NONE;
}