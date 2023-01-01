#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../include/plateau.h"
#include "../include/moves.h"
#include "../include/rules.h"
#include "../include/define.h"
#include "../include/bob.h"
#include "../include/ui.h"
#include "../include/SDL2/SDL.h"
#include "../include/components.h"
#include "../include/gamesave.h"




int main(int argc, char** argv)
{

    plateau p;
    pion pawn;

    int N; // taille de la grille
    int P;// Nombre de pions
    int X;// Nombre d'alignement nécéssaire
    int NBB,NBR; //Nombre de pions restants à placer
    int Phase; //Phase actuelle du jeu (1 ou 2)
    int tour;//Variable qui sait quel joueur doit jouer
    int reponse_RED,reponse_WHITE;//Variable qui vois si le joueur choisis de déplacer le pion ou d'utiliser le coup spécial


    do {
        printf("\nDonnez la taille souhaitee pour la grille (entier, minimim 3 cases) \n");
        scanf("%d",&N);
        fflush(stdin);
    }while (N<3);

    do {
        printf("\nDonnez le nombre de pions souhaites (plus petit que la taile du plateau) (entier) \n");
        scanf("%d",&P);
        fflush(stdin);
    } while (P>N || P<2);
    NBB=P;
    NBR=P;

    do {
        printf("\nDonnez le nombre de pions a alligner pour gagner (plus petit ou egal au nombre de pions par joueur) (entier) \n");
        scanf("%d",&X);
        fflush(stdin);
    } while (X>P);
    do {
        printf("\nDonnez le Joueur qui doit commencer (1: rouge ou 0: blanc)\n");
        scanf("%d",&tour);
        fflush(stdin);
    } while (tour!=1 && tour!=0);


    initPlateau(&p, N);
    showBoard(p);

    printf("\n");


    initPlateau(&p, N);
    showBoard(p);
    Phase=1;

    while(Phase==1)
    {
        if (tour==1)
        {
            pawn = inputPawn("Joueur rouge, c'est a vous. Voulez-vous quitter le programme ? Si oui, tapez 1. Sinon, tapez 0 --> ",
                             "Choisissez la position (X, Y): ",tour);
        }
        if (tour==0)
        {
            pawn = inputPawn("Joueur blanc, c'est a vous. Voulez-vous quitter le programme ? Si oui, tapez 1. Sinon, tapez 0 --> ",
                             "Choisissez la position (X, Y): ",tour);
        }

        if(pawn.info.couleur == -2)
        {
            break;
        }
        if(pawn.info.couleur == 1)
        {
            pawn.info.quantite=NBR;
        }
        if(pawn.info.couleur == 0)
        {
            pawn.info.quantite=NBB;
        }

        if(pawn.pos.x < 0 || pawn.pos.x > (N - 1) || pawn.pos.y < 0 || pawn.pos.y > (N - 1))
        {
            printf("\nposition non valide : en dehors du plateau\n");
            continue;
        }

        if(p.plateau[pawn.pos.y][pawn.pos.x].info.couleur!=-1)
        {
            printf("\nposition non valide : Case deja occupee par un autre pion\n");
            continue;
        }
        // BEGIN OF COMMENT
        if(pawn.info.couleur != 1 && pawn.info.couleur != 0 && pawn.info.couleur != -2)
        {
            printf("\nErreur de saisie de couleur\n");
            continue;
        }

        if(pawn.info.quantite <= 0)
        {
            printf("\nPlus de jetons %d Disponnibles (0 = Blanc ou 1 = Rouge)\n",pawn.info.couleur);
            continue;
        }
        // END OF COMMENT

        placement(&p,pawn, &NBB, &NBR);

        printf("\n\nnb rouge restant : %d\nnb blanc restant : %d \n\n", NBR, NBB);

        if (tour==1)
        {
            tour=0;
        }
        else if (tour==0)
        {
            tour=1;
        }

        int state = check_win(p, X);
        if(state == RED)
        {
            showBoard(p);
            printf("\nLe joueur rouge a gagne\n");
            break;
        }
        else if(state == WHITE)
        {
            showBoard(p);
            printf("\nLe joueur blanc a gagne\n");
            break;
        }

        printf("\n");
        showBoard(p);

        if (NBB<=0 && NBR<=0)
        {
            printf("\n\nFelicitation, tout les pions sont places. La phase 1 est donc terminee. Comme personne n'a gagné suite a cette phase, on peut passer a la phase 2\n\n");
            Phase=2;
        }
    }

    while(Phase==2)
    {
        printf("\n");
        showBoard(p);
        if (tour==1)
        {
            if (reponse_RED==2)
            {
                printf("\nJoueur rouge, vous devez replacer votre pion");
                coup_special(&p,tour,N);
                int state = check_win(p, X);
                if(state == RED)
                {
                    showBoard(p);
                    printf("\nLe joueur rouge a gagne\n");
                    break;
                }
                tour=0;
                reponse_RED=0;
                continue;
            }
        }
        else if (tour==0)
        {
            if (reponse_WHITE==2)
            {
                printf("\nJoueur blanc, vous devez replacer votre pion");
                coup_special(&p,tour,N);
                int state = check_win(p, X);
                if(state == WHITE)
                {
                    showBoard(p);
                    printf("\nLe joueur blanc a gagne\n");
                    break;
                }
                tour=1;
                reponse_WHITE=0;
                continue;
            }
        }
        if (tour==1)
        {
            do
            {
                pawn = inputPawn("\nJoueur rouge, c'est a vous. Voullez-vous quitter le programme ? Si oui, tapez 1. Sinon, tapez 0 --> ",
                              "\nChoisissez la position Du pion que vous souhaitez deplacer (X, Y): ",tour);
                if (p.plateau[pawn.pos.y][pawn.pos.x].info.couleur!=1)
                {
                    printf("\nERREUR, Cette case ne contient pas l'un de vos pions. ");
                }
            } while (p.plateau[pawn.pos.y][pawn.pos.x].info.couleur!=1);
        }
        if (tour==0)
            do
            {
                pawn = inputPawn("\nJoueur blanc, c'est a vous. Voullez-vous quitter le programme ? Si oui, tapez 1. Sinon, tapez 0 --> ",
                                 "\nChoisissez la position Du pion que vous souhaitez deplacer (X, Y): ",tour);
                if (p.plateau[pawn.pos.y][pawn.pos.x].info.couleur!=0)
                {
                    printf("\nERREUR, Cette case ne contient pas l'un de vos pions.\n");
                }
            } while (p.plateau[pawn.pos.y][pawn.pos.x].info.couleur!=0);
        if (tour==1)
        {
            reponse_RED=choix_deplacement(&p,pawn);
        }
        else if (tour==0)
        {
            reponse_WHITE=choix_deplacement(&p,pawn);
        }



        if (tour==1)
        {
            if (reponse_RED==1)
            {
                deplacement_pion(&p,pawn,tour,N);
            }
        }
        else if (tour==0)
        {
            if (reponse_WHITE==1)
            {
                deplacement_pion(&p,pawn,tour,N);
            }
        }
        int state = check_win(p, X);
        if(state == RED)
        {
            showBoard(p);
            printf("\nLe joueur rouge a gagne\n");
            break;
        }
        if(state == WHITE)
        {
            showBoard(p);
            printf("\nLe joueur blanc a gagne\n");
            break;
        }

        if (tour==1)
        {
            tour=0;
        }
        else if (tour==0)
        {
            tour=1;
        }
    }

    printf("\nFin du programme");
    freeboard(&p);
    return 0;
}


