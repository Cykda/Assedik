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
#include "../include/SDL2/SDL_ttf.h"


int main(int argc, char** argv)
{
    /* mise en place de la SDL et du TTF */

    SDL_Surface* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);

    // Creation fenetre et rendu
    window = SDL_CreateWindow("Teeko", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 780, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    TTF_Init();
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");

    // Chargement de la police
    TTF_Font* Sans = TTF_OpenFont("assets\\Inconsolata\\Inconsolata-VariableFont_wdth,wght.ttf", 12);

    // Texte en gras
    TTF_SetFontStyle(Sans, TTF_STYLE_BOLD);

    if (Sans == NULL){
        printf("Error while importing typeface \n");
        return 4;
    }

    // Verifications du fonctionnement
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

    SDL_Color Black = {0, 0, 0, 0};
    Color BaseColor = setColor(46, 83, 76, 255); // couleur du background

    /* Variables de base */
    plateau p;
    pion pawn;
    int N; // taille de la grille
    int P;// Nombre de pions
    int X;// Nombre d'alignement nécéssaire
    int NBB,NBR; //Nombre de pions restants à placer
    int Phase; //Phase actuelle du jeu (1 ou 2)
    int *pNBB, *pNBR;//Pointeurs sur les variables NBB et NBR
    int tour;//Variable qui sait quel joueur doit jouer
    int reponse_RED,reponse_WHITE;//Variable qui voit si le joueur choisit de déplacer le pion ou d'utiliser le coup spécial

    /* début du programme sans interface graphique */
    do {
        printf("\nTaille de la grille souhaitee (entier, minimim 3 cases): \n");
        scanf("%d",&N);
        fflush(stdin);
    }while (N<3);

    do {
        printf("\nNombre de pions souhaites (entier, plus petit que la taille du plateau): \n");
        scanf("%d",&P);
        fflush(stdin);
    } while (P>N || P<2);
    NBB=P;
    NBR=P;
    pNBB=&NBB;
    pNBR=&NBR;
    do {
        printf("\nNombre de pions a aligner pour gagner (entier, inferieur ou egal au nombre de pions par joueur) \n");
        scanf("%d",&X);
        fflush(stdin);
    } while (X>P);
    do {
        printf("\nJoueur qui doit commencer (1: rouge ou 0: blanc): \n");
        scanf("%d",&tour);
        fflush(stdin);
    } while (tour!=1 && tour!=0);


    // creation de la surface des textes
    SDL_Surface* surface_nb_pions1 = TTF_RenderText_Blended(Sans, "10", Black);
    SDL_Surface* surface_nb_pions2 = TTF_RenderText_Blended(Sans, "10", Black);
    SDL_Surface* surface_sauv= TTF_RenderText_Blended(Sans, "| sauvegarder",Black );
    SDL_Surface* surface_part= TTF_RenderText_Blended(Sans, "reprendre la partie precedente",Black );

    // conversion en texture
    SDL_Texture* nb_pawnsW = SDL_CreateTextureFromSurface(renderer, surface_nb_pions1);
    SDL_Texture* nb_pawnsR = SDL_CreateTextureFromSurface(renderer, surface_nb_pions2);
    SDL_Texture* sauv = SDL_CreateTextureFromSurface(renderer, surface_sauv);
    SDL_Texture* previous = SDL_CreateTextureFromSurface(renderer, surface_part);

    initPlateau(&p, N);

    SDL_Rect rect;
    rect.x = 10;
    rect.y = 10;
    rect.w = 100;
    rect.h = 100;
    
    SDL_Rect boardRect;

    GraphicalPawns* Wpawns = initGPawns(X, setPosition(0, 0), 50);
    GraphicalPawns* Rpawns = initGPawns(X, setPosition(0, 1), 50);

    SDL_bool launched = SDL_TRUE;

    Phase = 1;

    while(launched)
    {
        SDL_Event event;
        
        while(SDL_PollEvent(&event))
        {
            switch(event.type) {
                case SDL_MOUSEBUTTONDOWN:

                    if (event.button.button == SDL_BUTTON_LEFT) {

                        //SDL_RenderClear(renderer);

                        int w, h;
                        SDL_GetRendererOutputSize(renderer, &w, &h);

                        int x = event.button.x, y = event.button.y;
                        while (Phase == 1) {
                            if (tour == 1) // tour du joueur rouge
                            {
                                //DrawCircle(renderer, 3 * w / 4 + 50, h / 2, 60, setColor(199, 207, 0, 255), BaseColor);

                                //if (isMouseInBoard(boardRect, N)) {
                                printf("case du j r");
                                pion pawn;
                                pawn.pos.x = ((x - w / 2)/N)-((x - w / 2)%N);
                                printf("\n%i\n",pawn.pos.x);
                                pawn.pos.y = (y - h / 2)/N;
                                pawn.info.couleur = tour;
                               // }
                                break;
                            }
                            if (tour == 0) { // tour du joueur blanc
                                DrawCircle(renderer, w / 4 - 50, h / 2, 60, setColor(199, 207, 0, 255), BaseColor);

                                if (isMouseInBoard(boardRect, N)) {
                                    printf("case du j blanc");
                                    pion pawn;
                                    pawn.pos.x = x - w / 2;
                                    pawn.pos.y = y - h / 2;
                                    pawn.info.couleur = tour;
                                    printf("case du j blanc\n\n");
                                }
                                break;
                            }

                            if (pawn.info.couleur == 1) {
                                pawn.info.quantite = NBR;
                            }
                            if (pawn.info.couleur == 0) {
                                pawn.info.quantite = NBB;
                            }


                            if (p.plateau[pawn.pos.y][pawn.pos.x].info.couleur != -1) {
                                printf("\nposition non valide : Case deja occupee par un autre pion\n");
                                continue;
                            }

                            placement(&p, pawn, pNBB, pNBR);

                            if (tour == 1) {
                                tour = 0;
                                break;
                            } else if (tour == 0) {
                                tour = 1;
                                break;
                            }

                            int state = check_win(p, X);
                            if (state == RED) {
                                showBoard(p);
                                printf("\nLe joueur rouge a gagne\n");
                                break;
                            } else if (state == WHITE) {
                                showBoard(p);
                                printf("\nLe joueur blanc a gagne\n");
                                break;
                            }

                            printf("\n");

                            if (NBB <= 0 && NBR <= 0) {
                                printf("\n\nFelicitation, tout les pions sont places. La phase 1 est donc terminee. Comme personne n'a gagné suite a cette phase, on peut passer a la phase 2\n\n");
                                Phase = 2;
                            }


                        }

                    }
                    break;

                case SDL_QUIT:
                    launched = SDL_FALSE;
                    break;

                default:
                    break;

            }

        }
        
        SDL_RenderClear(renderer);
        /*
        // R: 249 G: 232 B: 204
        // R: 210 G: 176 B: 151
       
       
        */
        drawBoard(renderer, rect, p, setColor(249, 232, 204, 255)
            , setColor(210, 176, 151, 255), BaseColor, BOARD_CENTERED, &boardRect);

        int w, h;
        SDL_GetRendererOutputSize(renderer, &w, &h);

        // emplacement texte

        SDL_Rect Pawns1_rect;
        Pawns1_rect.x = w/4 - 70;
        Pawns1_rect.y = h/2 - 25;
        Pawns1_rect.w = 40;
        Pawns1_rect.h = 48;

        SDL_Rect Pawns2_rect;
        Pawns2_rect.x = (3*w)/4 +30;
        Pawns2_rect.y = h/2 - 25;
        Pawns2_rect.w = 40;
        Pawns2_rect.h = 48;

        SDL_Rect Sauv_rect;
        Sauv_rect.x = w/2+3;
        Sauv_rect.y = h-50;
        Sauv_rect.w = 126;
        Sauv_rect.h = 40;

        SDL_Rect Previous_rect;
        Previous_rect.x = w/2-291;
        Previous_rect.y = h-50;
        Previous_rect.w = 290;
        Previous_rect.h = 40;

        // Dessin des cercles qui constituent la pioche

        DrawCircle(renderer, w/4 -50, h/2, 50,setColor(255, 255, 255, 255), BaseColor);
        DrawCircle(renderer, (3*w)/4 +50, h/2, 50,setColor(255, 0, 0, 255), BaseColor);


        SDL_RenderCopy(renderer, nb_pawnsR, NULL, &Pawns1_rect);
        SDL_RenderCopy(renderer, nb_pawnsW, NULL, &Pawns2_rect);
        SDL_RenderCopy(renderer, sauv, NULL, &Sauv_rect);
        SDL_RenderCopy(renderer, previous, NULL, &Previous_rect);
        SDL_RenderPresent(renderer);
    }

    SDL_FreeSurface(surface_nb_pions1);
    SDL_FreeSurface(surface_nb_pions2);
    SDL_FreeSurface(surface_part);
    SDL_FreeSurface(surface_sauv);
    SDL_DestroyTexture(nb_pawnsR);
    SDL_DestroyTexture(nb_pawnsW);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    
    freeborad(&p);
    free(Wpawns);
    free(Rpawns);
    return EXIT_SUCCESS;
}
