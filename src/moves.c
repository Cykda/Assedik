#include <stdlib.h>
#include <stdio.h>
#include "../include/moves.h"



void placement(plateau* p, pion pawn,int *pNBB, int *pNBR)
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

int choix_deplacement(plateau* p, pion pawn)
{
    int choix;
    do
    {
        printf("Vous avez le choix entre deplacer ce pion (1) ou effectuer le coup special (2). Faites votre choix: ");
        scanf("%d",&choix);
        fflush(stdin);
    } while(choix!=1 && choix!=2);
    if (choix==1)
    {
        printf("\nVous avez choisi de deplacer le pion.\n");
        return 1;
    }
    if (choix==2)
    {
        printf("\nVous  avez choisis d'utiliser le coup special. Votre pion est retiré du plateau, vous pourrez le replacer au prochain tour");
        p->plateau[pawn.pos.y][pawn.pos.x].info.couleur=NONE;
        return 2;
    }
}

int coup_special(plateau* p,int tour,int N)
{
    int x,y;
    while(true)
    {
        printf("\nDonnez les coordonnees souhaitees pour placer le pion retire (X,Y)");
        scanf("%d %d",&x,&y);
        fflush(stdin);
        if (y<0 || x<0 || y>(N-1) || x>(N-1))
        {
            printf("\nLa case ne convient pas : hors du plateau\n");
            continue;
        }
        else if (y>=0 && x>=0 && y<=(N-1) && x<=(N-1))
        {
            if (p->plateau[y][x].info.couleur!=NONE)
            {
                printf("\nLa case ne convient pas : case deja ocupee\n");
                continue;
            }
            else if (p->plateau[y][x].info.couleur==NONE)
            {
                if (tour==1)
                {
                    p->plateau[y][x].info.couleur=RED;
                    return 0;
                }
                else if (tour==0)
                {
                    p->plateau[y][x].info.couleur=WHITE;
                    return 0;
                }
            }
        }
    }
}

int deplacement_pion(plateau* p,pion pawn,int tour,int N)
{
    int x,y;
    while (true)
    {
        printf("\nDonnez les coordonnees ou vous voulez deplacer le pion (X,Y): ");
        scanf("%d %d",&x,&y);
        fflush(stdin);
        if (y<0 || x<0 || y>(N-1) || x>(N-1))
        {
            printf("\nLa case ne convient pas : hors du plateau\n");
            continue;
        }
        else if (x>(pawn.pos.x)+1 || x<(pawn.pos.x)-1 || y>(pawn.pos.y)+1 || y<(pawn.pos.y)-1)
        {
            printf("\nERREUR: La case n'est pas adjacente a celle du pion\n");
            continue;
        }
        else if (x<=(pawn.pos.x)+1 && x>=(pawn.pos.x)-1 && y<=(pawn.pos.y)+1 && y>=(pawn.pos.y)-1)
        {
            if (p->plateau[y][x].info.couleur==WHITE)
            {
                printf("\nERREUR, la case est deja occupee par un pion blanc\n");
            }
            else if (p->plateau[y][x].info.couleur==RED)
            {
                printf("\nERREUR, la case est deja occupee par un pion rouge\n");
            }
            else if (p->plateau[y][x].info.couleur==NONE)
            {
                printf("\nBravo, la case convient parfaitement !\n");
                if (tour==1)
                {
                    p->plateau[y][x].info.couleur=RED;
                    p->plateau[pawn.pos.y][pawn.pos.x].info.couleur=NONE;
                    return 0;
                }
                else if (tour==0)
                {
                    p->plateau[y][x].info.couleur=WHITE;
                    p->plateau[pawn.pos.y][pawn.pos.x].info.couleur=NONE;
                    return 0;
                }
            }
        }
    }
}
