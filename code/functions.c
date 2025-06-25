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
#define MUSIC_VOLUME 0.2
#define TOP_BAR_HEIGHT 60

//DEFINIÇÕES DAS TEXTURAS, MÚSICAS E SONS
Image img_sword_mabel;
Texture2D swordMabelTexture;
Image img_sword_dipper;
Texture2D swordDipperTexture;
Texture swords[2];
Image img_life;
Texture2D lifeTexture;
//Texturas do player com cada uma das orientacoes
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
//MONSTRO 1 = MONSTRO ROXO
Image img_monster1N;
Texture2D monster1NTexture;
Image img_monster1S;
Texture2D monster1STexture;
Image img_monster1E;
Texture2D monster1ETexture;
Image img_monster1W;
Texture2D monster1WTexture;
//MONSTRO 2 = MONSTRO DENTADURA
Image img_monster2N;
Texture2D monster2NTexture;
Image img_monster2S;
Texture2D monster2STexture;
Image img_monster2E;
Texture2D monster2ETexture;
Image img_monster2W;
Texture2D monster2WTexture;
//MONSTRO 3 = MONSTRO FECHADURA
Image img_monster3N;
Texture2D monster3NTexture;
Image img_monster3S;
Texture2D monster3STexture;
Image img_monster3E;
Texture2D monster3ETexture;
Image img_monster3W;
Texture2D monster3WTexture;
//MONSTRO 4 = MONSTRO PRETO
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
Image BackGroundScoreNoNew;
Texture2D BackGroundScoreNoNewTexture;
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


//TIPO SCORE
typedef struct score
{
    char name[20]; //REPRESENTA O NOME DO JOGADOR COM O SCORE
    int score; //REPRESENTA O VALOR NUMERICO DO SCORE
} score;

//TIPO STATUS
typedef struct status
{
    int lifes; // REPRESENTA A QUANTIDADE DE VIDA ATUAL DO JOGADOR
    int level; // REPRESENTA O NIVEL ATUAL DO JOGO
    int score; // REPRESENTA A PONTUAÇÃO ATUAL DO JOGADOR
    int sword; // REPRESENTA SE O JOGADOR JA PEGOU A ESPADA OU NAO (0 = NAO PEGOU // 1 = PEGOU)
} status;

//TIPO BOSS
typedef struct boss
{
    int lifes; // REPRESENTA A QUANTIDADE DE VIDA DO BOSS
    int x; // REPRESENTA A COORDENADA X DO BOSS
    int y; // REPRESENTA A COORDENADA Y DO BOSS
    int attack; // REPRESENTA A QUANTIDADE DE BOLAS DE FOGO DO ATAQUE DO BOSS (PODE SER 3 OU 5)
    int orientation; //PODE SER 0 (BOSS ESTA SUBINDO) OU 1 (BOSS ESTA DESCENDO)
} boss;

//TIPO FIREBALL
typedef struct fireBall
{
    int exist; // PODE SER 0 (A BOLA DE FOGO NAO EXISTE) OU 1 (A BOLA DE FOGO EXISTE)
    int x; // REPRESENTA A COORDENADA X DA BOLA DE FOGO
    int y; // REPRESENTA A COORDENADA Y DA BOLA DE FOGO
} fireBall;

//TIPO SAVE
typedef struct save
{
    int index; // REPRESENTA O INDICE DO SAVE (PODE SER 1, 2 OU 3)
    char date[24]; // REPRESENTA A DATA EM QUE FOI CRIADO O SAVE
    char path[30]; // REPRESENTA UMA STRING COM O CAMINHO PARA O ARQUIVO DO SAVE
} save;

//TIPO MONSTRO
typedef struct monster
{
    int x; // REPRESENTA A COORDENADA X DO MONSTRO
    int y; // REPRESENTA A COORDENADA Y DO MONSTRO
    int score; // REPRESENTA A PONTUACAO QUE O MONSTRO DARA QUANDO MORRER (NUMERO ALEATORIO DE 0 A 100)
    int alive; // PODE SER 0 (O MONSTRO ESTA MORTO) OU 1 (O MONSTRO ESTA VIVO)
    int orientation; // REPRESENTA A DIRECAO EM QUE O MONSTRO ESTA ORIENTADO (PODE SER 1 = LESTE, 2 = OESTE, 3 = SUL, 4 = NORTE)
    int qnt; // REPRESENTA A QUANTIDADE TOTAL DE MONSTROS
    int sprite; // REPRESENTA O INDICE DA SPRITE DO MONSTRO (NUMERO ALEATORIO DE 0 A 3)
} monster;

//TIPO ESPADA
typedef struct sword
{
    int x; //REPRESENTA A COORDENADA X DA ESPADA
    int y; //REPRESENTA A COORDENADA Y DA ESPADA
    int alive; //PODE SER 0 (PLAYER PEGOU A ESPADA) OU 1 (PLAYER AINDA NAO PEGOU A ESPADA)
} sword;

//TIPO VIDA
typedef struct life
{
    int x; //REPRESENTA A COORDENADA X DA VIDA
    int y; //REPRESENTA A COORDENADA Y DA VIDA
    int alive; //PODE SER 0 (PLAYER COLETOU A VIDA) OU 1 (PLAYER AINDA NAO COLETOU A VIDA)
} life;

//TIPO PLAYER
typedef struct player
{
    int x; //REPRESENTA A COORDENADA X DO PLAYER
    int y; //REPRESENTA A COORDENADA Y DO PLAYER
    int orientation; //REPRESENTA A DIRECAO EM QUE O PLAYER ESTA ORIENTADO (PODE SER 1 = LESTE, 2 = OESTE, 3 = NORTE, 4 = SUL)
    int person; // REPRESENTA O PERSONAGEM ESCOLHIDO PELO JOGADOR (0 PARA DIPPER, 1 PARA MABEL)
    int imune; // PODE SER 0 (PLAYER NAO ESTA IMUNE) OU 1 (PLAYER ESTA IMUNE)
} player;

//TIPO JOGO
typedef struct game
{
    player atualPlayer; //REPRESENTA O PLAYER ATUAL DO JOGO
    status atualStatus; //REPRESENTA O STATUS ATUAL DO JOGO
    monster monsters[MAX_MONSTERS]; //REPRESENTA OS MONSTROS ATUAIS DO JOGO
    sword atualSword; //REPRESENTA A ESPADA ATUAL DO JOGO
    life lifes[MAX_LIFES]; //REPRESENTA AS VIDAS ATUAIS DO JOGO
    boss bossBill; //REPRESENTA O BOSS ATUAL DO JOGO
} game;

//FUNCAO QUE CARREGA OS ARQUIVOS DE SOM E MUSICA DO JOGO E CONFIGURA O VOLUME
void loadSoundsAndMusics()
{
    gameMusic = LoadMusicStream("../assets/sounds/weirdmageddonTheme.mp3");
    winGameMusic = LoadMusicStream("../assets/sounds/themeSong.mp3");
    SetMusicVolume(gameMusic, MUSIC_VOLUME);
    lifeSound = LoadSound("../assets/sounds/life.mp3");
    damageSound = LoadSound("../assets/sounds/damage.mp3");
    menuSound = LoadSound("../assets/sounds/menu.wav");
    killMonsterSound = LoadSound("../assets/sounds/killMonster.wav");
    gameOverSound = LoadSound("../assets/sounds/gameOver.mp3");
    nextLevelSound = LoadSound("../assets/sounds/levelPassed.wav");
}

