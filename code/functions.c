#include "raylib.h"
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
//Texturas do player com cada uma das orientações
Image img_playerN;
Texture2D playerNTexture;
Image img_playerS;
Texture2D playerSTexture;
Image img_playerE;
Texture2D playerETexture;
Image img_playerW;
Texture2D playerWTexture;
Image BackGround;
Image img_wall;
Texture2D wallTexture;
typedef struct
{
    int lifes;
    int level;
    int score;
    int sword;
} status;


void ShowTopBar(status TopBarStatus)
{
    char l[10], lev[12], sc[15];
    sprintf(l, "Vidas: %d", TopBarStatus.lifes);
    sprintf(lev, "Nivel: %d", TopBarStatus.level);
    sprintf(sc, "Escores: %d", TopBarStatus.score);
    DrawRectangle(0, 0, 1200, 60, BLACK);
    DrawText(l, 40, 5, 50, WHITE);
    DrawText(lev, 280, 5, 50, WHITE);
    DrawText(sc, 480, 5, 50, WHITE);
    if(!TopBarStatus.sword){
        DrawTexture(swordTexture, 1100 , 0, WHITE);
    }
}
void generateMap(char path[10], int MapArray[16][24], int MonsterArray[5][4], int SwordArray[3], int LifesArray[5][3], int *x_player, int *y_player)
{
    int i, j, lifes = 0, monsters = 0, x, y;
    char line[16], item;
    FILE *map = fopen(path, "r");
    for(i = 0; i < 16; i++){
        for(j = 0; j < 24; j++){
            item = (char)fgetc(map);
            if(item == 'P'){
                MapArray[i][j] = 1;
            }else{
                MapArray[i][j] = 0;
                x = j*50;
                y = i*50;
                switch(item){
                    case 'J':
                        *x_player = x;
                        *y_player = y;
                        break;
                    case 'V':
                        LifesArray[lifes][0] = x;
                        LifesArray[lifes][1] = y;
                        LifesArray[lifes][2] = 1;
                        lifes++;
                        break;
                    case 'M':
                        MonsterArray[monsters][0] = x;
                        MonsterArray[monsters][1] = y;
                        MonsterArray[monsters][2] = rand()%(100 + 1);
                        MonsterArray[monsters][3] = 1;
                        monsters++;
                        break;
                    case 'E':
                        SwordArray[0] = x;
                        SwordArray[1] = y;
                        SwordArray[2] = 1;
                }
            }
            x = 0;
            y = 0;
        }
    }
}
int menu(int gameInProgress)
{
    char text[40], *optionsText[3];
    int optionSelected, i, desenha;
    optionSelected = 0;
    desenha = 1;
    if(gameInProgress){
        optionsText[0] = "Continuar Jogo";
        optionsText[1] = "Voltar ao menu";
        optionsText[2] = "Sair";
    } else {
        optionsText[0] = "Iniciar";
        optionsText[1] = "Scoreboard";
        optionsText[2] = "Sair";
    }

    while(desenha){
        DrawText("ZINF", 100, 20, 100, WHITE);
        for(i = 0; i < 3; i++){
            if(optionSelected == i){
                DrawCircle(90, i*110 + 220, 5, RED);
                DrawText(optionsText[i], 100, i*110 + 200, 50, RED);
            } else {
                DrawText(optionsText[i], 100, i*110 + 200, 50, WHITE);
            }
        }
        //strcpy(texto,"Direita");
        if(IsKeyPressed(KEY_DOWN)){
            if(optionSelected == 2){
                optionSelected = 0;
            } else {
                optionSelected++;
            }
        }
        if(IsKeyPressed(KEY_UP)){
            if(optionSelected == 0){
                optionSelected = 2;
            } else {
                optionSelected--;
            }
        }
        BeginDrawing();
	    EndDrawing();
	    ClearBackground(BLACK);
	    if(IsKeyPressed(KEY_ENTER)||IsKeyPressed(KEY_LEFT)){
            desenha = 0;
            CloseWindow();
	    }
    }
    return optionSelected;
}
void killMonster(status *gameStatus, int arrayMonsters[5][4], int monster)
{
    int monsterScore;
    monsterScore = arrayMonsters[monster][2];
    gameStatus->score += monsterScore;
    arrayMonsters[monster][3] = 0;
}
int existMonster(int orientation, int arrayMonsters[5][4], int x_player, int y_player)
{
    int i, x, y, x_monster, y_monster;
    x = x_player;
    y = y_player;
    switch(orientation){
        case 1:
            x += 150;
            break;
        case 2:
            x -= 150;
            break;
        case 3:
            y -= 150;
            break;
        default:
            y += 150;
    }
    for(i = 0; i < 5; i++){
        if(arrayMonsters[i][3]){
            x_monster = arrayMonsters[i][0];
            y_monster = arrayMonsters[i][1];
            if(((x_monster <= x)&&(x_monster >= x_player))||((x_monster >= x)&&(x_monster <= x_player))||((y_monster <= y)&&(y_monster >= y_player))||((y_monster >= y)&&(y_monster <= y_player))){
                return i;
            }
        }
    }
    return -1;
}
void drawPlayer(int x, int y, int orientation)
{
    Texture2D playerTextureOriented;
    switch(orientation){
        case 1:
            playerTextureOriented = playerETexture;
            break;
        case 2:
            playerTextureOriented = playerWTexture;
            break;
        case 3:
            playerTextureOriented = playerNTexture;
            break;
        case 4:
            playerTextureOriented = playerSTexture;
    }
    DrawTexture(playerTextureOriented, x, y, WHITE);
}
void genarateWall(int matriz[16][24])
{
    int i, j;
    for(i = 0; i < 16; i++){
        for(j = 0; j < 24; j++){
            if(matriz[i][j]){
                DrawTexture(wallTexture, j*50, i*50, WHITE);
            }
        }
    }
}

