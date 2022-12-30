#include "../include/components.h"


Color setColor(int R, int G, int B, int A)
{
    Color c;
    c.R = R;
    c.G = G;
    c.B = B;
    c.A = A;
    
    return c;
}

// Rectangle
void drawRectangle(SDL_Renderer* renderer, SDL_Rect* rectangle, Color color, Color base)
{
    SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);
    SDL_RenderDrawRect(renderer, rectangle);
    SDL_RenderFillRect(renderer, rectangle);
    SDL_SetRenderDrawColor(renderer, base.R, base.G, base.B, base.A);
}

position getRectCenter(SDL_Rect rectangle)
{
    position pos;
    pos.x = rectangle.x + (rectangle.w / 2);
    pos.y = rectangle.y + (rectangle.h / 2);
    return pos;
}



// Circle
void DrawCircle(SDL_Renderer * renderer, int x, int y, int r, Color color, Color baseColor)
{

    int radius = r;
    SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
    
    SDL_SetRenderDrawColor(renderer, baseColor.R, baseColor.G, baseColor.B, baseColor.A);
}






// Plateau
void drawBoard(SDL_Renderer* renderer, position pos, plateau p, Color c1, Color c2, Color base, 
    short flag, SDL_Rect* BoardRect, int width, int height)
{

    bool color = 0;
    

    int ScreenWidth, ScreenHeight;
    
    SDL_GetRendererOutputSize(renderer, &ScreenWidth, &ScreenHeight);
    
    position NewPos;
    
    
    int w = width / p.N;
    int h = height / p.N;
    position CenterPos;
    
    
    if(flag == BOARD_CENTERED)
    {
        CenterPos.x = (ScreenWidth / 2) - (width / 2);
        CenterPos.y = (ScreenHeight / 2) - (height / 2);
    }
    else
    {
        CenterPos = pos;
    }

    

    SDL_Rect BufferRect;
    BufferRect.w = w;
    BufferRect.h = h;
            
  
    for(int i = 0; i < p.N; ++i)
    {
        for(int j = 0; j < p.N; ++j)
        {

            NewPos.x = CenterPos.x + w * j;
            NewPos.y = CenterPos.y + h * i;

  
            BufferRect.x = NewPos.x;
            BufferRect.y = NewPos.y;
            
 
            if(color == 0)
            {
                drawRectangle(renderer, &BufferRect, c1, base);
                color = 1;
            }
            else
            {
                drawRectangle(renderer, &BufferRect, c2, base);
                color = 0;
            }
        }
        

        if(p.N % 2 == 0)
        {
            color = !color;
        }
    }
    
    
    BufferRect.x = 0;
    BufferRect.y = 0;
    BufferRect.w = w;
    BufferRect.h = h;
    
    for(int i = 0; i < p.N; ++i)
    {
        for(int j = 0; j < p.N; ++j)
        {
            if(flag == BOARD_CENTERED)
            {
                BufferRect.x = BufferRect.w * (j - 1) + (BufferRect.w / 2) + w;
                BufferRect.y = BufferRect.h * (i - 1) + (BufferRect.h / 2) + h;
                
            }
            else
            {
                BufferRect.x = BufferRect.w * (j - 1) + (BufferRect.w / 2);
                BufferRect.y = BufferRect.h * (i - 1) + (BufferRect.h / 2);              
            }
            
            
            position po;
            po.x = BufferRect.x + BufferRect.w;
            po.y = BufferRect.y + BufferRect.h;
            if(p.plateau[i][j].couleur == RED)
            {
                DrawCircle(renderer, pos.x, pos.y, BufferRect.h / 2, setColor(255, 0, 0, 255), base);
            }
            else if(p.plateau[i][j].couleur == WHITE)
            {
                DrawCircle(renderer, pos.x, pos.y, BufferRect.w / 2, setColor(255, 255, 255, 255), base);
            }
            
            
        }
    }
    
    
}