//FUNCAO QUE DESCARREGA OS ARQUIVOS DE SOM E MUSICA DO JOGO
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

// FUNCAO QUE CARREGA E CONFIGURA TODAS AS TEXTURAS UTILIZADAS NOS MENUS DO JOGO
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
    BackGroundScoreNoNew = LoadImage("../assets/background_no_new_score.png");
    ImageResize(&BackGroundScoreNoNew, LARGURA, ALTURA);
    BackGroundScoreNoNewTexture = LoadTextureFromImage(BackGroundScoreNoNew);
    //confetes
    img_conf1 = LoadImage("../assets/confete1.png");
    img_conf2 = LoadImage("../assets/confete2.png");
    ImageResize(&img_conf1, 3*SPRITE_SIZE, 3*SPRITE_SIZE); //o tamanho do confete eh 3x3 sprites
    ImageResize(&img_conf2, 3*SPRITE_SIZE, 3*SPRITE_SIZE);
    confettis[0] = LoadTextureFromImage(img_conf1);
    confettis[1] = LoadTextureFromImage(img_conf2);
}

//FUNCAO QUE CARREGA E CONFIGURA TODAS AS TEXTURAS UTILIZADAS NA DURACAO DO JOGO
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
    ImageResize(&img_wall, SPRITE_SIZE, SPRITE_SIZE);
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
    ImageResize(&img_monster2N, SPRITE_SIZE, SPRITE_SIZE);
    monster2NTexture = LoadTextureFromImage(img_monster2N);
    //leste
    img_monster2E = LoadImage("../assets/monster2E.png");
    ImageResize(&img_monster2E, SPRITE_SIZE, SPRITE_SIZE);
    monster2ETexture = LoadTextureFromImage(img_monster2E);
    //sul
    img_monster2S = LoadImage("../assets/monster2S.png");
    ImageResize(&img_monster2S, SPRITE_SIZE, SPRITE_SIZE);
    monster2STexture = LoadTextureFromImage(img_monster2S);
    //oeste
    img_monster2W = LoadImage("../assets/monster2W.png");
    ImageResize(&img_monster2W, SPRITE_SIZE, SPRITE_SIZE);
    monster2WTexture = LoadTextureFromImage(img_monster2W);
    arrayTexturesMonster[1][0] = monster2ETexture;
    arrayTexturesMonster[1][1] = monster2WTexture;
    arrayTexturesMonster[1][2] = monster2STexture;
    arrayTexturesMonster[1][3] = monster2NTexture;
    //monstro 3
    //norte
    img_monster3N = LoadImage("../assets/monster3N.png");
    ImageResize(&img_monster3N, SPRITE_SIZE, SPRITE_SIZE);
    monster3NTexture = LoadTextureFromImage(img_monster3N);
    //leste
    img_monster3E = LoadImage("../assets/monster3E.png");
    ImageResize(&img_monster3E, SPRITE_SIZE, SPRITE_SIZE);
    monster3ETexture = LoadTextureFromImage(img_monster3E);
    //sul
    img_monster3S = LoadImage("../assets/monster3S.png");
    ImageResize(&img_monster3S, SPRITE_SIZE, SPRITE_SIZE);
    monster3STexture = LoadTextureFromImage(img_monster3S);
    //oeste
    img_monster3W = LoadImage("../assets/monster3W.png");
    ImageResize(&img_monster3W, SPRITE_SIZE, SPRITE_SIZE);
    monster3WTexture = LoadTextureFromImage(img_monster3W);
    arrayTexturesMonster[2][0] = monster3ETexture;
    arrayTexturesMonster[2][1] = monster3WTexture;
    arrayTexturesMonster[2][2] = monster3STexture;
    arrayTexturesMonster[2][3] = monster3NTexture;
    //monstro 4
    //norte
    img_monster4N = LoadImage("../assets/monster4N.png");
    ImageResize(&img_monster4N, SPRITE_SIZE, SPRITE_SIZE);
    monster4NTexture = LoadTextureFromImage(img_monster4N);
    //leste
    img_monster4E = LoadImage("../assets/monster4E.png");
    ImageResize(&img_monster4E, SPRITE_SIZE, SPRITE_SIZE);
    monster4ETexture = LoadTextureFromImage(img_monster4E);
    //sul
    img_monster4S = LoadImage("../assets/monster4S.png");
    ImageResize(&img_monster4S, SPRITE_SIZE, SPRITE_SIZE);
    monster4STexture = LoadTextureFromImage(img_monster4S);
    //oeste
    img_monster4W = LoadImage("../assets/monster4W.png");
    ImageResize(&img_monster4W, SPRITE_SIZE, SPRITE_SIZE);
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
    ImageResize(&img_fireBall, 2*SPRITE_SIZE, 2*SPRITE_SIZE); // o tamanho da bola de fogo do boss é 2x2 sprites
    fireBallTexture = LoadTextureFromImage(img_fireBall);
    //bola de fogo azul
    img_fireBallBlue = LoadImage("../assets/fireBallAzul.png");
    ImageResize(&img_fireBallBlue, 2*SPRITE_SIZE, 2*SPRITE_SIZE); // o tamanho da bola de fogo do boss é 2x2 sprites
    fireBallBlueTexture = LoadTextureFromImage(img_fireBallBlue);
    //Fundos
    BackGround = LoadImage("../assets/background.png");
    ImageResize(&BackGround, LARGURA, ALTURA);
    BackGroundTexture = LoadTextureFromImage(BackGround);
    iconImage = LoadImage("../assets/icon.png");
}