int conferePosicao(int x, int y, int matriz[16][24])
{
    if((!matriz[(int) floor(y/50)][(int) floor((x)/50)])&&(x < 1200)&&(x > -50)&&(y < 920)&&(y > 0)){
        return 1;
	} else {
        return 0;
	}
}
void chatchLife(status *lifeStatus)
{
    lifeStatus->lifes += 1;
}
void chatchSword(status *swordStatus, int arraySword[3])
{
    swordStatus->sword = 1;
    arraySword[2] = 0;
}
void drawSword(int arraySword[3])
{
    if(arraySword[2]){
        DrawTexture(swordTexture, arraySword[0], arraySword[1], BLACK);
    }
}
void drawMonsters(int MonstersArray[5][4], int MapArray[16][24])
{
    int i, randow, move, x, y;
    for(i = 0; i < 5; i++){
        if(MonstersArray[i][3]){
            x = MonstersArray[i][0];
            y = MonstersArray[i][1];
            DrawTexture(monsterTexture, x, y, WHITE);
            move = rand()%(5);
            randow = rand()%(4);
            if(move == 1){
                if(randow < 2){
                    if((randow == 1)&&(x < 800)){
                        x += 50;
                    } else if(x > 0){
                        x -= 50;
                    }
                } else {
                    if((randow == 3)&&(y < 800)){
                        y += 50;
                    } else if(y > 0){
                        y -= 50;
                    }
                }
                if(conferePosicao(x, y, MapArray)){
                    MonstersArray[i][1] = y;
                    MonstersArray[i][0] = x;
                }
            }
        }
    }
}

