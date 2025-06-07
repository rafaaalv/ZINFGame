#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include "raylib.h"
#include "functions.c"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LARGURA 1200
#define ALTURA 860

void generateTextures();

void unloadTextures();

void ShowTopBar(status TopBarStatus);

int menu(int gameInProgress);

int attackMonster(status *atualStatus, int arrayMonsters[5][MONSTERS_COLLUM], int x_player, int y_player);

void restartStatus(status *gameStatus, int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], int MonsterArray[5][MONSTERS_COLLUM], int SwordArray[3], int LifesArray[5][3], int *x_player, int *y_player, boss *bossBill);

void killMonster(status *gameStatus, int arrayMonsters[5][MONSTERS_COLLUM], int monster);

int existMonster(int orientation, int arrayMonsters[5][MONSTERS_COLLUM], int x_player, int y_player);

void drawPlayer(int x, int y, int orientation);

void genarateWall(int matriz[SPRITE_HEIGHT][SPRITE_WIDHT]);

int conferePosicao(int x, int y, int matriz[SPRITE_HEIGHT][SPRITE_WIDHT]);

void changeLife(status *lifeStatus, int value);

void chatchSword(status *swordStatus, int arraySword[3]);

void killBoss(int x_player, int y_player, boss *bossBill);

int fireBallsMove(boss *bossBill, fireBall fireBalls[5], int *counter, int mapArray[SPRITE_HEIGHT][SPRITE_WIDHT], int x_player, int y_player, int imune);

void attackBoss(boss *bossBill, int *counter, fireBall fireBalls[5]);

void drawBoss(boss *bossBill, int *counter);

void drawSword(int arraySword[3]);

void drawMonsters(int MonstersArray[5][MONSTERS_COLLUM], int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT]);

void drawLifes(int LifeArray[5][3]);

void readHighscores(score highscores[5]);

void showHighScores(score highscores[5]);

int gameOver();

int callMenu(int gameInProgress, int *continueGame, score highscores[5]);

void generateMap(char path[10], int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], int MonsterArray[5][MONSTERS_COLLUM], int SwordArray[3], int LifesArray[5][3], int *x_player, int *y_player, boss *bossBill);

int updateScores(score highscores[5], score new_score);

void newScore(score highscores[5], int playerScore);

int StartGame();

#endif
