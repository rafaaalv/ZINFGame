#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LARGURA 1200
#define ALTURA 860
#define SPRITE_WIDHT 24
#define SPRITE_HEIGHT 16
#define SPRITE_SIZE 50
#define MAX_MONSTERS 5
#define MAX_LIFES 5
#define MONSTERS_COLLUM 5
#define SWORD_COLLUM 3
#define LIFES_COLLUM 4
//DEFINIDO AT� AQUI




Image img_sword;
Texture2D swordTexture;
Image img_life;
Texture2D lifeTexture;
//Texturas do player com cada uma das orienta��es
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
//Texturas do monstro com cada uma das orientacoes
Image img_monsterN;
Texture2D monsterNTexture;
Image img_monsterS;
Texture2D monsterSTexture;
Image img_monsterE;
Texture2D monsterETexture;
Image img_monsterW;
Texture2D monsterWTexture;
Texture2D arrayTexturesMonster[4];
Image BackGround;
Image img_wall;
Texture2D wallTexture;
//Fontes
//Font fontBm;
//Font fontTtf;


typedef struct
{
    int lifes;
    int level;
    int score;
    int sword;
} status;

void generateTextures()
{
    img_sword = LoadImage("../assets/sword.png");
    ImageResize(&img_sword, SPRITE_SIZE, SPRITE_SIZE);
    swordTexture = LoadTextureFromImage(img_sword);
    img_life = LoadImage("../assets/life.png");
    ImageResize(&img_life, SPRITE_SIZE, SPRITE_SIZE);
    lifeTexture = LoadTextureFromImage(img_life);
    //texturas do player
    //norte
    img_playerN = LoadImage("../assets/jogador-norte.png");
    ImageResize(&img_playerN, SPRITE_SIZE, SPRITE_SIZE);
    playerNTexture = LoadTextureFromImage(img_playerN);
    //leste
    img_playerE = LoadImage("../assets/jogador-leste.png");
    ImageResize(&img_playerE, SPRITE_SIZE, SPRITE_SIZE);
    playerETexture = LoadTextureFromImage(img_playerE);
    //sul
    img_playerS = LoadImage("../assets/jogador-sul.png");
    ImageResize(&img_playerS, SPRITE_SIZE, SPRITE_SIZE);
    playerSTexture = LoadTextureFromImage(img_playerS);
    //oeste
    img_playerW = LoadImage("../assets/jogador-oeste.png");
    ImageResize(&img_playerW, SPRITE_SIZE, SPRITE_SIZE);
    playerWTexture = LoadTextureFromImage(img_playerW);
    //parede
    img_wall = LoadImage("../assets/wall.png");
    ImageResize(&img_wall, SPRITE_SIZE, SPRITE_SIZE);
    wallTexture = LoadTextureFromImage(img_wall);
    //texturas do monster
    //norte
    img_monsterN = LoadImage("../assets/monsterN.png");
    ImageResize(&img_monsterN, SPRITE_SIZE, SPRITE_SIZE);
    monsterNTexture = LoadTextureFromImage(img_monsterN);
    //leste
    img_monsterE = LoadImage("../assets/monsterE.png");
    ImageResize(&img_monsterE, SPRITE_SIZE, SPRITE_SIZE);
    monsterETexture = LoadTextureFromImage(img_monsterE);
    //sul
    img_monsterS = LoadImage("../assets/monsterS.png");
    ImageResize(&img_monsterS, SPRITE_SIZE, SPRITE_SIZE);
    monsterSTexture = LoadTextureFromImage(img_monsterS);
    //oeste
    img_monsterW = LoadImage("../assets/monsterW.png");
    ImageResize(&img_monsterW, SPRITE_SIZE, SPRITE_SIZE);
    monsterWTexture = LoadTextureFromImage(img_monsterW);
    arrayTexturesMonster[0] = monsterETexture;
    arrayTexturesMonster[1] = monsterWTexture;
    arrayTexturesMonster[2] = monsterSTexture;
    arrayTexturesMonster[3] = monsterNTexture;
    //fontes
    //fontBm = LoadFont("resources/pixantiqua.fnt");
    //fontTtf = LoadFontEx("resources/pixantiqua.ttf", 32, 0, 2SPRITE_SIZE);
    //SetTextLineSpacing(16);
}
void unloadTextures()
{
    UnloadImage(img_sword);
    UnloadImage(img_life);
    UnloadImage(img_playerE);
    UnloadImage(img_playerN);
    UnloadImage(img_playerS);
    UnloadImage(img_playerW);
    UnloadImage(img_wall);
    UnloadImage(img_monsterE);
    UnloadImage(img_monsterN);
    UnloadImage(img_monsterS);
    UnloadImage(img_monsterW);
    //Fontes
    //UnloadFont(fontBm);
    //UnloadFont(fontTtf);
    //Texturas
    UnloadTexture(swordTexture);
    UnloadTexture(lifeTexture);
    UnloadTexture(playerETexture);
    UnloadTexture(playerNTexture);
    UnloadTexture(playerSTexture);
    UnloadTexture(playerWTexture);
    UnloadTexture(monsterETexture);
    UnloadTexture(monsterNTexture);
    UnloadTexture(monsterSTexture);
    UnloadTexture(monsterWTexture);
    UnloadTexture(wallTexture);
}

