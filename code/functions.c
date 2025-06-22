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
#define MAX_LIFES_BOSS 30
//DEFINIDO AT� AQUI




Image img_sword_mabel;
Texture2D swordMabelTexture;
Image img_sword_dipper;
Texture2D swordDipperTexture;
Texture swords[2];
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
//Texturas dos monstros com cada uma das orientacoes
Image img_monster1N;
Texture2D monster1NTexture;
Image img_monster1S;
Texture2D monster1STexture;
Image img_monster1E;
Texture2D monster1ETexture;
Image img_monster1W;
Texture2D monster1WTexture;
Image img_monster2N;
Texture2D monster2NTexture;
Image img_monster2S;
Texture2D monster2STexture;
Image img_monster2E;
Texture2D monster2ETexture;
Image img_monster2W;
Texture2D monster2WTexture;
Image img_monster3N;
Texture2D monster3NTexture;
Image img_monster3S;
Texture2D monster3STexture;
Image img_monster3E;
Texture2D monster3ETexture;
Image img_monster3W;
Texture2D monster3WTexture;
Image img_monster4N;
Texture2D monster4NTexture;
Image img_monster4S;
Texture2D monster4STexture;
Image img_monster4E;
Texture2D monster4ETexture;
Image img_monster4W;
Texture2D monster4WTexture;
Texture2D arrayTexturesMonster[4][4];
//Fundos
Image BackGround;
Texture2D BackGroundTexture;
Image BackGroundGameOver;
Texture2D BackGroundGameOverTexture;
Image BackGroundMenu;
Texture2D BackGroundMenuTexture;
Image BackGroundWinGame;
Texture2D BackGroundWinGameTexture;
Image BackGroundScore;
Texture2D BackGroundScoreTexture;
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
Image iconImage;
//sounds
Music gameMusic;
Music winGameMusic;
Sound lifeSound;
Sound menuSound;
Sound killMonsterSound;
Sound gameOverSound;
Sound damageSound;
Sound nextLevelSound;



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
    int sprite; //um numero que representa o monstro sorteado para ele ser
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
    int person; // player.person 0 para dipper, 1 para mabel
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

void loadSoundsAndMusics()
{
    gameMusic = LoadMusicStream("../assets/sounds/weirdmageddonTheme.mp3");
    winGameMusic = LoadMusicStream("../assets/sounds/themeSong.mp3");
    SetMusicVolume(gameMusic, 0.3);
    lifeSound = LoadSound("../assets/sounds/life.mp3");
    damageSound = LoadSound("../assets/sounds/damage.mp3");
    menuSound = LoadSound("../assets/sounds/menu.wav");
    killMonsterSound = LoadSound("../assets/sounds/killMonster.wav");
    gameOverSound = LoadSound("../assets/sounds/gameOver.mp3");
    nextLevelSound = LoadSound("../assets/sounds/levelPassed.mp3");
}
void unloadSoundsAndMusics()
{
    UnloadMusicStream(gameMusic);
    UnloadMusicStream(winGameMusic);
    UnloadSound(lifeSound);
    UnloadSound(damageSound);
    UnloadSound(menuSound);
    UnloadSound(killMonsterSound);
    UnloadSound(gameOverSound);
    UnloadSound(nextLevelSound);
}

