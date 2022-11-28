#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/plateau.h"
#include "../include/moves.h"
#include "../include/rules.h"
#include "../include/define.h"
#include "../include/bob.h"
#include "../include/ui.h"
#include "../include/SDL2/SDL.h"
#include "../include/components.h"


/*
int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Surface* window = NULL;
    SDL_Renderer* renderer = NULL;
    window = SDL_CreateWindow("Hello World !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    if(window == NULL)
    {
        printf("Error while creating window\n");
        return 1;
    }
    if(renderer == NULL)
    {
        printf("Error while creating renderer\n");
        return 1;
    }
    
    int N = 5;
    int X = 10;
    plateau p;
    initPlateau(&p, N);
    
    Color BaseColor = setColor(27, 163, 156, 255);
    pion pawn;
    pion pawn2;
    
    pawn.pos.x = 0;
    pawn.pos.y = 0;
    pawn.couleur = RED;
    
    pawn2.pos.x = 3;
    pawn2.pos.y = 4;
    pawn2.couleur = WHITE;
    
    move(&p, pawn);
    move(&p, pawn2);
    showBoard(p);

    
    SDL_Rect rect;
    rect.x = 10;
    rect.y = 10;
    rect.w = 100;
    rect.h = 100;
    
    SDL_Rect boardRect;

    GraphicalPawns* Wpawns = initGPawns(X, setPosition(0, 0), 50);
    GraphicalPawns* Rpawns = initGPawns(X, setPosition(0, 0), 50);

    bool launched = true;
    
    
    while(launched)
    {
        SDL_Event event;
        
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                launched = false;
                break;
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                printf("%d %d %d %d || %d\n", boardRect.x, boardRect.y, boardRect.w, boardRect.h, isMouseInBoard(boardRect, N));
            }
        }
        int color = 0;
        
        SDL_RenderClear(renderer);
        // R: 249 G: 232 B: 204
        // R: 210 G: 176 B: 151

        drawBoard(renderer, rect, p, setColor(249, 232, 204, 255)
            , setColor(210, 176, 151, 255), BaseColor, BOARD_CENTERED, &boardRect);
            
        
        drawPawns(renderer, Wpawns, X, BaseColor, setColor(255, 255, 255, 255), false);
        drawPawns(renderer, Rpawns, X, BaseColor, setColor(255, 0, 0, 255), true);
        
        
        SDL_RenderPresent(renderer);
    }
    
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    
    freeborad(&p);
    free(Wpawns);
    free(Rpawns);
    return 0;
}

*/




int main(int argc, char** argv)
{
    printf("\n");
    plateau p;
    pion pawn;

    int N; // taille de la grille
    int P;// Nombre de pions
    int X;// Nombre d'alignement nécéssaire
    int NBB,NBR; //Nombre de pions restants à placer
    int Phase; //Phase actuelle du jeu (1 ou 2)
    int *pNBB, *pNBR;//Pointeurs sur les variables NBB et NBR
    int tour;//Variable qui sait quel joueur doit jouer


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
    pNBB=&NBB;
    pNBR=&NBR;
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
            pawn = inputPawn("Joueur rouge, c'est a vous. Voullez-vous quitter le programme ? Si oui, tapez 1. Sinon, tapez 0 --> ",
                             "Choisissez la position (X, Y): ",tour);
        }
        if (tour==0)
        {
            pawn = inputPawn("Joueur blanc, c'est a vous. Voullez-vous quitter le programme ? Si oui, tapez 1. Sinon, tapez 0 --> ",
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

        /*if(pawn.info.couleur != 1 && pawn.info.couleur != 0 && pawn.info.couleur != -2)
        {
            printf("\nErreur de saisie de couleur\n");
            continue;
        }

        if(pawn.info.quantite <= 0)
        {
            printf("\nPlus de jetons %d Disponnibles (0 = Blanc ou 1 = Rouge)\n",pawn.info.couleur);
            continue;
        }*/


        move(&p,pawn,pNBB,pNBR);

        printf("\n\nnb rouge restant : %d\nnb blanc restant : %d \n\n",NBR,NBB);

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


    printf("\nFin du programme");
    freeborad(&p);
    return 0;
}
