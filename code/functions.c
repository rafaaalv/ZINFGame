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
#define MAX_MONSTERS 10
#define MAX_LIFES 5
#define MONSTERS_COLLUM 5
#define SWORD_COLLUM 3
#define LIFES_COLLUM 4
#define A 1000
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
//Fontes
//Font fontBm;
//Font fontTtf;
//Personagem escolhido
int person;//0 para dipper, 1 para mabel

typedef struct score
{
    char name[20];
    int score;
} score;

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
    ImageResize(&img_playerNDip, SPRITE_SIZE, SPRITE_SIZE);
    playerNDipTexture = LoadTextureFromImage(img_playerNDip);
    //leste
    img_playerEDip = LoadImage("../assets/sprite_dipper00.png");
    ImageResize(&img_playerEDip, SPRITE_SIZE, SPRITE_SIZE);
    playerEDipTexture = LoadTextureFromImage(img_playerEDip);
    //sul
    img_playerSDip = LoadImage("../assets/sprite_dipper02.png");
    ImageResize(&img_playerSDip, SPRITE_SIZE, SPRITE_SIZE);
    playerSDipTexture = LoadTextureFromImage(img_playerSDip);
    //oeste
    img_playerWDip = LoadImage("../assets/sprite_dipper01.png");
    ImageResize(&img_playerWDip, SPRITE_SIZE, SPRITE_SIZE);
    playerWDipTexture = LoadTextureFromImage(img_playerWDip);
    arrayTexturesPlayer[0][0] = playerEDipTexture;
    arrayTexturesPlayer[0][1] = playerWDipTexture;
    arrayTexturesPlayer[0][2] = playerNDipTexture;
    arrayTexturesPlayer[0][3] = playerSDipTexture;
    //Mabel
    img_playerNMab = LoadImage("../assets/sprite_mabel03.png");
    ImageResize(&img_playerNMab, SPRITE_SIZE, SPRITE_SIZE);
    playerNMabTexture = LoadTextureFromImage(img_playerNMab);
    //leste
    img_playerEMab = LoadImage("../assets/sprite_mabel00.png");
    ImageResize(&img_playerEMab, SPRITE_SIZE, SPRITE_SIZE);
    playerEMabTexture = LoadTextureFromImage(img_playerEMab);
    //sul
    img_playerSMab = LoadImage("../assets/sprite_mabel02.png");
    ImageResize(&img_playerSMab, SPRITE_SIZE, SPRITE_SIZE);
    playerSMabTexture = LoadTextureFromImage(img_playerSMab);
    //oeste
    img_playerWMab = LoadImage("../assets/sprite_mabel01.png");
    ImageResize(&img_playerWMab, SPRITE_SIZE, SPRITE_SIZE);
    playerWMabTexture = LoadTextureFromImage(img_playerWMab);
    arrayTexturesPlayer[1][0] = playerEMabTexture;
    arrayTexturesPlayer[1][1] = playerWMabTexture;
    arrayTexturesPlayer[1][2] = playerNMabTexture;
    arrayTexturesPlayer[1][3] = playerSMabTexture;
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
    //confetes
    img_conf1 = LoadImage("../assets/confete1.png");
    img_conf2 = LoadImage("../assets/confete2.png");
    ImageResize(&img_conf1, 3*SPRITE_SIZE, 3*SPRITE_SIZE);
    ImageResize(&img_conf2, 3*SPRITE_SIZE, 3*SPRITE_SIZE);
    confettis[0] = LoadTextureFromImage(img_conf1);
    confettis[1] = LoadTextureFromImage(img_conf2);
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
                        *y_player = 60+y;
                        break;
                    case 'V':
                        LifesArray[lifes][0] = x;
                        LifesArray[lifes][1] = 60+y;
                        LifesArray[lifes][2] = 1;
                        lifes++;
                        break;
                    case 'M':
                        MonsterArray[monsters][0] = x;
                        MonsterArray[monsters][1] = 60+y;
                        MonsterArray[monsters][2] = rand()%(100 + 1);
                        MonsterArray[monsters][3] = 1;
                        MonsterArray[monsters][4] = 1;
                        monsters++;
                        break;
                    case 'E':
                        SwordArray[0] = x;
                        SwordArray[1] = 60+y;
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
    char text[40], *optionsText[4];
    int optionSelected, i, draw;
    optionSelected = 0;
    draw = 1;
    if(gameInProgress){
        optionsText[0] = "Continuar Jogo";
        optionsText[1] = "Voltar ao menu";
        optionsText[2] = "Personagem";
        optionsText[3] = "Sair";
    } else {
        optionsText[0] = "Iniciar";
        optionsText[1] = "Scoreboard";
        optionsText[2] = "Personagem";
        optionsText[3] = "Sair";
    }

    InitWindow(LARGURA, ALTURA, "Menu");
    generateTextures();
    SetTargetFPS(60);
    while(draw){
        DrawText("ZINF", 100, 20, 100, WHITE);
        for(i = 0; i < 4; i++){
            if(optionSelected == i){
                DrawCircle(90, i*110 + 220, 5, RED);
                DrawText(optionsText[i], 100, i*110 + 200, SPRITE_SIZE, RED);
            } else {
                DrawText(optionsText[i], 100, i*110 + 200, SPRITE_SIZE, WHITE);
            }
        }
        DrawTexture(arrayTexturesPlayer[person][0], 800, 440, WHITE);
        if((IsKeyPressed(KEY_LEFT)||IsKeyPressed(KEY_RIGHT))&&(optionSelected == 2)&&!gameInProgress){
            if(person == 1){
                person = 0;
            } else {
                person = 1;
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
    int i, x, y, x_monster, y_monster, y_max, y_min, x_max, x_min;
    x = x_player;
    y = y_player;
    x_max = x_player + 3*SPRITE_SIZE;
    x_min = x_player - 3*SPRITE_SIZE;
    y_max = y_player + 3*SPRITE_SIZE;
    y_min = y_player - 3*SPRITE_SIZE;
    for(i = 0; i < MAX_MONSTERS; i++){
        if(arrayMonsters[i][3]){
            x_monster = arrayMonsters[i][0];
            y_monster = arrayMonsters[i][1];
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
                return i;
            }
        }
    }
    return -1;
}
void drawPlayer(int x, int y, int orientation)
{
    DrawTexture(arrayTexturesPlayer[person][orientation - 1], x, y, WHITE);
}
void genarateWall(int matriz[SPRITE_HEIGHT][SPRITE_WIDHT])
{
    int i, j;
    for(i = 0; i < 16; i++){
        for(j = 0; j < SPRITE_WIDHT; j++){
            if(matriz[i][j]){
                DrawTexture(wallTexture, j*SPRITE_SIZE, i*SPRITE_SIZE + 60, WHITE);
            }
        }
    }
}
int allMonstersKilled(int monstersArray[MAX_MONSTERS][MONSTERS_COLLUM])
{
    int i;
    for(i = 0; i < MAX_MONSTERS; i++){
        if(monstersArray[i][3]){
            return 0;
        }
    }
    return 1;
}
int nextLevel(status *atualStatus, char file[20])
{
    atualStatus->level += 1;
    if(atualStatus->level <= 9){
        sprintf(file, "../assets/mapa0%d.txt", atualStatus->level);
    } else {
        sprintf(file, "../assets/mapa%d.txt", atualStatus->level);
    }
    atualStatus->sword = 0;
    return FileExists(file);
}
int conferePosicao(int x, int y, int matriz[SPRITE_HEIGHT][SPRITE_WIDHT])
{
    if((!matriz[(int) floor((y- 60)/SPRITE_SIZE)][(int) floor((x)/SPRITE_SIZE)])&&(x < 1200)&&(x > -SPRITE_SIZE)&&(y < 920)&&(y > 10)){
        return 1;
	} else {
        return 0;
	}
}
void changeLife(status *lifeStatus, int value)
{
    lifeStatus->lifes += value;
}
int attackMonster(status *atualStatus, int arrayMonsters[MAX_MONSTERS][MONSTERS_COLLUM], int x_player, int y_player)
{
    int i;
    for(i = 0; i < MAX_MONSTERS; i++){
        if((x_player == arrayMonsters[i][0])&&(y_player == arrayMonsters[i][1])&&(arrayMonsters[i][3])){
            changeLife(atualStatus, -1);
            return 1;
        }
    }
    return 0;
}
void chatchSword(status *swordStatus, int arraySword[3])
{
    swordStatus->sword = 1;
    arraySword[2] = 0;
}
void drawSword(int arraySword[3])
{
    if(arraySword[2]){
        DrawTexture(swordTexture, arraySword[0], arraySword[1], WHITE);
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
            if(randow == 1){
                MonstersArray[i][4] = move;
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
                MonstersArray[i][4] = move;
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
                if(conferePosicao(x, y, MapArray)){
                    MonstersArray[i][0] = x;
                    MonstersArray[i][1] = y;
                }
            }while(!conferePosicao(x, y, MapArray));
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
int callMenu(int gameInProgress, int *continueGame, score highscores[5])
{
    int MenuAswer;
    MenuAswer = menu(gameInProgress);
    if(gameInProgress){
        if(MenuAswer == 1){
            return callMenu(0, continueGame, highscores);
        } else if(MenuAswer == 3){
            *continueGame = 0;
        }
    } else {
        if(MenuAswer == 0){
            return 1; //precisa (re)comecar o jogo
        } else if(MenuAswer == 1){
            showHighScores(highscores);
            return callMenu(gameInProgress, continueGame, highscores);
        } else if(MenuAswer == 3){
            *continueGame = 0; // sair do jogo
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
int StartGame()
{
    status InGameStatus;
    score Highscores[5];
    int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], i, j, game, continueGame = 1, MenuAnswer, MonsterArray[MAX_MONSTERS][MONSTERS_COLLUM] = {{0}}, imune = 0, contador = 0;
    int SwordArray[3], LifesArray[5][3] = {{0}}, x_player, y_player, orientation = 1, monsterKilled, respostaMenu;
    char atualFile[20];

    restartStatus(&InGameStatus, MapArray, MonsterArray, SwordArray, LifesArray, &x_player, &y_player);
    srand(time(NULL));

    person = 0;
    readHighscores(Highscores);
    callMenu(0, &continueGame, Highscores);
    while(continueGame){
        readHighscores(Highscores);
        InitWindow(LARGURA, ALTURA, "ZINF"); //Inicializa janela, com certo tamanho e titulo
        generateTextures();
        SetTargetFPS(20);// Ajusta a janela para 20 frames por segundo
        drawPlayer(x_player, y_player, orientation);
        while (!WindowShouldClose())
        {
            DrawTexture(BackGroundTexture, 0, 0, WHITE);
            if (IsKeyPressed(KEY_RIGHT)||IsKeyDown(KEY_RIGHT)||IsKeyPressed(KEY_D)||IsKeyDown(KEY_D)) {
                orientation = 1;
                if(conferePosicao((x_player + SPRITE_SIZE), y_player, MapArray)){
                    x_player += SPRITE_SIZE;
                }
            }
            if (IsKeyPressed(KEY_LEFT)||IsKeyDown(KEY_LEFT)||IsKeyPressed(KEY_A)||IsKeyDown(KEY_A)) {
                orientation = 2;
                if(conferePosicao((x_player -SPRITE_SIZE), y_player, MapArray)){
                    x_player -= SPRITE_SIZE;
                }
            }
            if (IsKeyPressed(KEY_UP)||IsKeyDown(KEY_UP)||IsKeyPressed(KEY_W)||IsKeyDown(KEY_W)) {
                orientation = 3;
                if(conferePosicao(x_player, (y_player -SPRITE_SIZE), MapArray)){
                    y_player -= SPRITE_SIZE;
                }
            }
            if (IsKeyPressed(KEY_DOWN)||IsKeyDown(KEY_DOWN)||IsKeyPressed(KEY_S)||IsKeyDown(KEY_S)) {
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

            if(InGameStatus.sword){
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
            if(allMonstersKilled(MonsterArray)){
                if(nextLevel(&InGameStatus, atualFile)){
                    generateMap(atualFile, MapArray, MonsterArray, SwordArray, LifesArray, &x_player, &y_player);
                } else{
                    game = 2;
                    break;
                }
            }
            if(InGameStatus.lifes == 0){
                game = 1;
                break;
            }
            if(!imune){
                if(attackMonster(&InGameStatus, MonsterArray, x_player, y_player)){
                    imune = 1;
                    contador = 0;
                }
            }
            else contador++;
            if(contador > 29)
                imune = 0;
            drawPlayer(x_player, y_player, orientation);
            genarateWall(MapArray);
            drawMonsters(MonsterArray, MapArray);
            drawLifes(LifesArray);
            drawSword(SwordArray);

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
                    if(callMenu(0, &continueGame, Highscores)){
                        restartStatus(&InGameStatus, MapArray, MonsterArray, SwordArray, LifesArray, &x_player, &y_player);
                    }
                } else {
                    continueGame = 0;
                }
                break;
            case 2:
                MenuAnswer = winGame();
                if(MenuAnswer == 0){
                    newScore(Highscores, InGameStatus.score);
                    restartStatus(&InGameStatus, MapArray, MonsterArray, SwordArray, LifesArray, &x_player, &y_player);
                } else if(MenuAnswer == 1){
                    newScore(Highscores, InGameStatus.score);
                    if(callMenu(0, &continueGame, Highscores)){
                        restartStatus(&InGameStatus, MapArray, MonsterArray, SwordArray, LifesArray, &x_player, &y_player);
                    }
                } else {
                    continueGame = 0;
                    newScore(Highscores, InGameStatus.score);
                }
                break;
            case 3:
                if(callMenu(1, &continueGame, Highscores)){
                    restartStatus(&InGameStatus, MapArray, MonsterArray, SwordArray, LifesArray, &x_player, &y_player);
                }

        }
    }
    unloadTextures();
    CloseWindow(); // Fecha a janela
    return 0;
}