void loadTexturesMenus()
{
    loadSoundsAndMusics();
    iconImage = LoadImage("../assets/icon.png");
    BackGroundGameOver = LoadImage("../assets/background_gameOver.png");
    ImageResize(&BackGroundGameOver, LARGURA, ALTURA);
    BackGroundGameOverTexture = LoadTextureFromImage(BackGroundGameOver);
    BackGroundMenu = LoadImage("../assets/background_menu.png");
    ImageResize(&BackGroundMenu, LARGURA, ALTURA);
    BackGroundMenuTexture = LoadTextureFromImage(BackGroundMenu);
    BackGroundWinGame = LoadImage("../assets/background_wingame.png");
    ImageResize(&BackGroundWinGame, LARGURA, ALTURA);
    BackGroundWinGameTexture = LoadTextureFromImage(BackGroundWinGame);
    BackGroundScore = LoadImage("../assets/background_score.png");
    ImageResize(&BackGroundScore, LARGURA, ALTURA);
    BackGroundScoreTexture = LoadTextureFromImage(BackGroundScore);
    //confetes
    img_conf1 = LoadImage("../assets/confete1.png");
    img_conf2 = LoadImage("../assets/confete2.png");
    ImageResize(&img_conf1, 3*SPRITE_SIZE, 3*SPRITE_SIZE);
    ImageResize(&img_conf2, 3*SPRITE_SIZE, 3*SPRITE_SIZE);
    confettis[0] = LoadTextureFromImage(img_conf1);
    confettis[1] = LoadTextureFromImage(img_conf2);
}
void generateTextures()
{
    loadTexturesMenus();
    loadSoundsAndMusics();
    img_sword_mabel = LoadImage("../assets/swordMabel.png");
    ImageResize(&img_sword_mabel, SPRITE_SIZE, SPRITE_SIZE);
    swordMabelTexture = LoadTextureFromImage(img_sword_mabel);
    img_sword_dipper = LoadImage("../assets/swordDipper1.png");
    ImageResize(&img_sword_dipper, SPRITE_SIZE, SPRITE_SIZE);
    swordDipperTexture = LoadTextureFromImage(img_sword_dipper);
    swords[0] = swordDipperTexture;
    swords[1] = swordMabelTexture;
    img_life = LoadImage("../assets/life.png");
    ImageResize(&img_life, SPRITE_SIZE, SPRITE_SIZE);
    lifeTexture = LoadTextureFromImage(img_life);
    //texturas do player
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
    //texturas dos monstros
    //norte
    img_monster1N = LoadImage("../assets/monster1N.png");
    ImageResize(&img_monster1N, SPRITE_SIZE, SPRITE_SIZE);
    monster1NTexture = LoadTextureFromImage(img_monster1N);
    //leste
    img_monster1E = LoadImage("../assets/monster1E.png");
    ImageResize(&img_monster1E, SPRITE_SIZE, SPRITE_SIZE);
    monster1ETexture = LoadTextureFromImage(img_monster1E);
    //sul
    img_monster1S = LoadImage("../assets/monster1S.png");
    ImageResize(&img_monster1S, SPRITE_SIZE, SPRITE_SIZE);
    monster1STexture = LoadTextureFromImage(img_monster1S);
    //oeste
    img_monster1W = LoadImage("../assets/monster1W.png");
    ImageResize(&img_monster1W, SPRITE_SIZE, SPRITE_SIZE);
    monster1WTexture = LoadTextureFromImage(img_monster1W);
    arrayTexturesMonster[0][0] = monster1ETexture;
    arrayTexturesMonster[0][1] = monster1WTexture;
    arrayTexturesMonster[0][2] = monster1STexture;
    arrayTexturesMonster[0][3] = monster1NTexture;
    //norte
    img_monster2N = LoadImage("../assets/monster2N.png");
    ImageResize(&img_monster2N, 1.2*SPRITE_SIZE, 1.2*SPRITE_SIZE);
    monster2NTexture = LoadTextureFromImage(img_monster2N);
    //leste
    img_monster2E = LoadImage("../assets/monster2E.png");
    ImageResize(&img_monster2E, 1.2*SPRITE_SIZE, 1.2*SPRITE_SIZE);
    monster2ETexture = LoadTextureFromImage(img_monster2E);
    //sul
    img_monster2S = LoadImage("../assets/monster2S.png");
    ImageResize(&img_monster2S, 1.2*SPRITE_SIZE, 1.2*SPRITE_SIZE);
    monster2STexture = LoadTextureFromImage(img_monster2S);
    //oeste
    img_monster2W = LoadImage("../assets/monster2W.png");
    ImageResize(&img_monster2W, 1.2*SPRITE_SIZE, 1.2*SPRITE_SIZE);
    monster2WTexture = LoadTextureFromImage(img_monster2W);
    arrayTexturesMonster[1][0] = monster2ETexture;
    arrayTexturesMonster[1][1] = monster2WTexture;
    arrayTexturesMonster[1][2] = monster2STexture;
    arrayTexturesMonster[1][3] = monster2NTexture;
    //monstro 3
    //norte
    img_monster3N = LoadImage("../assets/monster3N.png");
    ImageResize(&img_monster3N, 1.2*SPRITE_SIZE, 1.2*SPRITE_SIZE);
    monster3NTexture = LoadTextureFromImage(img_monster3N);
    //leste
    img_monster3E = LoadImage("../assets/monster3E.png");
    ImageResize(&img_monster3E, 1.2*SPRITE_SIZE, 1.2*SPRITE_SIZE);
    monster3ETexture = LoadTextureFromImage(img_monster3E);
    //sul
    img_monster3S = LoadImage("../assets/monster3S.png");
    ImageResize(&img_monster3S, 1.2*SPRITE_SIZE, 1.2*SPRITE_SIZE);
    monster3STexture = LoadTextureFromImage(img_monster3S);
    //oeste
    img_monster3W = LoadImage("../assets/monster3W.png");
    ImageResize(&img_monster3W, 1.2*SPRITE_SIZE, 1.2*SPRITE_SIZE);
    monster3WTexture = LoadTextureFromImage(img_monster3W);
    arrayTexturesMonster[2][0] = monster3ETexture;
    arrayTexturesMonster[2][1] = monster3WTexture;
    arrayTexturesMonster[2][2] = monster3STexture;
    arrayTexturesMonster[2][3] = monster3NTexture;
    //monstro 4
    //norte
    img_monster4N = LoadImage("../assets/monster4N.png");
    ImageResize(&img_monster4N, 1.2*SPRITE_SIZE, 1.2*SPRITE_SIZE);
    monster4NTexture = LoadTextureFromImage(img_monster4N);
    //leste
    img_monster4E = LoadImage("../assets/monster4E.png");
    ImageResize(&img_monster4E, 1.2*SPRITE_SIZE, 1.2*SPRITE_SIZE);
    monster4ETexture = LoadTextureFromImage(img_monster4E);
    //sul
    img_monster4S = LoadImage("../assets/monster4S.png");
    ImageResize(&img_monster4S, 1.2*SPRITE_SIZE, 1.2*SPRITE_SIZE);
    monster4STexture = LoadTextureFromImage(img_monster4S);
    //oeste
    img_monster4W = LoadImage("../assets/monster4W.png");
    ImageResize(&img_monster4W, 1.2*SPRITE_SIZE, 1.2*SPRITE_SIZE);
    monster4WTexture = LoadTextureFromImage(img_monster4W);
    arrayTexturesMonster[3][0] = monster4ETexture;
    arrayTexturesMonster[3][1] = monster4WTexture;
    arrayTexturesMonster[3][2] = monster4STexture;
    arrayTexturesMonster[3][3] = monster4NTexture;
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
    //Fundos
    BackGround = LoadImage("../assets/background.png");
    ImageResize(&BackGround, LARGURA, ALTURA);
    BackGroundTexture = LoadTextureFromImage(BackGround);
    iconImage = LoadImage("../assets/icon.png");
}
void unloadTexturesMenus()
{
    unloadTexturesMenus();
    unloadSoundsAndMusics();
    UnloadImage(iconImage);
    UnloadImage(BackGroundGameOver);
    UnloadImage(BackGroundMenu);
    UnloadImage(BackGroundWinGame);
    UnloadImage(img_playerEDip);
    UnloadImage(img_playerWDip);
    UnloadImage(img_playerNDip);
    UnloadImage(img_playerSDip);
    UnloadImage(img_playerEMab);
    UnloadImage(img_playerWMab);
    UnloadImage(img_playerNMab);
    UnloadImage(img_playerSMab);
    UnloadImage(img_boss);
    UnloadImage(img_conf1);
    UnloadImage(img_conf2);
    //
    UnloadTexture(BackGroundGameOverTexture);
    UnloadTexture(BackGroundMenuTexture);
    UnloadTexture(BackGroundWinGameTexture);
    UnloadTexture(playerEDipTexture);
    UnloadTexture(playerWDipTexture);
    UnloadTexture(playerNDipTexture);
    UnloadTexture(playerSDipTexture);
    UnloadTexture(playerEMabTexture);
    UnloadTexture(playerWMabTexture);
    UnloadTexture(playerNMabTexture);
    UnloadTexture(playerSMabTexture);
    UnloadTexture(bossTexture);
}
void unloadTextures()
{
    unloadSoundsAndMusics();
    //Imagens
    UnloadImage(img_sword_mabel);
    UnloadImage(img_sword_dipper);
    UnloadImage(img_life);
    UnloadImage(img_wall);
    UnloadImage(img_monster1E);
    UnloadImage(img_monster1N);
    UnloadImage(img_monster1S);
    UnloadImage(img_monster1W);
    UnloadImage(img_monster2E);
    UnloadImage(img_monster2N);
    UnloadImage(img_monster2S);
    UnloadImage(img_monster2W);
    UnloadImage(img_monster3E);
    UnloadImage(img_monster3N);
    UnloadImage(img_monster3S);
    UnloadImage(img_monster3W);
    UnloadImage(img_monster4E);
    UnloadImage(img_monster4N);
    UnloadImage(img_monster4S);
    UnloadImage(img_monster4W);
    UnloadImage(BackGround);
    UnloadImage(iconImage);
    UnloadImage(img_playerEDip);
    UnloadImage(img_playerWDip);
    UnloadImage(img_playerNDip);
    UnloadImage(img_playerSDip);
    UnloadImage(img_playerEMab);
    UnloadImage(img_playerWMab);
    UnloadImage(img_playerNMab);
    UnloadImage(img_playerSMab);
    UnloadImage(img_boss);
    //Texturas
    UnloadTexture(swordMabelTexture);
    UnloadTexture(swordDipperTexture);
    UnloadTexture(lifeTexture);
    UnloadTexture(playerEDipTexture);
    UnloadTexture(playerWDipTexture);
    UnloadTexture(playerNDipTexture);
    UnloadTexture(playerSDipTexture);
    UnloadTexture(playerEMabTexture);
    UnloadTexture(playerWMabTexture);
    UnloadTexture(playerNMabTexture);
    UnloadTexture(playerSMabTexture);
    UnloadTexture(bossTexture);
    UnloadTexture(monster1ETexture);
    UnloadTexture(monster1NTexture);
    UnloadTexture(monster1STexture);
    UnloadTexture(monster1WTexture);
    UnloadTexture(monster2ETexture);
    UnloadTexture(monster2NTexture);
    UnloadTexture(monster2STexture);
    UnloadTexture(monster2WTexture);
    UnloadTexture(monster3ETexture);
    UnloadTexture(monster3NTexture);
    UnloadTexture(monster3STexture);
    UnloadTexture(monster3WTexture);
    UnloadTexture(monster4ETexture);
    UnloadTexture(monster4NTexture);
    UnloadTexture(monster4STexture);
    UnloadTexture(monster4WTexture);
    UnloadTexture(BackGroundTexture);
    UnloadTexture(wallTexture);
}
void underlineText(char *string, int x, int y, int size, Color inSideColor, Color outColor)
{
    DrawText(string, x - 3, y, size, outColor);
    DrawText(string, x, y - 3, size, outColor);
    DrawText(string, x, y + 3, size, outColor);
    DrawText(string, x + 3, y, size, outColor);
    DrawText(string, x, y, size, inSideColor);
}
void ShowTopBar(game gameTopBarStatus)
{
    char l[10], lev[12], sc[15];
    sprintf(l, "Vidas: %d", gameTopBarStatus.atualStatus.lifes);
    sprintf(lev, "Nivel: %d", gameTopBarStatus.atualStatus.level);
    sprintf(sc, "Escores: %d", gameTopBarStatus.atualStatus.score);
    DrawRectangle(0, 0, 1200, 60, BLACK);
    DrawText(l, 40, 5, SPRITE_SIZE, WHITE);
    DrawText(lev, 280, 5, SPRITE_SIZE, WHITE);
    DrawText(sc, 480, 5, SPRITE_SIZE, WHITE);
    if(gameTopBarStatus.atualStatus.sword){
        DrawTexture(swords[gameTopBarStatus.atualPlayer.person], 1100 , 5, WHITE);
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
                        InGame->monsters[monsters].sprite = rand()%(4);
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
    while(draw){
        DrawTexture(BackGroundMenuTexture, 0, 0, WHITE);
        DrawText("ZINF", 100, 20, 100, WHITE);
        for(i = 0; i < 5; i++){
            if(optionSelected == i){
                DrawCircle(90, i*110 + 220, 5, RED);
                DrawText(optionsText[i], 100, i*110 + 200, SPRITE_SIZE, RED);
            } else {
                DrawText(optionsText[i], 100, i*110 + 200, SPRITE_SIZE, WHITE);
            }
        }
        DrawTexture(arrayTexturesPlayer[gamePlayer->person][0], 420, 440 - 25, WHITE);
        if((IsKeyPressed(KEY_LEFT)||IsKeyPressed(KEY_RIGHT))&&(optionSelected == 2)&&!gameInProgress){
            PlaySound(menuSound);
            if(gamePlayer->person == 1){
                gamePlayer->person = 0;
            } else {
                gamePlayer->person = 1;
            }
        }
        if(IsKeyPressed(KEY_DOWN)){
            PlaySound(menuSound);
            if(optionSelected == 4){
                optionSelected = 0;
            } else {
                optionSelected++;
            }
        }
        if(IsKeyPressed(KEY_UP)){
            PlaySound(menuSound);
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
            PlaySound(menuSound);
            draw = 0;
	    }
    }
    return optionSelected;
}
int gameOver()
{
    char *optionsText[4];
    int optionSelected, i, draw, MenuAnswer;
    optionSelected = 0;
    draw = 1;
    optionsText[0] = "Recomecar";
    optionsText[1] = "Carregar jogo";
    optionsText[2] = "Voltar ao menu";
    optionsText[3] = "Sair";
    while(draw){
        DrawTexture(BackGroundGameOverTexture, 0, 0, WHITE);
        DrawText("VOCE PERDEU", 100, 20, 100, WHITE);
        for(i = 0; i < 4; i++){
            if(optionSelected == i){
                DrawCircle(90, i*110 + 220, 5 + 3, BLACK);
                DrawCircle(90, i*110 + 220, 5, RED);
                underlineText(optionsText[i], 100, i*110 + 200, SPRITE_SIZE, RED, BLACK);
            } else {
                underlineText(optionsText[i], 100, i*110 + 200, SPRITE_SIZE, WHITE, BLACK);
            }
        }
        DrawTexture(bossTexture, 600, 330, WHITE);
        if(IsKeyPressed(KEY_DOWN)){
            PlaySound(menuSound);
            if(optionSelected == 3){
                optionSelected = 0;
            } else {
                optionSelected++;
            }
        }
        if(IsKeyPressed(KEY_UP)){
            PlaySound(menuSound);
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
            PlaySound(menuSound);
            draw = 0;
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
    PlaySound(killMonsterSound);
    monsterScore = InGame->monsters[monster].score;
    InGame->atualStatus.score += monsterScore;
    InGame->monsters[monster].alive = 0;
}
void drawPlayer(player atualPlayer, int counter)
{
    if((!atualPlayer.imune)||(counter%8 == 0)){ //exibe a sprite normal se não estiver imune, se estiver, exibe apenas a cada 8 frames, para dar a impressão de piscando!
        DrawTexture(arrayTexturesPlayer[atualPlayer.person][atualPlayer.orientation - 1], atualPlayer.x, atualPlayer.y, WHITE);
    }
}
void genarateWall(int matriz[SPRITE_HEIGHT][SPRITE_WIDHT])
{
    int i, j;
    for(i = 0; i < 16; i++){
        for(j = 0; j < SPRITE_WIDHT; j++){
            if(matriz[i][j]){
                DrawTexture(wallTexture, j*SPRITE_SIZE -22, i*SPRITE_SIZE + 60 -22, WHITE);
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
    PlaySound(nextLevelSound);
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
void changeLife(status *lifeStatus, int value)
{
    if(value < 0){
        PlaySound(damageSound);
    }
    lifeStatus->lifes += value;
}
int checkBossArea(int x, int y, int matriz[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame)
{
    // se o boss estiver vivo
    if(InGame->bossBill.lifes > 0){
            // adiciona x > 950 para o player não poder invadir a área do boss
        if((!matriz[(int) floor((y- 60)/SPRITE_SIZE)][(int) floor((x)/SPRITE_SIZE)])&&(x < 1200)&&(x > -SPRITE_SIZE)&&(y < 860)&&(y > 10)&&(x > 950)){
            return 1;
        }
    }
    else
        return 0;
}
int checkPosition(int x, int y, int matriz[SPRITE_HEIGHT][SPRITE_WIDHT])
{

        if((!matriz[(int) floor((y- 60)/SPRITE_SIZE)][(int) floor((x)/SPRITE_SIZE)])&&(x < 1200)&&(x > -SPRITE_SIZE)&&(y < 860)&&(y > 10)){
            return 1;
        }
        else{
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
    PlaySound(lifeSound);
    InGame->atualStatus.sword = 1;
    InGame->atualSword.alive = 0;
}
void drawSword(game *InGame)
{
    if(InGame->atualSword.alive){
        DrawTexture(swords[InGame->atualPlayer.person], InGame->atualSword.x, InGame->atualSword.y, WHITE);
    }
}

void bossDificultMode(boss *bossBill, int *counter)
{
    bossBill->attack = 5;
    *counter = 0;
}
void killBoss(game *InGame, int *counter)
{
    int x_max, x_min, y_max, y_min, y_monster, x_monster, orientation, x, y;
    if(InGame->bossBill.lifes != 0){
        orientation =InGame->atualPlayer.orientation;
        x = InGame->atualPlayer.x;
        y = InGame->atualPlayer.y;
        x_max = InGame->atualPlayer.x + 3*SPRITE_SIZE;
        x_min = InGame->atualPlayer.x - 3*SPRITE_SIZE;
        y_max = InGame->atualPlayer.y + 3*SPRITE_SIZE;
        y_min = InGame->atualPlayer.y - 3*SPRITE_SIZE;
        y_monster = InGame->bossBill.y;
        x_monster = InGame->bossBill.x;
              switch(orientation){
                 case 1:
                     if(((x_monster <= x_max)&&(x_monster >= x))&&(y == y_monster || y == y_monster + SPRITE_SIZE || y == y_monster + 2*SPRITE_SIZE)){
                            InGame->bossBill.lifes--;
                            if(InGame->bossBill.lifes == 15){
                            bossDificultMode(&InGame->bossBill, counter);
                            }
                     }
                     break;
             }
       // if((y_monster <= y_max)&&((y_monster <= y_min)||(y_monster >= y_min))&&(x_monster >= x_min)&&(x_monster <= x_max)){
       //     InGame->bossBill.lifes--;
       //     if(InGame->bossBill.lifes == 15){
       //         bossDificultMode(&InGame->bossBill, counter);
       //     }
        }
    }
int fireBallsMove(game *InGame, fireBall fireBalls[5], int *counter, int mapArray[SPRITE_HEIGHT][SPRITE_WIDHT], player atualPlayer, int imune_muahaha)
{
    int new_counter, i, x_player, y_player;
    x_player = atualPlayer.x;
    y_player = atualPlayer.y;
    if(InGame->bossBill.lifes > 0){
        for(i = 0; i < InGame->bossBill.attack; i++){
            //printf("\n\n\n%d", fireBalls[i].exist);
            if(fireBalls[i].exist == 1){
                //printf("\n\n\n%d %d %d %d", fireBalls[i].x, fireBalls[i].y, i, fireBalls[i].exist);
                if(InGame->bossBill.attack == 3)
                    DrawTexture(fireBallTexture, fireBalls[i].x, fireBalls[i].y +20, WHITE);
                else
                    DrawTexture(fireBallBlueTexture, fireBalls[i].x, fireBalls[i].y +20, WHITE);
            }
        }
        if(*counter == 12 - InGame->bossBill.attack){ //12 - 3(bolas de fogo pro vez) para quando ele esta no modo normal e 12 - 5 quando esta no modo difcil diminuindo o tempo do contador para o boss fazer a acao ele fica mais rapido e as bolas de fogo sao geradas mais rapidamente
            new_counter = 0;
            for(i = 0; i < InGame->bossBill.attack; i++){
                if(fireBalls[i].exist == 1){
                    if(checkPosition(fireBalls[i].x - SPRITE_SIZE, fireBalls[i].y + SPRITE_SIZE, mapArray)){
                        fireBalls[i].x -= 50;
                    } else {
                        fireBalls[i].exist = 0;
                    }
                    if(!atualPlayer.imune && !imune_muahaha){
                        if(((fireBalls[i].x + 2*SPRITE_SIZE >= x_player)&&(fireBalls[i].x <= x_player))&&((fireBalls[i].y + SPRITE_SIZE == y_player))){
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
        if(*counter == 12 - bossBill->attack){ //12 - 3(bolas de fogo pro vez) para quando ele esta no modo normal e 12 - 5 quando esta no modo difcil diminuindo o tempo do contador para o boss fazer a acao ele fica mais rapido e as bolas de fogo sao geradas mais rapidamente
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
        DrawRectangleLines(bossBill->x - 5 - 2, bossBill->y - 5 - 2, MAX_LIFES_BOSS*8 +2,  20 + 2, RED);
        DrawRectangle(bossBill->x - 5, bossBill->y - 5, bossBill->lifes*8, 20, RED);
        if(bossBill->attack == 5){
            DrawTexture(bossDificultTexture, bossBill->x, bossBill->y, WHITE);
        } else {
            DrawTexture(bossTexture, bossBill->x, bossBill->y, WHITE);
        }

        //movimentacao
        if(*counter == 12 - bossBill->attack){//12 - 3(bolas de fogo pro vez) para quando ele esta no modo normal e 12 - 5 quando esta no modo difcil diminuindo o tempo do contador para o boss fazer a acao ele fica mais rapido e as bolas de fogo sao geradas mais rapidamente
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
void drawMonsters(monster monsters[MAX_MONSTERS], int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], int *monsterCounter, game *InGame)
{
    int i, randow, move, x, y;
    *monsterCounter += 1;
    for(i = 0; i < monsters[0].qnt; i++){
        if(monsters[i].alive){
            x = monsters[i].x;
            y = monsters[i].y;
            DrawTexture(arrayTexturesMonster[monsters[i].sprite][monsters[i].orientation - 1], x, y, WHITE);
            randow = rand()%(2);
            if(randow == 1){
                move = monsters[i].orientation;
            } else{
                move = rand()%(4) + 1;
            }
            randow = rand()%(3 + 1);
            if((*monsterCounter % 8 == 0 && randow == 1) || (*monsterCounter % 14 == 0 && randow == 2)){
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
    indconf = 0;
    randow = 0;
    PlayMusicStream(winGameMusic);
    while(draw){
        UpdateMusicStream(winGameMusic);
        DrawTexture(BackGroundWinGameTexture, 0, 0, WHITE);
        underlineText("VOCE GANHOUU!!!!", 100, 20, 100, WHITE, BLACK);
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
                DrawCircle(90, i*110 + 220, 5 + 3, BLACK);
                DrawCircle(90, i*110 + 220, 5, RED);
                underlineText(optionsText[i], 100, i*110 + 200, SPRITE_SIZE, RED, BLACK);
            } else {
                DrawCircle(90, i*110 + 220, 5 + 3, BLACK);
                underlineText(optionsText[i], 100, i*110 + 200, SPRITE_SIZE, WHITE, BLACK);
            }
        }
        if(IsKeyPressed(KEY_DOWN)){
            PlaySound(menuSound);
            if(optionSelected == 2){
                optionSelected = 0;
            } else {
                optionSelected++;
            }
        }
        if(IsKeyPressed(KEY_UP)){
            PlaySound(menuSound);
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
            PlaySound(menuSound);
            draw = 0;
	    }
    }
    return optionSelected;
}
void showHighScores(score highscores[5])
{
    char scoreString[20];
    int i, draw;
    draw = 1;
    while(draw){
        DrawTexture(BackGroundScoreTexture, 0, 0, WHITE);
        underlineText("Lista dos highscores:", 100, 20, 80, WHITE, BLACK);
        for(i = 0; i < 5; i++){
            sprintf(scoreString, "%d", highscores[i].score);
            underlineText(highscores[i].name, 100, i*80 + 200, SPRITE_SIZE, WHITE, BLACK);
            underlineText(scoreString, 500, i*80 + 200, SPRITE_SIZE, WHITE, BLACK);
        }
        DrawCircle(90, 625, 5, RED);
        underlineText("Voltar", 100, 600, SPRITE_SIZE, RED, BLACK);
        BeginDrawing();
	    EndDrawing();
	    ClearBackground(BLACK);
	    if(IsKeyPressed(KEY_ENTER)){
            draw = 0;
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
    //InitWindow(LARGURA, ALTURA, text);
    //loadTexturesMenus();
    //SetWindowIcon(iconImage);
    //SetTargetFPS(60);
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
            //CloseWindow();
            //unloadTexturesMenus();
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
    int i;
    char line[20];
    FILE *FHighscores = fopen("../assets/highscores.bin", "rb");
    for(i = 0; i < 5; i++){
        fread(&highscores[i], sizeof(score), 1, FHighscores);
    }
    fclose(FHighscores);
}
int updateScores(score highscores[5], score new_score)
{
    int i, removedI, changed;
    char strScore[20];
    FILE *FHighscores = fopen("../assets/highscores.bin", "wb");
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
                med_score = highscores[i];
                highscores[i] = removed_score;
                removed_score = med_score;
                removedI = i;
            }
        }
    }
    for(i = 0; i < 5; i++){
        highscores[i].name[strcspn(highscores[i].name, "\n")] = '\0';
        fwrite(&highscores[i], sizeof(score), 1, FHighscores);
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
        }
    }
    strcpy(new_score.name, name);
    new_score.score = playerScore;
    updated = updateScores(highscores, new_score);
    while(draw){
        DrawTexture(BackGroundScoreTexture, 0, 0, WHITE);
        underlineText("ESCORE ATUALIZADO!", 100, 20, 80, WHITE, BLACK);
        if(updated){
            underlineText("Voce conseguiu um novo recorde!!", 100, 200, 50, GREEN, BLACK);
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
            underlineText("Puxa! Voce não conseguiu nenhum novo recorde", 100, 200, 40, RED, BLACK);
        }
        DrawCircle(90, 300, 5 + 3, BLACK);
        DrawCircle(90, 300, 5, RED);
        underlineText("Voltar", 100, 300, 50, RED, BLACK);
        BeginDrawing();
        EndDrawing();
        ClearBackground(BLACK);
        if(IsKeyPressed(KEY_ENTER)){
            draw = 0;
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
    int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], i, j, gameOption, continueGame = 1, MenuAnswer, contador = 0, x_player, y_player;
    int orientation = 1, monsterKilled, respostaMenu, bossCounter = 0, imune_muahaha = 0, monsterCounter = 0;
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
    readHighscores(Highscores);
        InitWindow(LARGURA, ALTURA, "ZINF"); //Inicializa janela, com certo tamanho e titulo
        InitAudioDevice();
        generateTextures();
        PlayMusicStream(gameMusic);
        SetWindowIcon(iconImage);
        SetTargetFPS(60);// Ajusta a janela para 60 frames por segundo
        callMenu(0, &continueGame, Highscores, MapArray, &InGame);
    while(continueGame){
        while (!WindowShouldClose())
        {
            UpdateMusicStream(gameMusic);
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
            if(monsterCounter%3 == 0){
                InGame.atualPlayer.x = x_player;
                InGame.atualPlayer.y = y_player;
                InGame.atualPlayer.orientation = orientation;
            }
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
                    killBoss(&InGame, &bossCounter);
                }
            }
            for(i = 0; i < 5; i++){
                if((InGame.lifes[i].alive)&&(InGame.lifes[i].x == InGame.atualPlayer.x)&&(InGame.lifes[i].y== InGame.atualPlayer.y)){
                    InGame.lifes[i].alive = 0;
                    PlaySound(lifeSound);
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
            if(contador > 119)
                InGame.atualPlayer.imune = 0;
            if(fireBallsMove(&InGame, fireBalls, &bossCounter, MapArray, InGame.atualPlayer, imune_muahaha)){
                InGame.atualPlayer.imune = 1;
                contador = 0;
                if(InGame.bossBill.attack == 3){
                    changeLife(&InGame.atualStatus, -2);
                    if(InGame.atualPlayer.x >= 2*SPRITE_SIZE)
                    InGame.atualPlayer.x -= 2*SPRITE_SIZE;
                    else if(InGame.atualPlayer.x >= SPRITE_SIZE)
                    InGame.atualPlayer.x -= SPRITE_SIZE;
                }
                else{
                    changeLife(&InGame.atualStatus, -3);
                    if(InGame.atualPlayer.x >= 2*SPRITE_SIZE)
                    InGame.atualPlayer.x -= 2*SPRITE_SIZE;
                    else if(InGame.atualPlayer.x >= SPRITE_SIZE)
                    InGame.atualPlayer.x -= SPRITE_SIZE;
                }
            }
            if(checkBossArea(x_player, y_player, MapArray, &InGame)){
                InGame.atualPlayer.x -= 4*SPRITE_SIZE;
                changeLife(&InGame.atualStatus, -1);
            }
            drawPlayer(InGame.atualPlayer, contador);
            genarateWall(MapArray);
            drawBoss(&InGame.bossBill, &bossCounter);
            attackBoss(&InGame.bossBill, &bossCounter, fireBalls);
            drawMonsters(InGame.monsters, MapArray, &monsterCounter, &InGame);
            drawLifes(InGame.lifes);
            drawSword(&InGame);
            ShowTopBar(InGame);
            BeginDrawing(); //Inicia o ambiente de desenho na tela
            EndDrawing(); //Finaliza o ambiente de desenho na tela
            ClearBackground(WHITE);
        }
        switch(gameOption){// 1 -> game over, 2 -> ganhou, 3 -> menu de pause
            case 1:
                MenuAnswer = gameOver();
                if(MenuAnswer == 0){
                    restartStatus(MapArray, &InGame, fireBalls, &imune_muahaha);
                } else if(MenuAnswer == 1){
                    saves(1, MapArray, &InGame);
                } else if(MenuAnswer == 2){
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
                    newScore(Highscores, InGame.atualStatus.score);
                    continueGame = 0;
                }
                break;
            case 3:
                if(callMenu(1, &continueGame, Highscores, MapArray, &InGame)){
                    restartStatus(MapArray, &InGame, fireBalls, &imune_muahaha);
                }
        }
    }
    CloseWindow(); // Fecha a janela
    unloadTextures();
}
