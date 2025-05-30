#include "raylib.h"
#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LARGURA 1200
#define ALTURA 860


int main()
{
    int respostaMenu;
    respostaMenu = menu(0);
    if(respostaMenu == 2)
    {
        return 0; //Fecha jogo
    } else if(respostaMenu == 0){
        StartGame();//Incia Jogo
    } else {
        //Mostra Scoreboard
    }

    return 0;
}