//FUNCAO QUE DESCARREGA TODAS AS TEXTURAS UTILIZADAS NOS MENUS DO JOGO
void unloadTexturesMenus()
{
    unloadTexturesMenus();
    unloadSoundsAndMusics();
    UnloadImage(iconImage);
    UnloadImage(BackGroundGameOver);
    UnloadImage(BackGroundMenu);
    UnloadImage(BackGroundWinGame);
    UnloadImage(BackGroundScore);
    UnloadImage(BackGroundScoreNoNew);
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
    UnloadTexture(BackGroundScoreTexture);
    UnloadTexture(BackGroundScoreNoNewTexture);
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

//FUNCAO QUE DESCARREGA TODAS AS TEXTURAS UTILIZADAS NA DURACAO DO JOGO
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

// FUNCAO QUE RECEBE UMA STRING, UMA COOREDANA X, UMA COORDENADA Y, UMA COR1 E UMA COR2
// ESSA FUNCAO DESENHA A STRING NAS COORDENADAS RECEBIDAS COM A COR1, CONTORNADA PELA COR2
void underlineText(char *string, int x, int y, int size, Color inSideColor, Color outColor)
{
    //para das impressao de contornada o texto, imprimimos dos 4 lados o mesmo texto, em preto, 3 pixels para o respectivo lado
    DrawText(string, x - 3, y, size, outColor);
    DrawText(string, x, y - 3, size, outColor);
    DrawText(string, x, y + 3, size, outColor);
    DrawText(string, x + 3, y, size, outColor);
    DrawText(string, x, y, size, inSideColor);
}

//FUNCAO QUE RECEBE O JOGO ATUAL E EXIBE A TOPBAR COM AS INFORMACOES ATUAIS DO JOGO
void ShowTopBar(game gameTopBarStatus)
{
    char l[10], lev[12], sc[15]; //define strings a ser usadas na funcao
    sprintf(l, "Vidas: %d", gameTopBarStatus.atualStatus.lifes);
    sprintf(lev, "Nivel: %d", gameTopBarStatus.atualStatus.level);
    sprintf(sc, "Escores: %d", gameTopBarStatus.atualStatus.score);
    DrawRectangle(0, 0, LARGURA, TOP_BAR_HEIGHT, BLACK); //O tamanho da top bar eh 1200x60 pixels
    DrawText(l, 40, 5, SPRITE_SIZE, WHITE); //imprime a quantidade de vidas na posicao (40, 5), dentro da topbar
    DrawText(lev, 280, 5, SPRITE_SIZE, WHITE); //imprime o nivel atual na posicao (280, 5), dentro da topbar
    DrawText(sc, 480, 5, SPRITE_SIZE, WHITE); //imprime a pontuaçao atual na posicao (480, 5), dentro da topbar
    if(gameTopBarStatus.atualStatus.sword){ //se a espada foi coletada,
        //desenha a arma do personagem do player na posicao (1100, 5), dentro da topbar
        DrawTexture(swords[gameTopBarStatus.atualPlayer.person], 1100 , 5, WHITE);
    }
}

//FUNCAO QUE RECEBE UMA STRING QUE REPRESENTA O NOME DO ARQUIVO DE UM MAPA E UMA MATRIZ DE INTEIROS QUE REPRESENTA O MAPA
//A FUNCAO COLOCA 1 NAS POSICOES DA MATRIZ COM PAREDE E 0 NA POSICAO DA MATRIZ SEM PAREDE
void generateArrayMap(char path[20], int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT])
{
    int i, j;
    char  item;
    FILE *map = fopen(path, "r");
    for(i = 0; i < SPRITE_HEIGHT; i++){
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

//FUNCAO QUE RECEBE UMA STRING QUE REPRESENTA O NOME DO ARQUIVO DE UM MAPA, UMA MATRIZ DE INTEIROS QUE REPRESENTA O MAPA, O JOGO ATUAL, E UM ARRANJO DE FIREBALLS
//A FUNCAO COLOCA 1 NAS POSICOES DA MATRIZ COM PAREDE E 0 NA POSICAO DA MATRIZ SEM PAREDE, E, ALÉM DISSO, ELA CONFIGURA O JOGO ATUAL BASEADO NAS INFORMACOES DO MAPA
void generateMap(char path[20], int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame, fireBall fireBalls[5])
{
    int i, j, lifes = 0, monsters = 0, x, y, k;
    char item;
    FILE *map = fopen(path, "r");
    for(i = 0; i < SPRITE_HEIGHT; i++){
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
                        InGame->atualPlayer.orientation = 1; //INICIALIZA NA ORIENTACAO LESTE
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
                        InGame->monsters[monsters].score = rand()%(100 + 1); // SORTEIA UM NUMERO ALEATORIO ENTRE 0 E 100
                        InGame->monsters[monsters].alive = 1;
                        InGame->monsters[monsters].orientation = 1; // INICIALIZA NA ORIENTACAO LESTE
                        InGame->monsters[monsters].sprite = rand()%(4); // SORTEIA UM NUMERO DE 0 A 3 PARA SER A SPRITE DO MONSTRO
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
                }
            }
            x = 0;
            y = 0;
        }
    }
    InGame->monsters[0].qnt = monsters; //ARMAZENA A INFORMACAO DE QUANTOS MONSTROS FORAM CARREGADOS
}