void drawLifes(int LifeArray[5][3])
{
    int i;
    for(i = 0; i < 5; i++){
        if(LifeArray[i][2]){
            DrawTexture(lifeTexture, LifeArray[i][0], LifeArray[i][1], WHITE);
        }
    }
}
void generateTextures()
{
    img_sword = LoadImage("../assets/sword.png");
    ImageResize(&img_sword, 50, 50);
    swordTexture = LoadTextureFromImage(img_sword);
    img_monster = LoadImage("../assets/monster.png");
    ImageResize(&img_monster, 50, 50);
    monsterTexture = LoadTextureFromImage(img_monster);
    img_life = LoadImage("../assets/life.png");
    ImageResize(&img_life, 50, 50);
    lifeTexture = LoadTextureFromImage(img_life);
    //texturas do player
    //norte
    img_playerN = LoadImage("../assets/jogador-norte.png");
    ImageResize(&img_playerN, 50, 50);
    playerNTexture = LoadTextureFromImage(img_playerN);
    //leste
    img_playerE = LoadImage("../assets/jogador-leste.png");
    ImageResize(&img_playerE, 50, 50);
    playerETexture = LoadTextureFromImage(img_playerE);
    //sul
    img_playerS = LoadImage("../assets/jogador-sul.png");
    ImageResize(&img_playerS, 50, 50);
    playerSTexture = LoadTextureFromImage(img_playerS);
    //oeste
    img_playerW = LoadImage("../assets/jogador-oeste.png");
    ImageResize(&img_playerW, 50, 50);
    playerWTexture = LoadTextureFromImage(img_playerW);
    //parede
    img_wall = LoadImage("../assets/wall.png");
    ImageResize(&img_wall, 50, 50);
    wallTexture = LoadTextureFromImage(img_wall);
}
void unloadTextures()
{
    UnloadImage(img_sword);
    UnloadImage(img_life);
    UnloadImage(img_monster);
    UnloadImage(img_playerE);
    UnloadImage(img_playerN);
    UnloadImage(img_playerS);
    UnloadImage(img_playerW);

}
int StartGame()
{
    status InGameStatus;
    InGameStatus.lifes = 3;
    InGameStatus.level = 1;
    InGameStatus.score = 0;
    InGameStatus.sword = 0;
    int MapArray[16][24], i, j, MenuAnswer, MonsterArray[5][4], SwordArray[3], LifesArray[5][3] = {{0}}, x_player, y_player, orientation = 1, monsterKilled;
    InitWindow(LARGURA, ALTURA, "ZINF"); //Inicializa janela, com certo tamanho e titulo
    SetTargetFPS(20);// Ajusta a janela para 60 frames por segundo


    BackGround = LoadImage("../assets/background.png");
    generateTextures();
    srand(time(NULL));
    generateMap("../assets/mapa01.txt", MapArray, MonsterArray, SwordArray, LifesArray, &x_player, &y_player);

    printf("%d, %d\n", SwordArray[0], SwordArray[1]);
    drawPlayer(x_player, y_player, orientation);
    while (!WindowShouldClose())
    {
        // Trata entrada do usuario e atualiza estado do jogo
        if (IsKeyPressed(KEY_RIGHT)||IsKeyDown(KEY_RIGHT)) {
            orientation = 1;
            if(conferePosicao((x_player + 50), y_player, MapArray)){
                x_player += 50;
            }
        }
        if (IsKeyPressed(KEY_LEFT)||IsKeyDown(KEY_LEFT)) {
            orientation = 2;
            if(conferePosicao((x_player -50), y_player, MapArray)){
                x_player -= 50;
            }
        }
        if (IsKeyPressed(KEY_UP)||IsKeyDown(KEY_UP)) {
            orientation = 3;
            if(conferePosicao(x_player, (y_player -50), MapArray)){
                y_player -= 50;
            }
        }
        if (IsKeyPressed(KEY_DOWN)||IsKeyDown(KEY_DOWN)) {
            orientation = 4;
            if(conferePosicao(x_player, (y_player + 50), MapArray)){
                y_player += 50;
            }
        }
        if(IsKeyPressed(KEY_TAB)){
            MenuAnswer = menu(1);
            if(MenuAnswer == 2)
            {
                break; //Fecha jogo
            } else if(MenuAnswer == 0){
                //Só fecha o menu e continua o jogo
            } else {
                //Chama o menu inicial
                MenuAnswer = menu(0);
                if(MenuAnswer == 2)
                {
                    CloseWindow(); //Fecha jogo
                } else if(MenuAnswer == 0){
                    if(StartGame() == 0){//Incia Jogo
                        break;
                    }
                } else {
                    //Mostra Scoreboard
                }
            }
        }
        if((SwordArray[2])&&(SwordArray[0] == x_player)&&(SwordArray[1] == y_player)){
            chatchSword(&InGameStatus, SwordArray);
        }

        if(InGameStatus.sword = 1){
            if(IsKeyPressed(KEY_J)){
                monsterKilled = existMonster(orientation, MonsterArray, x_player, y_player);
                if(monsterKilled > -1){
                    killMonster(&InGameStatus, MonsterArray, monsterKilled);
                }
            }
        }
        for(i = 0; i < 5; i++){
            if((LifesArray[i][2])&&(LifesArray[i][0] == x_player)&&(LifesArray[i][1] == y_player)){
                LifesArray[i][2] = 0;
                chatchLife(&InGameStatus);
            }
        }
        drawPlayer(x_player, y_player, orientation);
        genarateWall(MapArray);
        drawMonsters(MonsterArray, MapArray);
        drawLifes(LifesArray);

        ShowTopBar(InGameStatus);
        // Atualiza o que eh mostrado na tela a partir do estado do jogo
        BeginDrawing(); //Inicia o ambiente de desenho na tela
        EndDrawing(); //Finaliza o ambiente de desenho na tela
        ClearBackground(WHITE);
        //ImageClearBackground(&BackGround, WHITE); //não consegui utilizar essa função
    }
    unloadTextures();
    CloseWindow(); // Fecha a janela
    return 0;
}
