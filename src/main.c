#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/plateau.h"
#include "../include/moves.h"
#include "../include/rules.h"
#include "../include/define.h"
#include "../include/bob.h"
#include "../include/SDL2/SDL.h"



int main(int argc, char** argv)
{
    int N = 10;
    plateau p;
    initPlateau(&p, N);


    showBoard(p);
    printf("\n\n");
    position pos;

    plateau p2;
    initPlateau(&p2, p.N);
    copyBoard(p, &p2);

    for(int i = 1; i < possibleMovesNumber(p) + 1; ++i)
    {
        pos = applyMove(&p2, i, (short)RED);
        if(!BoardEqu(p, p2))
        {
            showBoard(p2);
            directMove(&p2, NONE, pos.x, pos.y);
            printf("\n\n");
        }
        else
        {
            directMove(&p2, NONE, pos.x, pos.y);
        }
    }


    freeborad(&p2);
    freeborad(&p);
    return 0;
}




/*
int main(int argc, char** argv)
{
    printf("\n");
    plateau p;
    pion pawn;

    int N; // taille de la grille
    int P;// Nombre de pions
    int X;// Nombre d'alignement nécéssaire

    printf("\nDonnez la taille souhaitee pour a grille (entier) \n");
    scanf("%d",&N);
    fflush(stdin);
    do {
        printf("\nDonnez le nombre de pions souhaites (plus petit que la taile du plateau) (entier) \n");
        scanf("%d",&P);
        fflush(stdin);
    } while (P>N);
    do {
        printf("\nDonnez le nombre de pions a alligner pour gagner (plus petit ou egal au nombre de pions par joueur) (entier) \n");
        scanf("%d",&X);
        fflush(stdin);
    } while (X>P);

    initPlateau(&p, N);
    showBoard(p);

    printf("\n");


    int N = 10;
    int X = 5;


    initPlateau(&p, N);
    showBoard(p);





    while(true)
    {

        pawn = inputPawn("Choisissez la couleur (1: rouge, 0: blanc, -2: quitter le programme): ",
            "Choisissez la position (X, Y): ");


        if(pawn.couleur == -2)
        {
            break;
        }

        if(pawn.pos.x < 0 || pawn.pos.x > (N - 1) || pawn.pos.y < 0 || pawn.pos.y > (N - 1))
        {
            printf("position non valide\n");
            continue;
        }

        if(pawn.couleur != 1 && pawn.couleur != 0 && pawn.couleur != -2)
        {
            printf("Erreur de saisie de couleur\n");
            continue;
        }



        move(&p, pawn);

        int state = check_win(p, X);
        if(state == RED)
        {
            printf("\nLe joueur rouge a gagne\n");
            break;
        }
        else if(state == WHITE)
        {
            printf("\nLe joueur blanc a gagne\n");
            break;
        }

        printf("\n");
        showBoard(p);
    }


    printf("\nFin du programme");
    freeborad(&p);
    return 0;
}
*/