//FUNCAO QUE RECEBE O PLAYER DO JOGO ATUAL E UMA VARIAVEL QUE REPRESENTA SE O JOGO ESTA EM PROGRESSO OU NAO
//A FUNCAO DESENHA E RODA O MENU, POSSIBILITANDO QUE O USUARIA ALTERE ENTRE AS OPCOES DO MENU E ESCOLHA O PERSONAGEM DESEJADO
//A FUNCAO RETORNA A OPCAO DO MENU ESCOLHIDA E CONFIGURA O PERSONAGEM ESCOLHIDO PELO USUARIO
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
    SetTargetFPS(30); //DIMINUI OS FPS NORMAL PARA AS ANIMACOES DO MENU FICAREM MAIS DEVAGARES
    while(draw){
        DrawTexture(BackGroundMenuTexture, 0, 0, WHITE);
        DrawText("ZINFAGEDON", 100, 20, 100, WHITE);
        if(gameInProgress){
            DrawText("(Pause)", 800, 20, 80, WHITE);
        }
        for(i = 0; i < 5; i++){
            if(optionSelected == i){ //Se a opcao estiver selecionada, desenha em vermelho e desenha um circulo vermelho do lado
                if((optionSelected == 2)&&!gameInProgress){
                    DrawText("<", 100 - 25, 440 - 20, SPRITE_SIZE, RED);// DESENHA A SETA UM POUCO PARA CIMA PARA DAR A IMPRESSAO DE MOVIMENTACAO
                    DrawText(">", 420, 440 - 20, SPRITE_SIZE, RED);
                } else {
                    DrawCircle(90, i*110 + 220, 5, RED);
                    if(!gameInProgress){
                        DrawText("<", 100 - 25, 440 - 15, SPRITE_SIZE, WHITE);
                        DrawText(">", 420, 440 - 15, SPRITE_SIZE, WHITE);
                    }
                }

                DrawText(optionsText[i], 100, i*110 + 200, SPRITE_SIZE, RED);
            } else {
                DrawText(optionsText[i], 100, i*110 + 200, SPRITE_SIZE, WHITE); //Cada opcao eh 110 pixels abaixo da anterior
            }
        }

        DrawTexture(arrayTexturesPlayer[gamePlayer->person][0], 440, 440 - 25, WHITE);
        if((IsKeyPressed(KEY_LEFT))&&(optionSelected == 2)&&!gameInProgress){
            DrawText("<", 100 - 30, 440 - 20, SPRITE_SIZE, RED); //DESENHA A SETA PARA O LADO SELECIONADO PARA DAR IMPRESSAO DE MOVIMENTACAO
            PlaySound(menuSound);
            if(gamePlayer->person == 1){
                gamePlayer->person = 0;
            } else {
                gamePlayer->person = 1;
            }
        }
        if((IsKeyPressed(KEY_RIGHT))&&(optionSelected == 2)&&!gameInProgress){
            DrawText(">", 420 + 5, 440 - 20, SPRITE_SIZE, RED); //DESENHA A SETA PARA O LADO SELECIONADO PARA DAR IMPRESSAO DE MOVIMENTACAO
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
    SetTargetFPS(60); //RESETA O FPS PARA 60, O PADRAO DO JOGO
    return optionSelected;
}

//A FUNCAO DESENHA E RODA O MENU DE GAME OVER, POSSIBILITANDO QUE O USUARIO ALTERE ENTRE AS OPCOES DO MENU
//A FUNCAO RETORNA A OPCAO SELECIONADO PELO USUSARIO
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
    PlaySound(gameOverSound);
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

//A FUNCAO RECEBE O ARRANJO QUE REPRESENTA O MAPA, O JOGO ATUAL E A VARIAVEL DO CHEAT MUAHAHA
//A FUNCAO RECONFIGURA AS INFORMACOES PARA REINICIAR O JOGO
void restartStatus(int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame, fireBall fireBalls[5], int *imune_muahaha)
{
    //Reseta os status para o inicial, nivel 1, vidas 3, score 0 e a espada 0
    InGame->atualStatus.lifes = 3;
    InGame->atualStatus.level = 1;
    InGame->atualStatus.score = 0;
    InGame-> atualStatus.sword = 0;
    generateMap("../assets/maps/mapa01.txt", MapArray, InGame, fireBalls); // Carrega o primeiro mapa
    InGame->bossBill.lifes = 0;
    *imune_muahaha = 0;
}

//A FUNCAO RECEBE O JOGO ATUAL E O INDICE DE UM MONSTRO
//A FUNCAO MATA ESSE MONSTRO, TOCANDO O SOM, ATUALIZANDO A PONTUACAO DO JOGADOR E DECLARANDO O MONSTRO DO INDICE RECEBIDO COMO MORTO
void killMonster(game *InGame,  int monster)
{
    int monsterScore;
    PlaySound(killMonsterSound);
    monsterScore = InGame->monsters[monster].score;
    InGame->atualStatus.score += monsterScore;
    InGame->monsters[monster].alive = 0;
}

//A FUNCAO RECEBE O PLAYER E O CONTADOR DA IMUNIDADE E DESENHA O PLAYER
void drawPlayer(player atualPlayer, int counter)
{
    if((!atualPlayer.imune)||(counter%8 == 0)){ //exibe a sprite normal se não estiver imune, se estiver, exibe apenas a cada 8 frames, para dar a impressão de estar piscando!
        DrawTexture(arrayTexturesPlayer[atualPlayer.person][atualPlayer.orientation - 1], atualPlayer.x, atualPlayer.y, WHITE);
    }
}

//A FUNCAO RECEBE A MATRIZ QUE REPRESENTA O MAPA E DESENHA AS PARES NAS COORDENADAS DEFINIDAS COMO 1
void genarateWall(int matriz[SPRITE_HEIGHT][SPRITE_WIDHT])
{
    int i, j;
    for(i = 0; i < SPRITE_HEIGHT; i++){
        for(j = 0; j < SPRITE_WIDHT; j++){
            if(matriz[i][j]){
                DrawTexture(wallTexture, j*SPRITE_SIZE, i*SPRITE_SIZE + TOP_BAR_HEIGHT, WHITE); //+60 da top bar
            }
        }
    }
}

//A FUNCAO RECEBE O ARRAY DE MONSTROS E RETORNO 0 CASO ALGUM MONSTRO ESTEJA VIVO, SE TODOS ESTIVEREM MORTOS, A FUNCAO RETORNA 1
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

//A FUNCAO RECEBE O STATUS ATUAL DO JOGO, UMA STRING DO CAMINHO PARA O ARQUIVO DE UM MAPA E A VARIAVEL DO CHEAT MUAHAHA
// A FUNCAO PASSA PARA A SEGUINTE FASE E RETORNA 1 SE O ARQUIVO DA PROXIMA FASE EXISTIR, CASO CONTRARIO, RETORNA 0
int nextLevel(status *atualStatus, char file[20], int *muahaha)
{
    int i;
    atualStatus->level += 1;
    if(atualStatus->level <= 9){ //Se o level tiver apenas uma casa decimal, no caso <= 9, coloca um 0 na frente do caminho do arquivo do proximo mapa
        sprintf(file, "../assets/maps/mapa0%d.txt", atualStatus->level);
    } else {
        sprintf(file, "../assets/maps/mapa%d.txt", atualStatus->level);
    }
    atualStatus->sword = 0; //Zera o status da espada e do muahaha
    *muahaha = 0;
    return FileExists(file);
}

//A FUNCAO RECEBE O STATUS ATUAL E UM VALOR INTEIRO
//A FUNCAO ALTERA A VIDA DO JOGADOR BASEADO NO VALOR INTEIRO RECEBIDO (PODE PERDER OU GANHAR VIDA)
void changeLife(status *lifeStatus, int value)
{
    if(value < 0){//Se for negativo, significa que o player levou dano, logo toca o som de dano
        PlaySound(damageSound);
    }
    lifeStatus->lifes += value;
}

//A FUNCAO RECEBE As COORDENADA X E Y DO JOGADOR, A MATRIZ DO MAPA E O JOGO ATUAL
//A FUNCAO RETORNA 0 SE O PLAYER INVADIU A AREA DO BOSS, CASO CONTRARIO, RETORNA 1
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

//A FUNCAO RECEBE DUAS COORDENADAS E A MATRIZ DO MAPA
// A FUNCAO RETORNA 0 CASO AS COORDENADAS RECEBIDAS ESTEJAM DENTRO DE UMA PAREDE NO MAPA, CASO CONTRARIO, RETORNA 1
int checkPosition(int x, int y, int matriz[SPRITE_HEIGHT][SPRITE_WIDHT])
{
    if((!matriz[(int) floor((y- TOP_BAR_HEIGHT)/SPRITE_SIZE)][(int) floor((x)/SPRITE_SIZE)])&&(x < 1200)&&(x > -SPRITE_SIZE)&&(y < 860)&&(y > 10)){
        return 1;
    }
    else{
        return 0;
    }
}

//A FUNCAO RECEBE O JOGO ATUAL E A MATRIZ DO MAPA
//A FUNCAO RETORNA O INDICE DO MONSTRO NA AREA DE ATAQUE DO JOGADOR, SE EXISTIR ALGUM MONSTRO ALI
//CASO NAO EXISTA NENHUM MONSTRO NA AREA DE ATAQUE OU EXISTA ALGUMA PAREDE ENTRE O MONSTRO E O JOGADOR, A FUNCAO RETORNA -1
int existMonster(game *InGame, int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT])
{
    int i, x, y, x_monster, y_monster, y_max, y_min, x_max, x_min, orientation;
    orientation =InGame->atualPlayer.orientation;
    x = InGame->atualPlayer.x;
    y = InGame->atualPlayer.y;
    x_max = InGame->atualPlayer.x + 3*SPRITE_SIZE; //O ataque engloba 3 sprites na direcao do player
    x_min = InGame->atualPlayer.x - 3*SPRITE_SIZE;
    y_max = InGame->atualPlayer.y + 3*SPRITE_SIZE;
    y_min = InGame->atualPlayer.y - 3*SPRITE_SIZE;
    for(i = 0; i < MAX_MONSTERS; i++){ //O FOR VARRE OS MONSTROS
        if(InGame->monsters[i].alive){ //CONSIDERA APENAS OS MONSTROS VIVOS
            x_monster = InGame->monsters[i].x;
            y_monster = InGame->monsters[i].y;
             switch(orientation){
                 case 1: //CASO O PLAYER ESTEJA ORIENTADO AO LESTE
                     if(((x_monster <= x_max)&&(x_monster >= x))&&(y == y_monster)){ //SE O MONSTRO ESTIVER NA AREA DE 3 SPRITES A DIREITA DO PLAYER
                          // E SE O MONSTRO ESTIVER APENAS A 1 SPRITE DE DISTANCIA OU NO MESMO LUGAR DO PLAYER
                          if((x_monster - x == SPRITE_SIZE || x == x_monster))
                              return i; //RETORNA O INDICE DO MONSTRO
                          // OU, E SE O MOSNTRO ESTIVER A DOIS SPRITES DE DISTANCIA DO PLAYER E NAO EXISTIR PAREDE ENTRE O PLAYER E O MONSTRO
                          else if(x_monster - x == 2*SPRITE_SIZE && checkPosition(x + SPRITE_SIZE, y, MapArray))
                              return i; //RETORNA O INDICE DO MONSTRO
                          // OU, E SE O MOSNTRO ESTIVER A TRES SPRITES DE DISTANCIA DO PLAYER E NAO EXISTIR PAREDE ENTRE O PLAYER E O MONSTRO
                          else if(x_monster - x == 3*SPRITE_SIZE && checkPosition(x + SPRITE_SIZE, y, MapArray) && checkPosition(x + 2*SPRITE_SIZE, y, MapArray))
                              return i; //RETORNA O INDICE DO MONSTRO
                     }
                     break;
                 case 2: //CASO O PLAYER ESTEJA ORIENTADO AO OESTE
                     if(((x_monster >= x_min)&&(x_monster <= x))&&(y == y_monster)){ //SE O MONSTRO ESTIVER NA AREA DE 3 SPRITES A ESQUERDA DO PLAYER
                            // E SE O MONSTRO ESTIVER APENAS A 1 SPRITE DE DISTANCIA OU NO MESMO LUGAR DO PLAYER
                          if(x_monster - x == -SPRITE_SIZE || x == x_monster)
                              return i;
                          // OU, E SE O MOSNTRO ESTIVER A DOIS SPRITES DE DISTANCIA DO PLAYER E NAO EXISTIR PAREDE ENTRE O PLAYER E O MONSTRO
                          else if(x_monster - x == -2*SPRITE_SIZE && checkPosition(x - SPRITE_SIZE, y, MapArray))
                              return i; //RETORNA O INDICE DO MONSTRO
                          // OU, E SE O MOSNTRO ESTIVER A TRES SPRITES DE DISTANCIA DO PLAYER E NAO EXISTIR PAREDE ENTRE O PLAYER E O MONSTRO
                          else if(x_monster - x == -3*SPRITE_SIZE && checkPosition(x - SPRITE_SIZE, y, MapArray) && checkPosition(x - 2*SPRITE_SIZE, y, MapArray))
                              return i; //RETORNA O INDICE DO MONSTRO
                     }
                     break;
                 case 3: //CASO O PLAYER ESTEJA ORIENTADO AO NORTE
                     if(((y_monster >= y_min)&&(y_monster <= y))&&(x == x_monster)){ //SE O MONSTRO ESTIVER NA AREA DE 3 SPRITES ACIMA DO PLAYER
                            // E SE O MONSTRO ESTIVER APENAS A 1 SPRITE DE DISTANCIA OU NO MESMO LUGAR DO PLAYER
                          if(y_monster - y == -SPRITE_SIZE || y == y_monster)
                              return i;
                          // OU, E SE O MOSNTRO ESTIVER A DOIS SPRITES DE DISTANCIA DO PLAYER E NAO EXISTIR PAREDE ENTRE O PLAYER E O MONSTRO
                          else if(y_monster - y == -2*SPRITE_SIZE && checkPosition(x, y - SPRITE_SIZE, MapArray))
                              return i; //RETORNA O INDICE DO MONSTRO
                          // OU, E SE O MOSNTRO ESTIVER A TRES SPRITES DE DISTANCIA DO PLAYER E NAO EXISTIR PAREDE ENTRE O PLAYER E O MONSTRO
                          else if(y_monster - y == -3*SPRITE_SIZE && checkPosition(x, y - SPRITE_SIZE, MapArray) && checkPosition(x, y - 2*SPRITE_SIZE, MapArray))
                              return i; //RETORNA O INDICE DO MONSTRO
                     }
                     break;
                 default: //CASO O PLAYER ESTEJA ORIENTADO AO SUL
                     if(((y_monster <= y_max)&&(y_monster >= y))&&(x == x_monster)){ //SE O MONSTRO ESTIVER NA AREA DE 3 SPRITES ABAIXO DO PLAYER
                            // E SE O MONSTRO ESTIVER APENAS A 1 SPRITE DE DISTANCIA OU NO MESMO LUGAR DO PLAYER
                          if(y_monster - y == SPRITE_SIZE || y == y_monster)
                              return i;
                          // OU, E SE O MOSNTRO ESTIVER A DOIS SPRITES DE DISTANCIA DO PLAYER E NAO EXISTIR PAREDE ENTRE O PLAYER E O MONSTRO
                          else if(y_monster - y == 2*SPRITE_SIZE && checkPosition(x, y + SPRITE_SIZE, MapArray))
                              return i; //RETORNA O INDICE DO MONSTRO
                          // OU, E SE O MOSNTRO ESTIVER A TRES SPRITES DE DISTANCIA DO PLAYER E NAO EXISTIR PAREDE ENTRE O PLAYER E O MONSTRO
                          else if(y_monster - y == 3*SPRITE_SIZE && checkPosition(x, y + SPRITE_SIZE, MapArray) && checkPosition(x, y + 2*SPRITE_SIZE, MapArray))
                              return i; //RETORNA O INDICE DO MONSTRO
                     }
             }
        }
    }
    return -1;
}

