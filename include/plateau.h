#ifndef PLATEAU_H
#define PLATEAU_H

#include <stdbool.h>

typedef enum couleurs couleurs;
enum couleurs
{
    RED = 1,
    WHITE = 0,
    NONE = -1
};

typedef struct position position;
struct position
{
    int x;
    int y;
};

typedef struct pion pion;
struct pion
{
    int couleur;
    position pos;
};

typedef struct plateau plateau;
struct plateau
{
    pion** plateau;
    int N;
};


int initPlateau(plateau* p, int N);
void freeborad(plateau* p);
void showBoard(plateau p);
bool BoardEqu(plateau p1, plateau p2);
position setPosition(int x,  int y);
#endif /*PLATEAU_H*/