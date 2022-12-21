#ifndef GAMESAVE_H
#define GAMESAVE_H

#include "plateau.h"


void save_game(plateau p, char* path, short color);
plateau load_game(char* path, int* currentPlayedColor);

#endif /*GAMESAVE_H*/