//A FUNCAO RECEBE O JOGO ATUAL
//A FUNCAO RETORNA 1 E REMOVE UMA VIDA DO JOGADOR CASO O JOGADOR ESTEJA NA MESMA POSICAO DE UM MONSTRO VIVO, CASO CONTRARIO, A FUNCAO RETORNA 0
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

//A FUNCAO RECEBE O JOGO ATUAL
void chatchSword(game *InGame)
{
    PlaySound(lifeSound);
    InGame->atualStatus.sword = 1; // O JOGADOR PEGOU A ARMA
    InGame->atualSword.alive = 0; // A ARMA FOI COLETADA
}

//A FUNCAO RECEBE O JOGO ATUAL
//SE A ARMA NAO FOI COLETADA AINDA, A FUNCAO DESENHA A ARMA DO PERSONAGEM SELECIONADO EM SUA POSICAO
void drawSword(game *InGame)
{
    if(InGame->atualSword.alive){
        DrawTexture(swords[InGame->atualPlayer.person], InGame->atualSword.x, InGame->atualSword.y, WHITE);
    }
}

//A FUNCAO RECEBE O BOSS DO JOGO ATUAL E O CONTADOR DO BOSS
//A FUNCAO TORNA MUDA A QUANTIDADE DO ATAQUE DO BOSS E REINICIA O SEU CONTADOR
void bossDificultMode(boss *bossBill, int *counter)
{
    //Muda a rapidez e a quantidade do ataque do boss
    bossBill->attack = 5;
    *counter = 0;
}