void ShowTopBar(status TopBarStatus)
{
    char l[10], lev[12], sc[15];
    sprintf(l, "Vidas: %d", TopBarStatus.lifes);
    sprintf(lev, "Nivel: %d", TopBarStatus.level);
    sprintf(sc, "Escores: %d", TopBarStatus.score);
    DrawRectangle(0, 0, 1200, 60, BLACK);
    DrawText(l, 40, 5, SPRITE_SIZE, WHITE);
    DrawText(lev, 280, 5, SPRITE_SIZE, WHITE);
    DrawText(sc, 480, 5, SPRITE_SIZE, WHITE);
    if(!TopBarStatus.sword){
        DrawTexture(swordTexture, 1100 , 0, WHITE);
    }
}
void generateMap(char path[10], int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], int MonsterArray[MAX_MONSTERS][MONSTERS_COLLUM], int SwordArray[3], int LifesArray[5][3], int *x_player, int *y_player)
{
    int i, j, lifes = 0, monsters = 0, x, y;
    char line[16], item;
    FILE *map = fopen(path, "r");
    for(i = 0; i < 16; i++){
        for(j = 0; j < SPRITE_WIDHT; j++){
            item = (char)fgetc(map);
            if(item == 'P'){
                MapArray[i][j] = 1;
            }else{
                MapArray[i][j] = 0;
                x = j*SPRITE_SIZE;
                y = i*SPRITE_SIZE;
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
                        MonsterArray[monsters][4] = 1;
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
    int optionSelected, i, draw;
    optionSelected = 0;
    draw = 1;
    if(gameInProgress){
        optionsText[0] = "Continuar Jogo";
        optionsText[1] = "Voltar ao menu";
        optionsText[2] = "Sair";
    } else {
        optionsText[0] = "Iniciar";
        optionsText[1] = "Scoreboard";
        optionsText[2] = "Sair";
    }

    InitWindow(LARGURA, ALTURA, "Menu");
    generateTextures();
    SetTargetFPS(60);
    while(draw){
        DrawText("ZINF", 100, 20, 100, WHITE);
        for(i = 0; i < 3; i++){
            if(optionSelected == i){
                DrawCircle(90, i*110 + 220, 5, RED);
                DrawText(optionsText[i], 100, i*110 + 200, SPRITE_SIZE, RED);
            } else {
                DrawText(optionsText[i], 100, i*110 + 200, SPRITE_SIZE, WHITE);
            }
        }
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
            draw = 0;
            CloseWindow();
	    }
    }
    return optionSelected;
}
int gameOver()
{
    char *optionsText[3];
    int optionSelected, i, draw, MenuAnswer;
    optionSelected = 0;
    draw = 1;
    optionsText[0] = "Recomecar";
    optionsText[1] = "Voltar ao menu";
    optionsText[2] = "Sair";
    InitWindow(LARGURA, ALTURA, "Game Over");
    generateTextures();
    SetTargetFPS(60);
    while(draw){
        DrawText("VOCE PERDEU", 100, 20, 100, WHITE);
        for(i = 0; i < 3; i++){
            if(optionSelected == i){
                DrawCircle(90, i*110 + 220, 5, RED);
                DrawText(optionsText[i], 100, i*110 + 200, SPRITE_SIZE, RED);
            } else {
                DrawText(optionsText[i], 100, i*110 + 200, SPRITE_SIZE, WHITE);
            }
        }
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
            draw = 0;
            CloseWindow();
	    }
    }
    return optionSelected;
}
void restartStatus(status *gameStatus, int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], int MonsterArray[MAX_MONSTERS][MONSTERS_COLLUM], int SwordArray[3], int LifesArray[5][3], int *x_player, int *y_player)
{
    gameStatus->lifes = 3;
    gameStatus->level = 1;
    gameStatus->score = 0;
    gameStatus->sword = 0;
    generateMap("../assets/mapa01.txt", MapArray, MonsterArray, SwordArray, LifesArray, x_player, y_player);
}
void killMonster(status *gameStatus, int arrayMonsters[MAX_MONSTERS][MONSTERS_COLLUM], int monster)
{
    int monsterScore;
    monsterScore = arrayMonsters[monster][2];
    gameStatus->score += monsterScore;
    arrayMonsters[monster][3] = 0;
}
int existMonster(int orientation, int arrayMonsters[MAX_MONSTERS][MONSTERS_COLLUM], int x_player, int y_player)
{
    int i, x, y, x_monster, y_monster;
    x = x_player;
    y = y_player;
    switch(orientation){
        case 1:
            x += 3*SPRITE_SIZE;//tres blocos de ataque
            break;
        case 2:
            x -= 3*SPRITE_SIZE;
            break;
        case 3:
            y -= 3*SPRITE_SIZE;
            break;
        default:
            y += 3*SPRITE_SIZE;
    }
    for(i = 0; i < MAX_MONSTERS; i++){
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
void genarateWall(int matriz[SPRITE_HEIGHT][SPRITE_WIDHT])
{
    int i, j;
    for(i = 0; i < 16; i++){
        for(j = 0; j < SPRITE_WIDHT; j++){
            if(matriz[i][j]){
                DrawTexture(wallTexture, j*SPRITE_SIZE, i*SPRITE_SIZE, WHITE);
            }
        }
    }
}

int conferePosicao(int x, int y, int matriz[SPRITE_HEIGHT][SPRITE_WIDHT])
{
    if((!matriz[(int) floor(y/SPRITE_SIZE)][(int) floor((x)/SPRITE_SIZE)])&&(x < 1200)&&(x > -SPRITE_SIZE)&&(y < 920)&&(y > 0)){
        return 1;
	} else {
        return 0;
	}
}
void changeLife(status *lifeStatus, int value)
{
    lifeStatus->lifes += value;
}
void attackMonster(status *atualStatus, int arrayMonsters[MAX_MONSTERS][MONSTERS_COLLUM], int x_player, int y_player)
{
    int i;
    for(i = 0; i < MAX_MONSTERS; i++){
        if((x_player == arrayMonsters[i][0])&&(y_player == arrayMonsters[i][1])){
            changeLife(atualStatus, -1);
        }
    }
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
void drawMonsters(int MonstersArray[MAX_MONSTERS][MONSTERS_COLLUM], int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT])
{
    int i, randow, move, x, y;
    for(i = 0; i < MAX_MONSTERS; i++){
        if(MonstersArray[i][3]){
            x = MonstersArray[i][0];
            y = MonstersArray[i][1];
            DrawTexture(arrayTexturesMonster[MonstersArray[i][4] - 1], x, y, WHITE);
            randow = rand()%(2);
            if(randow == 1){
                move = MonstersArray[i][4];
            } else{
                move = rand()%(4) + 1;
            }
            randow = rand()%(6 + 1);
            MonstersArray[i][4] = move;
            if(randow == 1){
                switch(move){
                case 1:
                    x += SPRITE_SIZE;
                    break;
                case 2:
                    x -= SPRITE_SIZE;
                    break;
                case 3:
                    y += SPRITE_SIZE;
                    break;
                case 4:
                    y -= SPRITE_SIZE;
                }
            }
            if(conferePosicao(x, y, MapArray)){
                MonstersArray[i][0] = x;
                MonstersArray[i][1] = y;
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
int callMenu(int gameInProgress, int *continueGame)
{
    int MenuAswer;
    MenuAswer = menu(gameInProgress);
    if(gameInProgress){
        if(MenuAswer == 1){
            callMenu(0, continueGame);
        } else if(MenuAswer == 2){
            *continueGame = 0;
        }
    } else {
        if(MenuAswer == 0){
            return 1; //precisa (re)come�ar o jogo
        } else if(MenuAswer == 1){
            //ScoreBoard
        } else {
            *continueGame = 0;
        }
    }
    return 0;
}
int StartGame()
{
    status InGameStatus;
    int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], i, j, game, continueGame = 1, MenuAnswer, MonsterArray[MAX_MONSTERS][MONSTERS_COLLUM];
    int SwordArray[3], LifesArray[5][3] = {{0}}, x_player, y_player, orientation = 1, monsterKilled;

    BackGround = LoadImage("../assets/background.png");
    restartStatus(&InGameStatus, MapArray, MonsterArray, SwordArray, LifesArray, &x_player, &y_player);
    srand(time(NULL));

    while(continueGame){
        InitWindow(LARGURA, ALTURA, "ZINF"); //Inicializa janela, com certo tamanho e titulo
        generateTextures();
        SetTargetFPS(20);// Ajusta a janela para 20 frames por segundo
        drawPlayer(x_player, y_player, orientation);
        while (!WindowShouldClose())
        {
            if (IsKeyPressed(KEY_RIGHT)||IsKeyDown(KEY_RIGHT)) {
                orientation = 1;
                if(conferePosicao((x_player + SPRITE_SIZE), y_player, MapArray)){
                    x_player += SPRITE_SIZE;
                }
            }
            if (IsKeyPressed(KEY_LEFT)||IsKeyDown(KEY_LEFT)) {
                orientation = 2;
                if(conferePosicao((x_player -SPRITE_SIZE), y_player, MapArray)){
                    x_player -= SPRITE_SIZE;
                }
            }
            if (IsKeyPressed(KEY_UP)||IsKeyDown(KEY_UP)) {
                orientation = 3;
                if(conferePosicao(x_player, (y_player -SPRITE_SIZE), MapArray)){
                    y_player -= SPRITE_SIZE;
                }
            }
            if (IsKeyPressed(KEY_DOWN)||IsKeyDown(KEY_DOWN)) {
                orientation = 4;
                if(conferePosicao(x_player, (y_player + SPRITE_SIZE), MapArray)){
                    y_player += SPRITE_SIZE;
                }
            }
            if(IsKeyPressed(KEY_TAB)){
                game = 3;
                break;
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
                    changeLife(&InGameStatus, 1);
                }
            }
            if(InGameStatus.lifes == 0){
                game = 1;
                break;
            }
            attackMonster(&InGameStatus, MonsterArray, x_player, y_player);
            drawPlayer(x_player, y_player, orientation);
            genarateWall(MapArray);
            drawMonsters(MonsterArray, MapArray);
            drawLifes(LifesArray);

            ShowTopBar(InGameStatus);
            BeginDrawing(); //Inicia o ambiente de desenho na tela
            EndDrawing(); //Finaliza o ambiente de desenho na tela
            ClearBackground(WHITE);
            //ImageClearBackground(&BackGround, WHITE); //n�o consegui utilizar essa fun��o
        }
        CloseWindow();
        switch(game){
            case 1:
                MenuAnswer = gameOver();
                if(MenuAnswer == 0){
                    restartStatus(&InGameStatus, MapArray, MonsterArray, SwordArray, LifesArray, &x_player, &y_player);
                } else if(MenuAnswer == 1){
                    if(callMenu(0, &continueGame)){
                        restartStatus(&InGameStatus, MapArray, MonsterArray, SwordArray, LifesArray, &x_player, &y_player);
                    }
                } else {
                    continueGame = 0;
                }
                break;
            case 2:
                //WinGame
                break;
            case 3:
                if(callMenu(1, &continueGame)){
                    restartStatus(&InGameStatus, MapArray, MonsterArray, SwordArray, LifesArray, &x_player, &y_player);
                }

        }
    }
    unloadTextures();
    CloseWindow(); // Fecha a janela
    return 0;
}
