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



int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Surface* window = NULL;
    SDL_Renderer* renderer = NULL;
    window = SDL_CreateWindow("Hello World !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 480, 0);
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
    
    
    

    SDL_Rect rect;
    rect.x = 10;
    rect.y = 10;
    rect.w = 100;
    rect.h = 100;
    
    SDL_Rect rect2;
    rect2.x = 200;
    rect2.y = 200;
    rect2.w = 100;
    rect2.h = 100;

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
        }
        
        SDL_RenderClear(renderer);
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &rect2);
        SDL_RenderFillRect(renderer, &rect2);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        
        SDL_RenderPresent(renderer);
    }
    
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}



/*
int main(int argc, char** argv)
{
    printf("\n");
    plateau p;
    pion pawn;

    int N = 10; // taille de la grille
    //int P;// Nombre de pions
    int X = 3;// Nombre d'alignement nécéssaire


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