#include <stdio.h>
#include <stdlib.h>
#include "../include/ui.h"




GraphicalPawns* initGPawns(int X, position pos, int size)
{
    
    GraphicalPawns* pawns = malloc(sizeof(GraphicalPawns) * X);
    
    if(pawns == NULL)
    {
        fprintf(stderr, "ERROR while allocating dynamix G-pawns array");
    }
    
    SDL_Rect rect;
    rect.x = pos.x + size;
    rect.y = pos.y + size;
    rect.w = size;
    rect.h = size;
    
    for(int i = 0; i < X; ++i)
    {
        pawns[i].Boardpos = setPosition(0, 0);
        pawns[i].color = setColor(0, 0, 0, 255);
        pawns[i].rectangle = rect;
    }
    
    
    return pawns;
    
}



void drawPawns(SDL_Renderer* renderer, GraphicalPawns* pawns, int N, Color BaseColor, Color color, bool inverse)
{
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);

    SDL_Rect rect;
    if(inverse)
    {
        rect.x = pawns[0].rectangle.x - (pawns[0].rectangle.w * 2) + w;
    }
    else
    {
        rect.x = pawns[0].rectangle.x;
    }
    rect.y = pawns[0].rectangle.y; 
    rect.w = pawns[0].rectangle.w;
    rect.h = pawns[0].rectangle.h;
    

    for(int i = 0; i < N; ++i)
    {
        DrawCircle(renderer, rect.x, rect.y, rect.h, color, BaseColor);

            
        rect.y += rect.h * 2;
        if(rect.y + rect.h >= h)
        {
            if(inverse)
            {
                rect.x -= rect.w * 2;
            }
            else
            {
                rect.x += rect.w * 2;
            }
            rect.y = pawns->rectangle.x;
        }
    }
    
    
    
}

bool isMouseInBoard(SDL_Rect caseRect, int N)
{
    SDL_PumpEvents();
    int x, y;
    SDL_GetMouseState(&x, &y);
    
    int BoardLength = caseRect.w * N;
    int BoardHeight = caseRect.h * N;
    
    if(x > caseRect.x && x < caseRect.x + BoardLength && y > caseRect.y && y < caseRect.y + caseRect.h)
    {
        return true;
    }
    
    return false;
    
    
   
 
}