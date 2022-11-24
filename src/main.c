#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
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
    int X = 100;
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
    
    
    freeboard(&p);
    free(Wpawns);
    free(Rpawns);
    return 0;
}
*/



/*
int main(int argc, char** argv)
{
    printf("\n");
    plateau p;
    pion pawn;

    int N = 10; // taille de la grille
    //int P;// Nombre de pions
    int X = 3;// Nombre d'alignement nécéssaire
    
    /*
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


int main(int argc, char** argv)
{
    
    
    int N = 10;
    
    plateau p;
    initPlateau(&p, N);
    
    //showBoard(p);
    
    
    
    

    int inf = INFINITY;
    
    int result = explore(&p, 2, true);
    
    printf("\n\n");
    printf("Resultat: %d\n", result);
    printf("-inf: %d\n", -inf);
    printf("inf: %d\n", inf);
    
    
    freeboard(&p);
    return 0;
}