//A FUNCAO RECEBE O JOGO ATUAL E O CONTADOR DO BOSS
//A FUNCAO DANIFICA O BOSS CASO ELE ESTEJA NA AREA DE ATAQUE DO JOGADOR;
void killBoss(game *InGame, int *counter)
{
    int x_max, y_boss, x_boss, orientation, x, y;
    if(InGame->bossBill.lifes != 0){
        orientation =InGame->atualPlayer.orientation;
        x = InGame->atualPlayer.x;
        y = InGame->atualPlayer.y;
        x_max = InGame->atualPlayer.x + 3*SPRITE_SIZE;
        y_boss = InGame->bossBill.y;
        x_boss = InGame->bossBill.x;
              if(orientation == 1){//se o jogador estiver orientado ao leste
                    //SE O BOSS ESTIVER NA AREA DE 3 SPRITES A DIREITA DO PLAYER E NA MESMA ALTURA DO PLAYER,
                    //(DESTACA-SE QUE O BOSS OCUPA TRES SPRITES DE ALTURA, LOGO EH NECESSARIO CONFERIR O Y EM 3 SPRITES DIFERENTES)
                    if(((x_boss <= x_max)&&(x_boss >= x))&&(y == y_boss || y == y_boss + SPRITE_SIZE || y == y_boss + 2*SPRITE_SIZE)){
                        InGame->bossBill.lifes--; //REMOVE UMA VIDA DO BOSS
                        PlaySound(killMonsterSound);
                        if(InGame->bossBill.lifes == 15){ //SE A VIDA DO BOSS ATINGIR 15,
                            bossDificultMode(&InGame->bossBill, counter); //ATIVAR O MODO DIFICIL DO BOSS
                        }
                    }
             }
        }
    }

