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

typedef struct couleur couleur;
struct couleur
{
    int couleur;
    int quantite;
};

typedef struct pion pion;
struct pion
{
    couleur info;
    position pos;
};

typedef struct plateau plateau;
struct plateau
{
    pion** plateau;
    int N;
};


int initPlateau(plateau* p, int N);
void freeboard(plateau* p);
void showBoard(plateau p);
position setPosition(int x,  int y);

#endif /*PLATEAU_H*/
