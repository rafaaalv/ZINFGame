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
#define SPRITE_SIZE2 55
#define MAX_MONSTERS 10
#define MAX_LIFES 5
#define MONSTERS_COLLUM 5
#define SWORD_COLLUM 3
#define LIFES_COLLUM 4
#define MAX_LIFES_BOSS 20
//DEFINIDO AT� AQUI




Image img_sword;
Texture2D swordTexture;
Image img_life;
Texture2D lifeTexture;
//Texturas do player com cada uma das orienta��es
Image img_playerNDip;
Texture2D playerNDipTexture;
Image img_playerSDip;
Texture2D playerSDipTexture;
Image img_playerEDip;
Texture2D playerEDipTexture;
Image img_playerWDip;
Texture2D playerWDipTexture;
Image img_playerNMab;
Texture2D playerNMabTexture;
Image img_playerSMab;
Texture2D playerSMabTexture;
Image img_playerEMab;
Texture2D playerEMabTexture;
Image img_playerWMab;
Texture2D playerWMabTexture;
Texture2D arrayTexturesPlayer[2][4];
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
Texture2D BackGroundTexture;
Image img_wall;
Texture2D wallTexture;
//Confetes
Image img_conf1;
Image img_conf2;
//Image img_conf1;
Texture2D confettis[2];
//Textura do boss
Image img_boss;
Texture2D bossTexture;
//Textura do bosso no modo com raiva
Image img_bossDificult;
Texture2D bossDificultTexture;
//Textura da bola de fogo
Image img_fireBall;
Texture2D fireBallTexture;
//Textura da bola de fogo azul
Image img_fireBallBlue;
Texture2D fireBallBlueTexture;
//Fontes
//Font fontBm;
//Font fontTtf;
//Personagem escolhido
// player.person 0 para dipper, 1 para mabel

typedef struct score
{
    char name[20];
    int score;
} score;