//A FUNCAO RECEBE O JOGO ATUAL, O ARRAY DE FIREBALLS, O CONTADOR DA IMUNIDADE, A MATRIZ DO MAPA E A VARIAVEL DO CHEAT MUAHAHA
//A FUNCAO DESENHA AS BOLAS DE FOGO E AS MOVIMENTA, SE ELAS EXISTIREM
//CASO UMA BOLA DE FOGO ATINGA O PLAYER OU ALGUMA PAREDE, ELA DEIXA DE EXISTIR
//A FUNCAO RETORNA 1 CASO A BOLA ATINGA UM PLAYER NAO IMUNE, CASO CONTRARIO, A FUNCAO RETORNA 0
int fireBallsMove(game *InGame, fireBall fireBalls[5], int *counter, int mapArray[SPRITE_HEIGHT][SPRITE_WIDHT], int imune_muahaha)
{
    int new_counter, i, x_player, y_player;
    x_player = InGame->atualPlayer.x;
    y_player = InGame->atualPlayer.y;
    if(InGame->bossBill.lifes != 0){ // SE O BOSS ESTA VIVO
        for(i = 0; i < InGame->bossBill.attack; i++){
            if(fireBalls[i].exist == 1){ // SE EXISTE FIREBALL COM ESSE INDICE, DESENHA A TEXTURA DEPENDENDO DO MODO DO BOSS
                if(InGame->bossBill.attack == 3)
                    DrawTexture(fireBallTexture, fireBalls[i].x, fireBalls[i].y +20, WHITE);
                else
                    DrawTexture(fireBallBlueTexture, fireBalls[i].x, fireBalls[i].y +20, WHITE);
            }
        }
        if(*counter == 12 - InGame->bossBill.attack){ //12 - 3(bolas de fogo pro vez) para quando ele esta no modo normal e 12 - 5 quando esta no modo difcil diminuindo o tempo do contador para o boss fazer a acao ele fica mais rapido e as bolas de fogo sao geradas mais rapidamente
            new_counter = 0;
            for(i = 0; i < InGame->bossBill.attack; i++){
            if(fireBalls[i].exist == 1){ // DESLOCA A FIREBALL PARA A ESQUERDA SE ELA NAO ENCONTRAR O PLAYER, UMA PAREDE, OU O FIM DA TELA
                    if(checkPosition(fireBalls[i].x - SPRITE_SIZE, fireBalls[i].y + SPRITE_SIZE, mapArray)){
                        fireBalls[i].x -= 50;
                    } else { // SE BATER EM UMA PAREDE OU ENCONTRAR O FIM DA DELA, ELA DEIXA DE EXISTIR
                        fireBalls[i].exist = 0;
                    }
                    if(!InGame->atualPlayer.imune && !imune_muahaha){ // SE O PLAYER NAO ESTIVER IMUNE
                        if(((fireBalls[i].x + 2*SPRITE_SIZE >= x_player)&&(fireBalls[i].x <= x_player))&&((fireBalls[i].y + SPRITE_SIZE == y_player))){ //CONFERE SE A FIREBALL ENTROU EM CONTATO COM O PLAYER
                            fireBalls[i].exist = 0; // SE BATER NO PLAYER, DEIXA DE EXISTIR
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

//A FUNCAO RECEBE O JOGO ATUAL
//CASO O PLAYER ESTEJA NA MESMA POSICAO DO BOSS, A FUNCAO RETORNA 1, CASO CONTRARIO, A FUNCAO RETORNA 0
int attackContactBoss(game *InGame)
{
    //DESTACA-SE QUE EH NECESSARIO FAZER VARIAS CONFERENCIAS CONSIDERANDO QUE O BOSS CUPA 3X3 SPRITES
    if((InGame->atualPlayer.x >= InGame->bossBill.x)&&((InGame->atualPlayer.y == InGame->bossBill.y) || (InGame->atualPlayer.y == InGame->bossBill.y + SPRITE_SIZE) || (InGame->atualPlayer.y == InGame->bossBill.y + 2*SPRITE_SIZE))&&(InGame->bossBill.lifes > 0)){
        if(InGame->bossBill.attack == 3)//SE O MODO DIFICIL ESTIVER DESATIVADO
           changeLife(&InGame->atualStatus, -2); //TIRA DUAS VIDAS DO PLAYER
        else //SENAO
           changeLife(&InGame->atualStatus, -3); //TIRA TRES VIDAS DO PLAYER
        return 1;
    }
    else{
    return 0;
    }
}

//A FUNCAO RECEBE O BOSS DO JOGO ATUAL, O CONTADOR DO BOSS E AS FIREBALLS
//A FUNCAO INICIALIZA OS ATAUQES DE BOLAS DE FOGO QUE NAO FORAM INICIALIZADAS AINDA QUANDO O CONTADOR DO BOSS CHEGA A DETERMINADO NUMERO
void attackBoss(boss *bossBill, int *counter, fireBall fireBalls[5])
{
    int new_counter, i;
    if(bossBill->lifes != 0){
        if(*counter == 12 - bossBill->attack){ //12 - 3(bolas de fogo pro vez) para quando ele esta no modo normal e 12 - 5 quando esta no modo difcil diminuindo o tempo do contador para o boss fazer a acao ele fica mais rapido e as bolas de fogo sao geradas mais rapidamente
            for(i = 0; i < bossBill->attack; i++){
                if(fireBalls[i].exist != 1){ // SE NAO EXITIR FIREBALL COM ESSE INDICE, CRIA E SAI DO FOR
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
}

//A FUNCAO RECEBE O BOSS DO JOGO ATUAL E O CONTADOR DO BOSS
//A FUNCAO DESENHA E MOVIMENTA O BOSS
void drawBoss(boss *bossBill, int *counter)
{
    int new_counter;
    if(bossBill->lifes != 0){
        DrawRectangleLines(bossBill->x - 5 - 2, bossBill->y - 5 - 2, MAX_LIFES_BOSS*8 +2,  20 + 2, RED);
        DrawRectangle(bossBill->x - 5, bossBill->y - 5, bossBill->lifes*8, 20, RED); //BARRA DE VIDA DO BOSS
        if(bossBill->attack == 5){ //A TEXTURA DO BOSS MUDA DEPENDENDO SE O MODO DIFICIL FOI ATIVADO OU NAO
            DrawTexture(bossDificultTexture, bossBill->x, bossBill->y, WHITE);
        } else {
            DrawTexture(bossTexture, bossBill->x, bossBill->y, WHITE);
        }

        //movimentacao
        if(*counter == 12 - bossBill->attack){//12 - 3(bolas de fogo pro vez) para quando ele esta no modo normal e 12 - 5 quando esta no modo difcil diminuindo o tempo do contador para o boss fazer a acao ele fica mais rapido e as bolas de fogo sao geradas mais rapidamente
            //Desloca o boss para cima ou para baixo
            if(bossBill->orientation){
                bossBill->y += 50;
            } else {
                bossBill->y -= 50;
            }
            new_counter = 0;
        } else {
            new_counter = *counter + 1;
        }
        if(bossBill->y <= TOP_BAR_HEIGHT){//60 da barra de status -  tamanho do boss
            bossBill->orientation = 1;
        } else if(bossBill->y >= ALTURA - 3*SPRITE_SIZE - TOP_BAR_HEIGHT) { // altura da tela + 60 da barra de status
            bossBill->orientation = 0;
        }
        *counter = new_counter;
    }
}

//A MATRIZ DO MAPA, O CONTADOR DA MOVIMENTACAO E O JOGO ATUAL
//A FUNCAO DESENHA E MOVIMENTA OS MONSTROS BASEADO NO CONTADOR DE MOVIMENTACAO E NA ALEATORIEDADE
//SE A NOVA POSICAO DO MONSTRO NAO PASSAR PELA FUNCAO CHECKPOSITION, ALTERA A POSICAO ATE ACHAR UMA POSICAO VALIDA
void drawMonsters(int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], int *monsterCounter, game *InGame)
{
    int i, randow, move, x, y;
    *monsterCounter += 1;
    for(i = 0; i < InGame->monsters[0].qnt; i++){
        if(InGame->monsters[i].alive){
            x = InGame->monsters[i].x;
            y = InGame->monsters[i].y;
            DrawTexture(arrayTexturesMonster[InGame->monsters[i].sprite][InGame->monsters[i].orientation - 1], x, y, WHITE);//DESENHA O MONSTRO
            randow = rand()%(2);
            if(randow == 1){
                move = InGame->monsters[i].orientation; //50% DE CHANCE DO MONSTRO MANTER A MESMA ORIENTACAO
            } else{
                move = rand()%(4) + 1; //50% DE CHANCE DO MONSTRO MUDAR DE ORIENTACAO
            }
            randow = rand()%(3 + 1);
            //O MONSTRO TEM CHANCE DE MOVER TODA VEZ QUE O CONTADOR FOR DIVISIVEL POR 10 OU POR 16
            if((*monsterCounter % 10 == 0 && randow == 1) || (*monsterCounter % 16 == 0 && randow == 2)){
                InGame->monsters[i].orientation = move;
                switch(move){//ALTERA A COORDENADA DO MONSTRO BASEADO NA ORIENTACAO
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
            if(checkPosition(x, y, MapArray)){// SE PASSAR PELO TESTE, DEFINE A NOVA POSICAO DO MONSTRO
                InGame->monsters[i].x = x;
                InGame->monsters[i].y = y;
            }
            else do{//SENAO, RETORNA PARA AS COORDENADAS ANTERIORES
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
                if(move == 1){//SE A ORIENTACAO ESTAVA PARA O LESTE, AGORA ESTA PARA O NORTE
                    move = 4;
                }
                else if(move == 2){//SE A ORIENTACAO ESTAVA PARA O OESTE, AGORA ESTA PARA O SUL
                    move = 3;
                }
                else if(move == 3){//SE A ORIENTACAO ESTAVA PARA O SUL, AGORA ESTA PARA O LESTE
                    move = 1;
                }
                else{//SE A ORIENTACAO ESTAVA PARA O NORTE, AGORA ESTA PARA O OESTE
                    move = 2;
                }
                InGame->monsters[i].orientation = move;
                switch(move){//ALTERA A COORDENADA DO MONSTRO BASEADO NA NOVA ORIENTACAO
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
                if(checkPosition(x, y, MapArray)){// SE PASSAR PELO TESTE, DEFINE A NOVA POSICAO DO MONSTRO
                    InGame->monsters[i].x = x;
                    InGame->monsters[i].y = y;
                }
            }while(!checkPosition(x, y, MapArray));//REPETE O PROCESSO ATE ACHAR UMA POSICAO VALIDA
        }
    }
}

//A FUNCAO RECEBE AS VIDAS DO JOGO ATUAL E AS DESENHA SE AINDA NAO TIVEREM SIDO CAPTURADAS
void drawLifes(life lifes[MAX_LIFES])
{
    int i;
    for(i = 0; i < MAX_LIFES; i++){
        if(lifes[i].alive){
            DrawTexture(lifeTexture, lifes[i].x, lifes[i].y, WHITE);
        }
    }
}

// A FUNCAO RECEBE O INDICE DO CONFETE E DESENHA O CONFETE
void drawConfetti(int indconf)
{
    DrawTexture(confettis[indconf], 1000, 150, WHITE);
}

//A FUNCAO EXECUTA O MENU DE VITORIA E RETORNA A OPCAO QUE O USUARIO ESCOLHER
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
        underlineText("Obrigado por jogar nosso jogo! =)", 750, 700, 20, WHITE, BLACK); //UM PEQUENO TESTO DE CREDITOS NO FIM DO JOGO
        underlineText("Jogo feito por:", 750, 725, 20, WHITE, BLACK);
        underlineText("Gabriel Fontaneli", 750, 750, 20, WHITE, BLACK);
        underlineText("Rafaele Castagnara", 750, 775, 20, WHITE, BLACK);
        underlineText("Jogo inspirado no desenho Gravity Falls", 750, 800, 20, WHITE, BLACK);
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

//A POSICAO RECEBE OS HIGHSCORES E OS EXIBE NA TELA ATE O USUARIO APERTAR ENTER PARA VOLTAR
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

// A FUNCAO RECEBE UM SAVE E O JOGO ATUAL E SALVO O JOGO NESSE SAVE
void saveGame(save saveSave, game *InGame)
{
    printf("%s\n", saveSave.path);
    FILE *saveFileSave = fopen(saveSave.path, "wb");
    fwrite(InGame, sizeof(game), 1, saveFileSave);
    fclose(saveFileSave);
}

//A FUNCAO RECEBE UM SAVE, A MATRIZ DO MAPA E O JOGO ATUAL E CARREGA O SAVE NO JOGO ATUAL
void loadGame(save loadSave, int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame)
{
    FILE *loadFileSave = fopen(loadSave.path, "rb");
    char atualFile[30];
    fread(InGame, sizeof(game), 1, loadFileSave);
    if(InGame->atualStatus.level <= 9){ //CARREGA O CAMINHO CERTO DO MAPA DO LEVEL DO SAVE
        sprintf(atualFile, "../assets/maps/mapa0%d.txt", InGame->atualStatus.level);
    }
    else {
        sprintf(atualFile, "../assets/maps/mapa%d.txt", InGame->atualStatus.level);
    }
    generateArrayMap(atualFile, MapArray); //GERA APENAS A MATRIZ DO MAPA E NAO RECARREGA OS MOSNTROS E OUTROS ATRIBUTOS
    fclose(loadFileSave);
}

//A FUNCAO RECEBE UMA VARIAVEL DE OPCAO, A MATRIZ DO MAPA E O JOGO ATUAL
//A FUNCAO EXECUTA O MENU DE SALVAR OU CARREGAR O JOGO, DEPENDENDO DA OPCAO
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
        sprintf(optionsText[i], "Save %d da data: %s", i + 1, savesList[i].date); //EXIBE A DATA DO SAVE
    }
    fclose(file_saves);
    strcpy(optionsText[3], "Voltar");
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
                    savesList[optionSelected].index = optionSelected + 1; //SUBSTITUI O SAVE ANTERIOR
                    sprintf(savesList[optionSelected].path, "../assets/saves/save%d.bin", savesList[optionSelected].index);
                    for(i = 0; i < 3; i++){
                        fwrite(&savesList[i], sizeof(save), 1, file_saves);
                    }
                    fclose(file_saves);
                    saveGame(savesList[optionSelected], InGame);
                }
            }
            draw = 0;
	    }
    }
}

//FUNCAO QUE RECEBE UMA VARIAVEL QUE REPRESENTA SE O JOGO ESTA EM PROGRESSO OU NAO E UMA VARIAVEL QUE REPRESENTA SE O JOGO DEVE CONTINUAR OU NAO
//ALEM DISSO, A FUNCAO RECEBE OS HIGHSCORES, A MATRIZ DO MAPA E O JOGO ATUAL
//A FUNCAO CHAMA A FUNCAO MENU, QUE VARIA DE ACORDO COM SE O JOGO ESTA EM PROGRESSO OU NAO, E CHAMA OUTRAS FUNCOES BASEADO NA OPCAO DO MENU SELECIONADA PELO USUSARIO
//A FUNCAO RETORNA 1 SE PRECISA COMECAR OU RECOMECAR O JOGO E RETORNA 0 SE PRECISA RETORNAR AO JOGO ATUAL
int callMenu(int gameInProgress, int *continueGame, score highscores[5], int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame)
{
    int MenuAswer;
    MenuAswer = menu(gameInProgress, &InGame->atualPlayer);
    if(gameInProgress){
        if(MenuAswer == 1){ //Chamou o menu inicial
            return callMenu(0, continueGame, highscores, MapArray, InGame);
        } else if(MenuAswer == 4){ //Escolheu a opcao de sair
            *continueGame = 0;
        } else if(MenuAswer == 3){ //Escolheu a opcao de salvar jogo
            saves(0, MapArray, InGame);
            return callMenu(1, continueGame, highscores, MapArray, InGame);
        }
    } else {
        if(MenuAswer == 0){ //Escolheu iniciar ou reiniciar o jogo
            return 1; //precisa (re)comecar o jogo
        } else if(MenuAswer == 1){ //Escolheu a opcao de ver os highscores
            showHighScores(highscores);
            return callMenu(gameInProgress, continueGame, highscores, MapArray, InGame);
        } else if(MenuAswer == 4){ //Escolheu sair do jogo
            *continueGame = 0; // sair do jogo
        } else if(MenuAswer == 3){ //Escolheu carregar um jogo anterior
            saves(1, MapArray, InGame);
        }
    }
    return 0; //retorna ao jogo atual
}

//A FUNCAO RECEBE O ARRAY DE HIGHSCORES E OS ASSOCIA COM OS HIGHSCORES SALVOS NO ARQUIVO DE HIGHSCORES
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

//A FUNCAO RECEBE O ARRAY DE HIGHSCORES E UM NOVO SCORE
//CASO O NOVO SCORE SEJA MAIOR DO QUE UM DOS HIGHSCORES DO ARRAY, ATUALIZA O ARQUIVO DOS HIGHSCORES E RETORNA 1
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

//A FUNCAO RECEBE UM ARRAY DE HIGHSCORES E O SCORE DO PLAYER
//A FUNCAO PEDE PRO USUARIO DIGITAR O SEU NOME
//CASO O SCORE TENHA SIDO ATUALIZADO, ABRE UM MENU PARABENIZANDO O JOGADOR, CASO CONTRARIO, ABRE OUTRO MENU
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
        if(updated){
            DrawTexture(BackGroundScoreTexture, 0, 0, WHITE);
        } else {
            DrawTexture(BackGroundScoreNoNewTexture, 0, 0, WHITE);
        }
        underlineText("ESCORE ATUALIZADO!", 100, 20, 80, WHITE, BLACK);
        if(updated){ //O jogador teve seu score incluido nos highscores
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

//A FUNCAO RECEBE A VARIAVEL DO CHEAT MUAHAHA E A STRING DE TESTE DO CHEAT MUAHAHA
void muahaha(int *imune_muahaha, char test[8])
{
    int i = 0;
    char muahaha[8] = {'M','U','A','H','A','H','A','\0'}, current, read;
    current = GetKeyPressed(); //ARMAZENA O CARACTER QUE O PLAYER ESTA DIGITANDO NO MOMENTO
    if(current != 0){ //SE O PLAYER DIGITOU ALGUM CARACTER,
        for(i=0;i<7;i++){
            if(i!=6){
                test[i] = test [i+1]; // A STRING DE TESTE INTEIRA É EMPURRADA UM CARACTER PARA A ESQUERDA, ELIMINANDO O PRIMEIRO CARACTER
            }
            else{
                test[6] = current; //O CARACTER DIGITADO PELO PLAYER EH ARMAZENADO NO UTLIMO CARACTER DO ARRAY DE TESTE
            }
        }
    }
    if(strcmp(test, muahaha) == 0){ //SE AS STRINGS FOREM IGUAIS
        *imune_muahaha = 1; //ATIVA O CHEAT MUAHAHA
    }
}
