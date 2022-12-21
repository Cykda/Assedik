#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gamesave.h"


void save_game(plateau p, char* path, short color) // aka Danielou
{

    //char sentence[1000];


    FILE *fptr;


    fptr = fopen(path, "w");


    if (fptr == NULL) {
        printf("Error while opening Save file\n");
        exit(1);
    }
    
    fprintf(fptr, "%d\n", p.N);
    fprintf(fptr, "%d\n", color);    
    for(int i = 0; i < p.N; ++i)
    {
        for(int j = 0; j < p.N; ++j)
        {
            fprintf(fptr, "%d|%d|%d ", p.plateau[i][j].couleur + 1, p.plateau[i][j].pos.x, p.plateau[i][j].pos.y);
        }
        fprintf(fptr, "\n");
    }
    
    
    
    
    fclose(fptr);

    
}



plateau load_game(char* path, int* currentPlayedColor)
{
    FILE *file;
    char *text;
    long numbytes;
    if ( (file = fopen(path, "rb")) == NULL)
    {
        
        printf("Cannot read game, file error\n");
        return;
    }
    

    fseek(file, 0L, SEEK_END);
    numbytes = ftell(file);
    fseek(file, 0L, SEEK_SET);  

    text = (char*)calloc(numbytes, sizeof(char));   
    if(text == NULL)
    return;

    fread(text, sizeof(char), numbytes, file);
    fclose(file);
    
    
    char * curLine = text;
    
    int lineID = 0;
    
    
    plateau p;
    position BoardCounter;
            
    BoardCounter.x = 0;
    BoardCounter.y = 0;

    while(curLine)
    {
        char * nextLine = strchr(curLine, '\n');
        
        
        if (nextLine)
        {
             *nextLine = '\0';
        }
        
        if(lineID == 0)
        {
            
            int pN;
            sscanf(curLine, "%d", &pN);
            initPlateau(&p, pN);
        }
        
        else if(lineID == 1)
        {
            int PlayingColor;
            sscanf(curLine, "%d", &PlayingColor);
            
            if(PlayingColor == 1)
            {
                printf("Current Playing Color RED\n");
            }
            else
            {
                printf("Current Playing Color WHITE\n");
            }
        }
        else if(lineID > 1)
        {




            char *ptr = strtok(curLine, " ");

            while(ptr != NULL)
            {
                char c = ptr[0];
                if(c == '0' || c == '1' || c == '2')
                {
                    int CaseColor = (c - '0') - 1;
                    
                    
                    if(BoardCounter.x >= p.N)
                    {
                        BoardCounter.x = 0;
                        BoardCounter.y += 1;
                    }
                    
                    pion BufferPawn;
                    
                    BufferPawn.couleur = CaseColor;
                    BufferPawn.pos = BoardCounter;
                    p.plateau[BoardCounter.y][BoardCounter.x] = BufferPawn;
                    BoardCounter.x++;
                }
                
                
                ptr = strtok(NULL, " ");
            }


        }
        
        
        
        if (nextLine)
        {
          *nextLine = '\n';  
        }   
        curLine = nextLine ? (nextLine+1) : NULL;
        lineID++;
    }


    return p;

    //printf("%s", text);
}