typedef struct status
{
    int lifes;
    int level;
    int score;
    int sword;
} status;
typedef struct boss
{
    int lifes;
    int x;
    int y;
    int attack; //pode ser 3 bolas de fogo por vez ou 5
    int orientation; //pode ser 0(subindo), ou 1(descendo)
} boss;
typedef struct fireBall
{
    int exist;
    int x;
    int y;
} fireBall;
typedef struct save
{
    int index;
    char date[24];
    char path[30];
} save;
typedef struct monster
{
    int x;
    int y;
    int score;
    int alive;
    int orientation;
    int qnt;
} monster;
typedef struct sword
{
    int x;
    int y;
    int alive;
} sword;
typedef struct life
{
    int x;
    int y;
    int alive;
} life;
typedef struct player
{
    int x;
    int y;
    int orientation;
    int person;
    int imune;
} player;
typedef struct game
{
    player atualPlayer;
    status atualStatus;
    monster monsters[MAX_MONSTERS];
    sword atualSword;
    life lifes[MAX_LIFES];
    boss bossBill;
} game;


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
    /*img_playerN = LoadImage("../assets/jogador-norte.png");
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
    playerWTexture = LoadTextureFromImage(img_playerW);*/
    //Dipper
    img_playerNDip = LoadImage("../assets/sprite_dipper03.png");
    ImageResize(&img_playerNDip, SPRITE_SIZE2, SPRITE_SIZE2);
    playerNDipTexture = LoadTextureFromImage(img_playerNDip);
    //leste
    img_playerEDip = LoadImage("../assets/sprite_dipper00.png");
    ImageResize(&img_playerEDip, SPRITE_SIZE2, SPRITE_SIZE2);
    playerEDipTexture = LoadTextureFromImage(img_playerEDip);
    //sul
    img_playerSDip = LoadImage("../assets/sprite_dipper02.png");
    ImageResize(&img_playerSDip, SPRITE_SIZE2, SPRITE_SIZE2);
    playerSDipTexture = LoadTextureFromImage(img_playerSDip);
    //oeste
    img_playerWDip = LoadImage("../assets/sprite_dipper01.png");
    ImageResize(&img_playerWDip, SPRITE_SIZE2, SPRITE_SIZE2);
    playerWDipTexture = LoadTextureFromImage(img_playerWDip);
    arrayTexturesPlayer[0][0] = playerEDipTexture;
    arrayTexturesPlayer[0][1] = playerWDipTexture;
    arrayTexturesPlayer[0][2] = playerNDipTexture;
    arrayTexturesPlayer[0][3] = playerSDipTexture;
    //Mabel
    img_playerNMab = LoadImage("../assets/sprite_mabel03.png");
    ImageResize(&img_playerNMab, SPRITE_SIZE2, SPRITE_SIZE2);
    playerNMabTexture = LoadTextureFromImage(img_playerNMab);
    //leste
    img_playerEMab = LoadImage("../assets/sprite_mabel00.png");
    ImageResize(&img_playerEMab, SPRITE_SIZE2, SPRITE_SIZE2);
    playerEMabTexture = LoadTextureFromImage(img_playerEMab);
    //sul
    img_playerSMab = LoadImage("../assets/sprite_mabel02.png");
    ImageResize(&img_playerSMab, SPRITE_SIZE2, SPRITE_SIZE2);
    playerSMabTexture = LoadTextureFromImage(img_playerSMab);
    //oeste
    img_playerWMab = LoadImage("../assets/sprite_mabel01.png");
    ImageResize(&img_playerWMab, SPRITE_SIZE2, SPRITE_SIZE2);
    playerWMabTexture = LoadTextureFromImage(img_playerWMab);
    arrayTexturesPlayer[1][0] = playerEMabTexture;
    arrayTexturesPlayer[1][1] = playerWMabTexture;
    arrayTexturesPlayer[1][2] = playerNMabTexture;
    arrayTexturesPlayer[1][3] = playerSMabTexture;
    //parede
    img_wall = LoadImage("../assets/wall.png");
    ImageResize(&img_wall, 2*SPRITE_SIZE, 2*SPRITE_SIZE);
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
    //confetes
    img_conf1 = LoadImage("../assets/confete1.png");
    img_conf2 = LoadImage("../assets/confete2.png");
    ImageResize(&img_conf1, 3*SPRITE_SIZE, 3*SPRITE_SIZE);
    ImageResize(&img_conf2, 3*SPRITE_SIZE, 3*SPRITE_SIZE);
    confettis[0] = LoadTextureFromImage(img_conf1);
    confettis[1] = LoadTextureFromImage(img_conf2);
    //boss
    img_boss = LoadImage("../assets/boss.png");
    ImageResize(&img_boss, 3*SPRITE_SIZE, 4*SPRITE_SIZE);// o tamanho do boss é 3x4 sprites
    bossTexture = LoadTextureFromImage(img_boss);
    //boss dificult
    img_bossDificult = LoadImage("../assets/bossDificult.png");
    ImageResize(&img_bossDificult, 3*SPRITE_SIZE, 4*SPRITE_SIZE);// o tamanho do boss é 3x4 sprites
    bossDificultTexture = LoadTextureFromImage(img_bossDificult);
    //bola de fogo
    img_fireBall = LoadImage("../assets/fireBall.png");
    ImageResize(&img_fireBall, 2*SPRITE_SIZE, 2*SPRITE_SIZE); // o tamanho do boss é 2x3 sprites
    fireBallTexture = LoadTextureFromImage(img_fireBall);
    //bola de fogo azul
    img_fireBallBlue = LoadImage("../assets/fireBallAzul.png");
    ImageResize(&img_fireBallBlue, 2*SPRITE_SIZE, 2*SPRITE_SIZE); // o tamanho do boss é 2x3 sprites
    fireBallBlueTexture = LoadTextureFromImage(img_fireBallBlue);
    //fontes
    //fontBm = LoadFont("resources/pixantiqua.fnt");
    //fontTtf = LoadFontEx("resources/pixantiqua.ttf", 32, 0, 2SPRITE_SIZE);
    //SetTextLineSpacing(16);
    BackGround = LoadImage("../assets/background.png");
    ImageResize(&BackGround, LARGURA, ALTURA);
    BackGroundTexture = LoadTextureFromImage(BackGround);
}
void unloadTextures()
{
    UnloadImage(img_sword);
    UnloadImage(img_life);
    /*UnloadImage(img_playerE);
    UnloadImage(img_playerN);
    UnloadImage(img_playerS);
    UnloadImage(img_playerW);*/
    UnloadImage(img_wall);
    UnloadImage(img_monsterE);
    UnloadImage(img_monsterN);
    UnloadImage(img_monsterS);
    UnloadImage(img_monsterW);
    UnloadImage(img_conf1);
    UnloadImage(img_conf2);
    //Fontes
    //UnloadFont(fontBm);
    //UnloadFont(fontTtf);
    //Texturas
    UnloadTexture(swordTexture);
    UnloadTexture(lifeTexture);
    /*UnloadTexture(playerETexture);
    UnloadTexture(playerNTexture);
    UnloadTexture(playerSTexture);
    UnloadTexture(playerWTexture);*/
    UnloadTexture(monsterETexture);
    UnloadTexture(monsterNTexture);
    UnloadTexture(monsterSTexture);
    UnloadTexture(monsterWTexture);
    UnloadTexture(BackGroundTexture);
    UnloadTexture(wallTexture);
    UnloadTexture(confettis[0]);
    UnloadTexture(confettis[1]);
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
    if(TopBarStatus.sword){
        DrawTexture(swordTexture, 1100 , 5, WHITE);
    }
}
void generateArrayMap(char path[20], int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT])
{
    int i, j;
    char  item;
    FILE *map = fopen(path, "r");
    for(i = 0; i < 16; i++){
        for(j = 0; j < SPRITE_WIDHT; j++){
            item = (char)fgetc(map);
            if(item == 'P'){
                MapArray[i][j] = 1;
            }else{
                MapArray[i][j] = 0;
            }
        }
    }
}
void generateMap(char path[20], int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame, fireBall fireBalls[5])
{
    int i, j, lifes = 0, monsters = 0, x, y, k;
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
                y = i*SPRITE_SIZE + 60;//+ 60 da barra de status
                switch(item){
                    case 'J':
                        InGame->atualPlayer.x = x;
                        InGame->atualPlayer.y = y;
                        InGame->atualPlayer.orientation = 1;
                        InGame->atualPlayer.imune = 0;
                        break;
                    case 'V':
                        InGame->lifes[lifes].x = x;
                        InGame->lifes[lifes].y = y;
                        InGame->lifes[lifes].alive = 1;
                        lifes++;
                        break;
                    case 'M':
                        InGame->monsters[monsters].x = x;
                        InGame->monsters[monsters].y = y;
                        InGame->monsters[monsters].score = rand()%(100 + 1);
                        InGame->monsters[monsters].alive = 1;
                        InGame->monsters[monsters].orientation = 1;
                        monsters++;
                        break;
                    case 'E':
                        InGame->atualSword.x = x;
                        InGame->atualSword.y = y;
                        InGame->atualSword.alive = 1;
                        break;
                    case 'B':
                        InGame->bossBill.attack = 3;
                        InGame->bossBill.lifes = MAX_LIFES_BOSS;
                        InGame->bossBill.x = x;
                        InGame->bossBill.y = y;
                        InGame->bossBill.orientation = 0;
                        /*for(k = 0; k < 5; k++){
                            fireBalls[i].exist = 0;
                            fireBalls[i].x = -50;
                            fireBalls[i].y = -50;
                        }*/
                }
            }
            x = 0;
            y = 0;
        }
    }
    InGame->monsters[0].qnt = monsters;
}
int menu(int gameInProgress, player *gamePlayer)
{
    char text[40], *optionsText[5];
    int optionSelected, i, draw;
    optionSelected = 0;
    draw = 1;
    if(gameInProgress){
        optionsText[0] = "Continuar Jogo";
        optionsText[1] = "Voltar ao menu";
        optionsText[2] = "Personagem";
        optionsText[3] = "Salvar jogo";
        optionsText[4] = "Sair";
    } else {
        optionsText[0] = "Iniciar";
        optionsText[1] = "Scoreboard";
        optionsText[2] = "Personagem";
        optionsText[3] = "Carregar jogo";
        optionsText[4] = "Sair";
    }

    InitWindow(LARGURA, ALTURA, "Menu");
    generateTextures();
    SetTargetFPS(60);
    while(draw){
        DrawText("ZINF", 100, 20, 100, WHITE);
        for(i = 0; i < 5; i++){
            if(optionSelected == i){
                DrawCircle(90, i*110 + 220, 5, RED);
                DrawText(optionsText[i], 100, i*110 + 200, SPRITE_SIZE, RED);
            } else {
                DrawText(optionsText[i], 100, i*110 + 200, SPRITE_SIZE, WHITE);
            }
        }
        DrawTexture(arrayTexturesPlayer[gamePlayer->person][0], 800, 440, WHITE);
        if((IsKeyPressed(KEY_LEFT)||IsKeyPressed(KEY_RIGHT))&&(optionSelected == 2)&&!gameInProgress){
            if(gamePlayer->person == 1){
                gamePlayer->person = 0;
            } else {
                gamePlayer->person = 1;
            }
        }
        if(IsKeyPressed(KEY_DOWN)){
            if(optionSelected == 4){
                optionSelected = 0;
            } else {
                optionSelected++;
            }
        }
        if(IsKeyPressed(KEY_UP)){
            if(optionSelected == 0){
                optionSelected = 4;
            } else {
                optionSelected--;
            }
        }
        BeginDrawing();
	    EndDrawing();
	    ClearBackground(BLACK);
	    if(IsKeyPressed(KEY_ENTER)&&optionSelected!=2){
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
        DrawTexture(bossTexture, 800, 330, WHITE);
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
	    if(IsKeyPressed(KEY_ENTER)){
            draw = 0;
            CloseWindow();
	    }
    }
    return optionSelected;
}
void restartStatus(int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame, fireBall fireBalls[5], int *imune_muahaha)
{
    InGame->atualStatus.lifes = 3;
    InGame->atualStatus.level = 1;
    InGame->atualStatus.score = 0;
    InGame-> atualStatus.sword = 0;
    generateMap("../assets/mapa01.txt", MapArray, InGame, fireBalls);
    InGame->bossBill.lifes = 0;
    *imune_muahaha = 0;
}
void killMonster(game *InGame,  int monster)
{
    int monsterScore;
    monsterScore = InGame->monsters[monster].score;
    InGame->atualStatus.score += monsterScore;
    InGame->monsters[monster].alive = 0;
}
void drawPlayer(player atualPlayer, int counter)
{
    if((!atualPlayer.imune)||(counter%4 == 0)){
        DrawTexture(arrayTexturesPlayer[atualPlayer.person][atualPlayer.orientation - 1], atualPlayer.x, atualPlayer.y, WHITE);
    }
}
void genarateWall(int matriz[SPRITE_HEIGHT][SPRITE_WIDHT])
{
    int i, j;
    for(i = 0; i < 16; i++){
        for(j = 0; j < SPRITE_WIDHT; j++){
            if(matriz[i][j]){
                DrawTexture(wallTexture, j*SPRITE_SIZE - 20, i*SPRITE_SIZE + 60 - 20, WHITE);
            }
        }
    }
}
int allMonstersKilled(monster monsters[MAX_MONSTERS])
{
    int i;
    for(i = 0; i < monsters[0].qnt; i++){
        if(monsters[i].alive){
            return 0;
        }
    }
    return 1;
}
int nextLevel(status *atualStatus, char file[20], int *muahaha, char test[8])
{
    int i;
    atualStatus->level += 1;
    if(atualStatus->level <= 9){
        sprintf(file, "../assets/mapa0%d.txt", atualStatus->level);
    } else {
        sprintf(file, "../assets/mapa%d.txt", atualStatus->level);
    }
    atualStatus->sword = 0;
    *muahaha = 0;
    for(i=0;i<8;i++){
        test[i] = 0;
    }
    return FileExists(file);
}
int checkPosition(int x, int y, int matriz[SPRITE_HEIGHT][SPRITE_WIDHT])
{
    if((!matriz[(int) floor((y- 60)/SPRITE_SIZE)][(int) floor((x)/SPRITE_SIZE)])&&(x < 1200)&&(x > -SPRITE_SIZE)&&(y < 860)&&(y > 10)){
        return 1;
	} else {
        return 0;
	}
}
int existMonster(game *InGame, int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT])
{
    int i, x, y, x_monster, y_monster, y_max, y_min, x_max, x_min, orientation;
    orientation =InGame->atualPlayer.orientation;
    x = InGame->atualPlayer.x;
    y = InGame->atualPlayer.y;
    x_max = InGame->atualPlayer.x + 3*SPRITE_SIZE;
    x_min = InGame->atualPlayer.x - 3*SPRITE_SIZE;
    y_max = InGame->atualPlayer.y + 3*SPRITE_SIZE;
    y_min = InGame->atualPlayer.y - 3*SPRITE_SIZE;
    for(i = 0; i < MAX_MONSTERS; i++){
        if(InGame->monsters[i].alive){
            x_monster = InGame->monsters[i].x;
            y_monster = InGame->monsters[i].y;
             switch(orientation){
                 case 1:
                     if(((x_monster <= x_max)&&(x_monster >= x))&&(y == y_monster)){
                          if((x_monster - x == SPRITE_SIZE || x == x_monster) || (x_monster - x == 2*SPRITE_SIZE && checkPosition(x + SPRITE_SIZE, y, MapArray)) || (x_monster - x == 3*SPRITE_SIZE && checkPosition(x + SPRITE_SIZE, y, MapArray) && checkPosition(x + 2*SPRITE_SIZE, y, MapArray)))
                              return i;
                     }
                     break;
                 case 2:
                     if(((x_monster >= x_min)&&(x_monster <= x))&&(y == y_monster)){
                          if((x_monster - x == -SPRITE_SIZE || x == x_monster) || (x_monster - x == -2*SPRITE_SIZE && checkPosition(x - SPRITE_SIZE, y, MapArray)) || (x_monster - x == -3*SPRITE_SIZE && checkPosition(x - SPRITE_SIZE, y, MapArray) && checkPosition(x - 2*SPRITE_SIZE, y, MapArray)))
                              return i;
                     }
                     break;
                 case 3:
                     if(((y_monster >= y_min)&&(y_monster <= y))&&(x == x_monster)){
                          if((y_monster - y == -SPRITE_SIZE || y == y_monster) || (y_monster - y == -2*SPRITE_SIZE && checkPosition(x, y - SPRITE_SIZE, MapArray)) || (y_monster - y == -3*SPRITE_SIZE && checkPosition(x, y - SPRITE_SIZE, MapArray) && checkPosition(x, y - 2*SPRITE_SIZE, MapArray)))
                              return i;
                     }
                     break;
                 default:
                     if(((y_monster <= y_max)&&(y_monster >= y))&&(x == x_monster)){
                          if((y_monster - y == SPRITE_SIZE || y == y_monster) || (y_monster - y == 2*SPRITE_SIZE && checkPosition(x, y + SPRITE_SIZE, MapArray)) || (y_monster - y == 3*SPRITE_SIZE && checkPosition(x, y + SPRITE_SIZE, MapArray) && checkPosition(x, y + 2*SPRITE_SIZE, MapArray)))
                              return i;
                     }
             }
            //if((y_monster <= y_max)&&(y_monster >= y_min)&&(x_monster >= x_min)&&(x_monster <= x_max)){
            //    return i;
            //}
        }
    }
    return -1;
}
void changeLife(status *lifeStatus, int value)
{
    lifeStatus->lifes += value;
}
int attackMonster(game *InGame)
{
    int i;
    for(i = 0; i < MAX_MONSTERS; i++){
        if((InGame->atualPlayer.x == InGame->monsters[i].x)&&(InGame->atualPlayer.y == InGame->monsters[i].y)&&(InGame->monsters[i].alive)){
            changeLife(&InGame->atualStatus, -1);
            return 1;
        }
    }
    return 0;
}
void chatchSword(game *InGame)
{
    InGame->atualStatus.sword = 1;
    InGame->atualSword.alive = 0;
}
void drawSword(sword *atualSword)
{
    if(atualSword->alive){
        DrawTexture(swordTexture, atualSword->x, atualSword->y, WHITE);
    }
}

