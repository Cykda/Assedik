#ifndef GAMESAVE_H
#define GAMESAVE_H

#include "plateau.h"



typedef struct
{
    plateau Board;
    short CurrentPlayer;
} Board_Data;


void save_game(plateau p, char* path, short color);
Board_Data load_game(char* path);

#endif /*GAMESAVE_H*/