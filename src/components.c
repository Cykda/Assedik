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
void drawBoard(SDL_Renderer* renderer, SDL_Rect Baserect, plateau p, Color c1, Color c2, Color base, short flag, SDL_Rect* BoardRect)
{

    bool color = 0;

    int w, h;

    SDL_GetRendererOutputSize(renderer, &w, &h);

    w = (w / 2) - (Baserect.w * p.N / 2);
    h = (h / 2) - (Baserect.h * p.N / 2);

    if(BoardRect != NULL)
    {
        BoardRect->x = Baserect.x + w;
        BoardRect->y = Baserect.y + h;
        BoardRect->w = Baserect.w * p.N;
        BoardRect->h = Baserect.h * p.N;
    }

    SDL_Rect rect = Baserect;

    for(int i = 0; i < p.N; ++i)
    {
        for(int j = 0; j < p.N; ++j)
        {
            if(flag == BOARD_CENTERED)
            {
                rect.x = rect.w * j + w;
                rect.y = rect.h * i + h;
            }
            else
            {
                rect.x = rect.w * j;
                rect.y = rect.h * i;
            }

            if(color == 0)
            {
                drawRectangle(renderer, &rect, c1, base);
                color = 1;
            }
            else
            {
                drawRectangle(renderer, &rect, c2, base);
                color = 0;
            }
        }


        if(p.N % 2 == 0)
        {
            color = !color;
        }

    }

    rect = Baserect;

    for(int i = 0; i < p.N; ++i)
    {
        for(int j = 0; j < p.N; ++j)
        {
            if(BOARD_CENTERED)
            {
                rect.x = rect.w * (j - 1) + (rect.w / 2) + w;
                rect.y = rect.h * (i - 1) + (rect.h / 2) + h;

            }
            else
            {
                rect.x = rect.w * (j - 1) + (rect.w / 2);
                rect.y = rect.h * (i - 1) + (rect.h / 2);
            }

            position pos;
            pos.x = rect.x + rect.w;
            pos.y = rect.y + rect.h;

            if(p.plateau[i][j].info.couleur == RED)
            {
                DrawCircle(renderer, pos.x, pos.y, rect.h / 2, setColor(255, 0, 0, 255), base);
            }
            else if(p.plateau[i][j].info.couleur == WHITE)
            {
                DrawCircle(renderer, pos.x, pos.y, rect.w / 2, setColor(255, 255, 255, 255), base);
            }

        }
    }
}