void bossDificultMode(boss *bossBill)
{
    bossBill->attack = 5;
}
void killBoss(game *InGame)
{
    int x_max, x_min, y_max, y_min, y_monster, x_monster;
    if(InGame->bossBill.lifes != 0){
        x_max = InGame->atualPlayer.x + 3*SPRITE_SIZE;
        x_min = InGame->atualPlayer.x - 3*SPRITE_SIZE;
        y_max = InGame->atualPlayer.y + 3*SPRITE_SIZE;
        y_min = InGame->atualPlayer.y - 3*SPRITE_SIZE;
        y_monster = InGame->bossBill.y;
        x_monster = InGame->bossBill.x;
            // switch(orientation){
            //     case 1:
            //         x += 3*SPRITE_SIZE;//tres blocos de ataque
            //         if(((x_monster <= x)&&(x_monster >= x_player))&&(y == y_monster)){
            //             return i;
            //         }
            //         break;
            //     case 2:
            //         x -= 3*SPRITE_SIZE;
            //         if(((x_monster >= x)&&(x_monster <= x_player))&&(y == y_monster)){
            //             return i;
            //         }
            //         break;
            //     case 3:
            //         y -= 2*SPRITE_SIZE;
            //         if(((y_monster >= y)&&(y_monster <= y_player))&&(x == x_monster)){
            //             return i;
            //         }
            //         break;
            //     default:
            //         y += 2*SPRITE_SIZE;
            //         if(((y_monster <= y)&&(y_monster >= y_player))&&(x == x_monster)){
            //             return i;
            //         }
            // }
        if((y_monster <= y_max)&&(y_monster >= y_min)&&(x_monster >= x_min)&&(x_monster <= x_max)){
            InGame->bossBill.lifes--;
            if(InGame->bossBill.lifes == 7){
                bossDificultMode(&InGame->bossBill);
            }
        }
    }

}
int fireBallsMove(boss *bossBill, fireBall fireBalls[5], int *counter, int mapArray[SPRITE_HEIGHT][SPRITE_WIDHT], player atualPlayer, int imune_muahaha)
{
    int new_counter, i, x_player, y_player;
    x_player = atualPlayer.x;
    y_player = atualPlayer.y;
    if(bossBill->lifes != 0){
        for(i = 0; i < bossBill->attack; i++){
            //printf("\n\n\n%d", fireBalls[i].exist);
            if(fireBalls[i].exist == 1){
                //printf("\n\n\n%d %d %d %d", fireBalls[i].x, fireBalls[i].y, i, fireBalls[i].exist);
                if(bossBill->attack == 3)
                    DrawTexture(fireBallTexture, fireBalls[i].x, fireBalls[i].y +20, WHITE);
                else
                    DrawTexture(fireBallBlueTexture, fireBalls[i].x, fireBalls[i].y +20, WHITE);
            }
        }
        if(*counter == 8 - bossBill->attack){ //8 - 3(bolas de fogo pro vez) para quando ele esta no modo normal e 8 - 5 quando esta no modo difcil diminuindo o tempo do contador para o boss fazer a acao ele fica mais rapido e as bolas de fogo sao geradas mais rapidamente
            new_counter = 0;
            for(i = 0; i < bossBill->attack; i++){
                if(fireBalls[i].exist == 1){
                    if(checkPosition(fireBalls[i].x -50, fireBalls[i].y, mapArray)){
                        fireBalls[i].x -= 50;
                    } else {
                        fireBalls[i].exist = 0;
                    }
                    if(!atualPlayer.imune && !imune_muahaha){
                        if(((fireBalls[i].x + 100 >= x_player)&&(fireBalls[i].x <= x_player))&&((fireBalls[i].y + 50 >= y_player)&&(fireBalls[i].y <= y_player))){
                            fireBalls[i].exist = 0;
                            return 1;
                        }
                    }
                }
            }
        } else {
            new_counter = *counter + 1;
        }
    }
    return 0;
}
int attackContactBoss(game *InGame)
{
    if((InGame->atualPlayer.x >= InGame->bossBill.x)&&((InGame->atualPlayer.y == InGame->bossBill.y) || (InGame->atualPlayer.y == InGame->bossBill.y + SPRITE_SIZE) || (InGame->atualPlayer.y == InGame->bossBill.y + 2*SPRITE_SIZE))&&(InGame->bossBill.lifes > 0)){
        if(InGame->bossBill.attack == 3)
           changeLife(&InGame->atualStatus, -2);
        else
           changeLife(&InGame->atualStatus, -3);
        return 1;
    }
    else{
    return 0;
    }
}
void attackBoss(boss *bossBill, int *counter, fireBall fireBalls[5])
{
    int new_counter, i;
    if(bossBill->lifes != 0){
        if(*counter == 8 - bossBill->attack){ //8 - 3(bolas de fogo pro vez) para quando ele esta no modo normal e 8 - 5 quando esta no modo difcil diminuindo o tempo do contador para o boss fazer a acao ele fica mais rapido e as bolas de fogo sao geradas mais rapidamente
            for(i = 0; i < bossBill->attack; i++){
                if(fireBalls[i].exist != 1){
                    fireBalls[i].exist = 1;
                    fireBalls[i].x = bossBill->x;
                    fireBalls[i].y = bossBill->y;
                    break;
                }
            }
            new_counter = 0;
        } else {
            new_counter = *counter + 1;
        }
    }
    //*counter = new_counter;
}

