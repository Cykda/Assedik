#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "../include/SDL2/SDL.h"
#include "../include/plateau.h"

// Generals

#define BOARD_CENTERED 1


typedef struct Color Color;
struct Color
{
    int R;
    int G;
    int B;
    int A;
};




// rectangle

void drawRectangle(SDL_Renderer* renderer, SDL_Rect* rectangle, Color color, Color base);
position getRectCenter(SDL_Rect rectangle);

// Cercles

void DrawCircle(SDL_Renderer * renderer, int x, int y, int r, Color color, Color baseColor);


// plateau

void drawBoard(SDL_Renderer* renderer, SDL_Rect Baserect, plateau p, 
    Color c1, Color c2, Color base, short flag, SDL_Rect* BoardRect);


//utils

Color setColor(int R, int G, int B, int A);


#endif /*COMPONENTS_H*/