#include "raylib.h"
#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LARGURA 1200
#define ALTURA 860

Image img_sword;
Texture2D swordTexture;
Image img_monster;
Texture2D monsterTexture;
Image img_life;
Texture2D lifeTexture;

int main()
{
    int respostaMenu;
    InitWindow(LARGURA, ALTURA, "ZINF");
    SetTargetFPS(30);
    img_sword = LoadImage("sword.png");
    ImageResize(&img_sword, 50, 50);
    swordTexture = LoadTextureFromImage(img_sword);
    respostaMenu = menu(0);
    if(respostaMenu == 2)
    {
        return 0; //Fecha jogo
    } else if(respostaMenu == 0){
        if(StartGame() == 0){//Incia Jogo
            return 0;
        }
    } else {
        //Mostra Scoreboard
    }

    return 0;
}