void drawBoss(boss *bossBill, int *counter)
{
    int new_counter;
    if(bossBill->lifes != 0){
        DrawRectangleLines(bossBill->x - 5 - 2, bossBill->y - 5 - 2, MAX_LIFES_BOSS*10 +2,  20 + 2, RED);
        DrawRectangle(bossBill->x - 5, bossBill->y - 5, bossBill->lifes*10, 20, RED);
        if(bossBill->attack == 5){
            DrawTexture(bossDificultTexture, bossBill->x, bossBill->y, WHITE);
        } else {
            DrawTexture(bossTexture, bossBill->x, bossBill->y, WHITE);
        }

        //movimentacao
        if(*counter == 8 - bossBill->attack){//8 - 3(bolas de fogo pro vez) para quando ele esta no modo normal e 8 - 5 quando esta no modo difcil diminuindo o tempo do contador para o boss fazer a acao ele fica mais rapido e as bolas de fogo sao geradas mais rapidamente
            if(bossBill->orientation){
                bossBill->y += 50;
            } else {
                bossBill->y -= 50;
            }
            new_counter = 0;
        } else {
            new_counter = *counter + 1;
        }
        if(bossBill->y <= 60){//60 da barra de status -  tamanho do boss
            bossBill->orientation = 1;
        } else if(bossBill->y >= ALTURA - 3*SPRITE_SIZE - 60) { // altura da tela + 60 da barra de status
            bossBill->orientation = 0;
        }
        *counter = new_counter;
    }
}
void drawMonsters(monster monsters[MAX_MONSTERS], int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT])
{
    int i, randow, move, x, y;
    for(i = 0; i < monsters[0].qnt; i++){
        if(monsters[i].alive){
            x = monsters[i].x;
            y = monsters[i].y;
            DrawTexture(arrayTexturesMonster[monsters[i].orientation - 1], x, y, WHITE);
            randow = rand()%(2);
            if(randow == 1){
                move = monsters[i].orientation;
            } else{
                move = rand()%(4) + 1;
            }
            randow = rand()%(8 + 1);
            if(randow == 1){
                monsters[i].orientation = move;
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
            if(checkPosition(x, y, MapArray)){
                monsters[i].x = x;
                monsters[i].y = y;
            }
            else do{
                switch(move){
                case 1:
                    x -= SPRITE_SIZE;
                    break;
                case 2:
                    x += SPRITE_SIZE;
                    break;
                case 3:
                    y -= SPRITE_SIZE;
                    break;
                case 4:
                    y += SPRITE_SIZE;
                }
                if(move == 1){
                    move = 4;
                }
                else if(move == 2){
                    move = 3;
                }
                else if(move == 3){
                    move = 1;
                }
                else{
                    move = 2;
                }
                monsters[i].orientation = move;
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
                if(checkPosition(x, y, MapArray)){
                    monsters[i].x = x;
                    monsters[i].y = y;
                }
            }while(!checkPosition(x, y, MapArray));
        }
    }
}

void drawLifes(life lifes[MAX_LIFES])
{
    int i;
    for(i = 0; i < 5; i++){
        if(lifes[i].alive){
            DrawTexture(lifeTexture, lifes[i].x, lifes[i].y, WHITE);
        }
    }
}
void drawConfetti(int indconf)
{
    DrawTexture(confettis[indconf], 1000, 150, WHITE);
}
int winGame()
{
    char *optionsText[3];
    int optionSelected, i, draw, MenuAnswer, indconf, randow;
    optionSelected = 0;
    draw = 1;
    optionsText[0] = "Jogar Novamente";
    optionsText[1] = "Voltar ao menu";
    optionsText[2] = "Sair";
    InitWindow(LARGURA, ALTURA, "PARABEEENS");
    generateTextures();
    SetTargetFPS(60);
    indconf = 0;
    randow = 0;
    while(draw){
        DrawText("VOCE GANHOUU!!!!", 100, 20, 100, WHITE);
        if(randow == 60){
            if(indconf == 0){
                indconf = 1;
            } else if(indconf == 1){
                indconf = 0;
            } else {
                indconf++;
            }
            randow = 0;
        } else{
            randow++;
        }
        drawConfetti(indconf);
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
void showHighScores(score highscores[5])
{
    char scoreString[20];
    int i, draw;
    draw = 1;
    InitWindow(LARGURA, ALTURA, "HIGHSCORES");
    generateTextures();
    SetTargetFPS(60);
    while(draw){
        DrawText("Lista dos highscores:", 100, 20, 80, WHITE);
        for(i = 0; i < 5; i++){
            sprintf(scoreString, "%d", highscores[i].score);
            DrawText(highscores[i].name, 100, i*80 + 200, SPRITE_SIZE, WHITE);
            DrawText(scoreString, 500, i*80 + 200, SPRITE_SIZE, WHITE);
        }
        DrawCircle(90, 625, 5, RED);
        DrawText("Voltar", 100, 600, SPRITE_SIZE, RED);
        BeginDrawing();
	    EndDrawing();
	    ClearBackground(BLACK);
	    if(IsKeyPressed(KEY_ENTER)){
            draw = 0;
            CloseWindow();
	    }
    }
}
void saveGame(save saveSave, game *InGame)
{
    printf("%s\n", saveSave.path);
    FILE *saveFileSave = fopen(saveSave.path, "wb");
    fwrite(InGame, sizeof(game), 1, saveFileSave);
    fclose(saveFileSave);
}
void loadGame(save loadSave, int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame)
{
    FILE *loadFileSave = fopen(loadSave.path, "rb");
    char atualFile[20];
    fread(InGame, sizeof(game), 1, loadFileSave);
    sprintf(atualFile, "../assets/mapa0%d.txt", InGame->atualStatus.level);
    generateArrayMap(atualFile, MapArray);
    fclose(loadFileSave);
}
void saves(int option, int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame)//option pode ser 0, para salvar o jogo, ou 1 para carregar o jogo
{
    FILE *file_saves = fopen("../assets/saves/saves.bin", "rb");
    save savesList[3];
    int draw = 1, i, optionSelected = 0, index;
    char text[20], optionsText[4][40];
    if(option){
        strcpy(text, "Carregar jogo");
    } else {
        strcpy(text, "Salvar jogo");
    }
    for(i = 0; i < 3; i++){
        fread(&savesList[i], sizeof(save), 1, file_saves);
        sprintf(optionsText[i], "Save %d da data: %s", i + 1, savesList[i].date);
    }
    fclose(file_saves);
    strcpy(optionsText[3], "Voltar");
    InitWindow(LARGURA, ALTURA, text);
    generateTextures();
    SetTargetFPS(60);
    while(draw){
        DrawText(text, 100, 20, 80, WHITE);
        for(i = 0; i < 4; i++){
            if(optionSelected == i){
                DrawCircle(90, i*110 + 220, 5, RED);
                DrawText(optionsText[i], 100, i*110 + 200, SPRITE_SIZE, RED);
                if(optionSelected != 3){
                    DrawText(text, 100, i*110 + 200 + 50, SPRITE_SIZE/2, RED);
                }
            } else {
                DrawText(optionsText[i], 100, i*110 + 200, SPRITE_SIZE, WHITE);
            }
        }
        if(IsKeyPressed(KEY_DOWN)){
            if(optionSelected == 3){
                optionSelected = 0;
            } else {
                optionSelected++;
            }
        }
        if(IsKeyPressed(KEY_UP)){
            if(optionSelected == 0){
                optionSelected = 3;
            } else {
                optionSelected--;
            }
        }
        BeginDrawing();
	    EndDrawing();
	    ClearBackground(BLACK);
	    if(IsKeyPressed(KEY_ENTER)){
            if(optionSelected != 3){
                if(option){
                    loadGame(savesList[optionSelected], MapArray, InGame);
                } else {
                    time_t rawtime;
                    time(&rawtime);
                    struct tm *current_info = localtime(&rawtime);
                    strftime(savesList[optionSelected].date, sizeof(savesList[optionSelected].date), "%d/%m/%Y %H:%M:%S", current_info);
                    FILE *file_saves = fopen("../assets/saves/saves.bin", "wb");
                    if(file_saves == NULL){
                        printf("FALHOU\n\n\n");
                    }
                    savesList[optionSelected].index = optionSelected + 1;
                    sprintf(savesList[optionSelected].path, "../assets/saves/save%d.bin", savesList[optionSelected].index);
                    for(i = 0; i < 3; i++){
                        fwrite(&savesList[i], sizeof(save), 1, file_saves);
                    }
                    fclose(file_saves);
                    saveGame(savesList[optionSelected], InGame);
                }
            }
            draw = 0;
            CloseWindow();
	    }
    }
}
int callMenu(int gameInProgress, int *continueGame, score highscores[5], int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame)
{
    int MenuAswer;
    MenuAswer = menu(gameInProgress, &InGame->atualPlayer);
    if(gameInProgress){
        if(MenuAswer == 1){
            return callMenu(0, continueGame, highscores, MapArray, InGame);
        } else if(MenuAswer == 4){
            *continueGame = 0;
        } else if(MenuAswer == 3){
            saves(0, MapArray, InGame);
            return callMenu(1, continueGame, highscores, MapArray, InGame);
        }
    } else {
        if(MenuAswer == 0){
            return 1; //precisa (re)comecar o jogo
        } else if(MenuAswer == 1){
            showHighScores(highscores);
            return callMenu(gameInProgress, continueGame, highscores, MapArray, InGame);
        } else if(MenuAswer == 4){
            *continueGame = 0; // sair do jogo
        } else if(MenuAswer == 3){
            saves(1, MapArray, InGame);
        }
    }
    return 0;
}
void readHighscores(score highscores[5])
{
    score generateScore;
    int i, score;
    char line[20];
    FILE *FHighscores = fopen("../assets/highscores.txt", "r");
    for(i = 0; i < 5; i++){
        fgets(line, 20, FHighscores);
        strcpy(generateScore.name, line);
        fgets(line, 20, FHighscores);
        score = atoi(line);
        generateScore.score = score;
        highscores[i] = generateScore;
    }
    fclose(FHighscores);
}
int updateScores(score highscores[5], score new_score)
{
    int i, removedI, changed;
    char strScore[20];
    FILE *FHighscores = fopen("../assets/highscores.txt", "w");
    score removed_score, med_score;
    removedI = 5;
    changed = 0;
    for(i = 0; i < 5; i++){
        if(new_score.score > highscores[i].score){
            removed_score = highscores[i];
            highscores[i] = new_score;
            removedI = i;
            changed = 1;
            break;
        }
    }
    while(removedI < 4){
        for(i = removedI + 1; i < 5; i++){
            if(removed_score.score > highscores[i].score){
                printf("\nNome: %s\n", highscores[i].name);
                printf("\nScore: %d\n", highscores[i].score);
                med_score = highscores[i];
                highscores[i] = removed_score;
                removed_score = med_score;
                removedI = i;
            }
        }
    }
    for(i = 0; i < 5; i++){
        highscores[i].name[strcspn(highscores[i].name, "\n")] = '\0';
        fprintf(FHighscores, highscores[i].name);
        fprintf(FHighscores, "\n");
        sprintf(strScore, "%d", highscores[i].score);
        fprintf(FHighscores, strScore);
        fprintf(FHighscores, "\n");
    }
    fclose(FHighscores);
    return changed;
}
void newScore(score highscores[5], int playerScore)
{
    score new_score;
    char scoreString[20], name[20] = "\0";
    int i, draw, letterCount = 0, key, nameEntered = 0, updated, randow = 0, indconf = 0;
    draw = 1;
    InitWindow(LARGURA, ALTURA, "Digite seu nome");
    SetTargetFPS(60);
    while(!nameEntered){
        DrawText("Digite seu nome:", 100, 20, 100, WHITE);
        key = GetCharPressed();
        while (key > 0){
            if (((key >= 32) && (key <= 125)) && (letterCount < 20)){
                name[letterCount] = (char)key;
                letterCount++;
                name[letterCount] = '\0';  // Garante fim de string
            }
            key = GetCharPressed();  // Continua lendo se houve mais de um char
        }
        if (IsKeyPressed(KEY_BACKSPACE)){
            if (letterCount > 0){
                letterCount--;
                name[letterCount] = '\0';
            }
        }
        DrawRectangle(100, 150, 300, 50, LIGHTGRAY);
        DrawText(name, 105, 150, 40, BLACK);
        if (((GetTime() * 2) - (int)(GetTime() * 2)) < 0.5 && letterCount < 40)
            DrawText("_", 105 + MeasureText(name, 40), 170, 35, BLACK);
        BeginDrawing();
        EndDrawing();
        ClearBackground(BLACK);
        if(IsKeyPressed(KEY_ENTER)){
            nameEntered = 1;
            CloseWindow();
        }
    }
    strcpy(new_score.name, name);
    new_score.score = playerScore;
    updated = updateScores(highscores, new_score);

    InitWindow(LARGURA, ALTURA, "Escore atulizado");
    generateTextures();
    SetTargetFPS(60);
    while(draw&&!WindowShouldClose()){
        if(updated){
            DrawText("Voce conseguiu um novo recorde!!", 100, 40, 50, GREEN);
            if(randow == 60){
                if(indconf == 0){
                    indconf = 1;
                } else if(indconf == 1){
                    indconf = 0;
                } else {
                    indconf++;
                }
                randow = 0;
            } else{
                randow++;
            }
            drawConfetti(indconf);
        } else{
            DrawText("Puxa! Voce não conseguiu nenhum novo recorde", 100, 40, 50, RED);
        }
        DrawText("Voltar", 100, 300, 50, RED);
        BeginDrawing();
        EndDrawing();
        ClearBackground(BLACK);
        if(IsKeyPressed(KEY_ENTER)){
            draw = 0;
            CloseWindow();
        }
    }

}
void muahaha(int *imune_muahaha, char test[8])
{
    int i = 0;
    char muahaha[8] = {'M','U','A','H','A','H','A','\0'}, current, read;
    current = GetKeyPressed();
    if(current != 0){
        for(i=0;i<7;i++){
            if(i==6){
                test[6] = current;
            }
            else{
                test[i] = test [i+1];
            }
        }
    }
    if(strcmp(test, muahaha) == 0){
        *imune_muahaha = 1;
    }
}
void StartGame()
{
    status InGameStatus;
    game InGame;
    monster monsters[MAX_MONSTERS];
    score Highscores[5];
    fireBall fireBalls[5];
    boss bossBill;
    player atualPlayer;
    sword atualSword;
    life lifes[MAX_LIFES];
    int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], i, j, gameOption, continueGame = 1, MenuAnswer, contador = 0, x_player, y_player, orientation = 1, monsterKilled, respostaMenu, bossCounter = 0, imune_muahaha = 0;
    char atualFile[20], test[8] = {0,0,0,0,0,0,0,'\0'};

    InGame.atualPlayer = atualPlayer;
    InGame.atualStatus = InGameStatus;
    memcpy(InGame.monsters, monsters, sizeof(monster) * MAX_MONSTERS);
    InGame.atualSword = atualSword;
    memcpy(InGame.lifes, lifes, sizeof(life) * MAX_LIFES);
    InGame.bossBill = bossBill;

    srand(time(NULL));

    InGame.atualPlayer.person = 0;
    readHighscores(Highscores);
    restartStatus(MapArray, &InGame, fireBalls, &imune_muahaha);
    callMenu(0, &continueGame, Highscores, MapArray, &InGame);
    while(continueGame){
        readHighscores(Highscores);
        InitWindow(LARGURA, ALTURA, "ZINF"); //Inicializa janela, com certo tamanho e titulo
        generateTextures();
        SetTargetFPS(20);// Ajusta a janela para 20 frames por segundo
        while (!WindowShouldClose())
        {
            DrawTexture(BackGroundTexture, 0, 0, WHITE);
            x_player = InGame.atualPlayer.x;
            y_player = InGame.atualPlayer.y;
            if (IsKeyPressed(KEY_RIGHT)||IsKeyDown(KEY_RIGHT)||IsKeyPressed(KEY_D)||IsKeyDown(KEY_D)) {
                orientation = 1;
                if(checkPosition((x_player + SPRITE_SIZE), y_player, MapArray)){
                    x_player += SPRITE_SIZE;
                }
            }
            if (IsKeyPressed(KEY_LEFT)||IsKeyDown(KEY_LEFT)||IsKeyPressed(KEY_A)||IsKeyDown(KEY_A)) {
                orientation = 2;
                if(checkPosition((x_player -SPRITE_SIZE), y_player, MapArray)){
                    x_player -= SPRITE_SIZE;
                }
            }
            if (IsKeyPressed(KEY_UP)||IsKeyDown(KEY_UP)||IsKeyPressed(KEY_W)||IsKeyDown(KEY_W)) {
                orientation = 3;
                if(checkPosition(x_player, (y_player -SPRITE_SIZE), MapArray)){
                    y_player -= SPRITE_SIZE;
                }
            }
            if (IsKeyPressed(KEY_DOWN)||IsKeyDown(KEY_DOWN)||IsKeyPressed(KEY_S)||IsKeyDown(KEY_S)) {
                orientation = 4;
                if(checkPosition(x_player, (y_player + SPRITE_SIZE), MapArray)){
                    y_player += SPRITE_SIZE;
                }
            }
            InGame.atualPlayer.x = x_player;
            InGame.atualPlayer.y = y_player;
            InGame.atualPlayer.orientation = orientation;
            if(IsKeyPressed(KEY_TAB)){
                gameOption = 3;
                break;
            }
            if((InGame.atualSword.alive)&&(InGame.atualSword.x == InGame.atualPlayer.x)&&(InGame.atualSword.y == InGame.atualPlayer.y)){
                chatchSword(&InGame);
            }
            if(InGame.atualStatus.sword){
                if(IsKeyPressed(KEY_J)){
                    monsterKilled = existMonster(&InGame, MapArray);
                    if(monsterKilled > -1){
                        killMonster(&InGame, monsterKilled);
                    }
                    killBoss(&InGame);
                }
            }
            for(i = 0; i < 5; i++){
                if((InGame.lifes[i].alive)&&(InGame.lifes[i].x == InGame.atualPlayer.x)&&(InGame.lifes[i].y== InGame.atualPlayer.y)){
                    InGame.lifes[i].alive = 0;
                    changeLife(&InGame.atualStatus, 1);
                }
            }
            if((allMonstersKilled(InGame.monsters))&&(InGame.bossBill.lifes == 0)){
                if(nextLevel(&InGame.atualStatus, atualFile, &imune_muahaha, test)){
                    generateMap(atualFile, MapArray, &InGame, fireBalls);
                } else{
                    gameOption = 2;
                    break;
                }
            }
            if(InGame.atualStatus.lifes <= 0){
                gameOption = 1;
                break;
            }
            muahaha(&imune_muahaha, test);
            if(!InGame.atualPlayer.imune && !imune_muahaha){
                if(attackMonster(&InGame) || attackContactBoss(&InGame)){
                    InGame.atualPlayer.imune = 1;
                    contador = 0;
                }
            }
            else contador++;
            if(contador > 39)
                InGame.atualPlayer.imune = 0;
            if(fireBallsMove(&InGame.bossBill, fireBalls, &bossCounter, MapArray, InGame.atualPlayer, imune_muahaha)){
                InGame.atualPlayer.imune = 1;
                contador = 0;
                if(InGame.bossBill.attack == 3)
                changeLife(&InGame.atualStatus, -2);
                else
                changeLife(&InGame.atualStatus, -3);
            }
            drawPlayer(InGame.atualPlayer, contador);
            genarateWall(MapArray);
            drawBoss(&InGame.bossBill, &bossCounter);
            attackBoss(&InGame.bossBill, &bossCounter, fireBalls);
            drawMonsters(InGame.monsters, MapArray);
            drawLifes(InGame.lifes);
            drawSword(&InGame.atualSword);
            ShowTopBar(InGame.atualStatus);
            BeginDrawing(); //Inicia o ambiente de desenho na tela
            EndDrawing(); //Finaliza o ambiente de desenho na tela
            ClearBackground(WHITE);
            //ImageClearBackground(&BackGround, WHITE); //n�o consegui utilizar essa fun��o
        }
        CloseWindow();
        switch(gameOption){// 1 -> game over, 2 -> ganhou, 3 -> menu de pause
            case 1:
                MenuAnswer = gameOver();
                if(MenuAnswer == 0){
                    restartStatus(MapArray, &InGame, fireBalls, &imune_muahaha);
                } else if(MenuAnswer == 1){
                    if(callMenu(0, &continueGame, Highscores, MapArray, &InGame)){
                        restartStatus(MapArray, &InGame, fireBalls, &imune_muahaha);
                    }
                } else {
                    continueGame = 0;
                }
                break;
            case 2:
                MenuAnswer = winGame();
                if(MenuAnswer == 0){
                    newScore(Highscores, InGame.atualStatus.score);
                    restartStatus(MapArray, &InGame, fireBalls, &imune_muahaha);
                } else if(MenuAnswer == 1){
                    newScore(Highscores, InGame.atualStatus.score);
                    if(callMenu(0, &continueGame, Highscores, MapArray, &InGame)){
                        restartStatus(MapArray, &InGame, fireBalls, &imune_muahaha);
                    }
                } else {
                    continueGame = 0;
                    newScore(Highscores, InGame.atualStatus.score);
                }
                break;
            case 3:
                if(callMenu(1, &continueGame, Highscores, MapArray, &InGame)){
                    restartStatus(MapArray, &InGame, fireBalls, &imune_muahaha);
                }
        }
    }
    unloadTextures();
    CloseWindow(); // Fecha a janela
}
