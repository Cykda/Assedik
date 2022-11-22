#ifndef UI_H
#define UI_H
#include "../include/SDL2/SDL.h"
#include "../include/components.h"
#include "../include/plateau.h"


typedef struct GraphicalPawns GraphicalPawns;
struct GraphicalPawns
{
    SDL_Rect rectangle;
    position Boardpos;
    Color color;
};


GraphicalPawns* initGPawns(int X, position pos, int size);
void drawPawns(SDL_Renderer* renderer, GraphicalPawns* pawns, int N, Color BaseColor, Color color, bool inverse);


// Drag'n'Drop

bool isMouseInBoard(SDL_Rect caseRect, int N);



#endif //UI_H
