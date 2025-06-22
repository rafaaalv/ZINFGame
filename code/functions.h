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

void underlineText(char string[50], int x, int y, int size, Color inSideColor, Color outColor);

void ShowTopBar(game gameTopBarStatus);

int menu(int gameInProgress, player *gamePlayer);

int attackMonster(game *InGame);

void restartStatus(int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame, fireBall fireBalls[5], int *imune_muahaha);

void killMonster(game *InGame,  int monster);

void drawPlayer(player atualPlayer, int counter);

void genarateWall(int matriz[SPRITE_HEIGHT][SPRITE_WIDHT]);

int checkBossArea(int x, int y, int matriz[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame);

int checkPosition(int x, int y, int matriz[SPRITE_HEIGHT][SPRITE_WIDHT]);

int existMonster(game *InGame,  int matriz[SPRITE_HEIGHT][SPRITE_WIDHT]);

int allMonstersKilled(monster monsters[MAX_MONSTERS]);

void changeLife(status *lifeStatus, int value);

void chatchSword(game *InGame);

void killBoss(game *InGame, int *counter);

int fireBallsMove(game *InGame, fireBall fireBalls[5], int *counter, int mapArray[SPRITE_HEIGHT][SPRITE_WIDHT], player atualPlayer, int imune_muahaha);

void attackBoss(boss *bossBill, int *counter, fireBall fireBalls[5]);

int attackContactBoss(game *InGame);

void drawBoss(boss *bossBill, int *counter);

void drawSword(game *InGame);

void drawMonsters(monster monsters[MAX_MONSTERS], int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], int *monsterCounter, game *InGame);

void drawLifes(life lifes[MAX_LIFES]);

void readHighscores(score highscores[5]);

void showHighScores(score highscores[5]);

void saveGame(save saveSave, game *InGame);

void loadGame(save loadSave, int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame);

void saves(int option, int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame);

int gameOver();

int callMenu(int gameInProgress, int *continueGame, score highscores[5], int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame);

void generateMap(char path[20], int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame, fireBall fireBalls[5]);

int updateScores(score highscores[5], score new_score);

void newScore(score highscores[5], int playerScore);

void muahaha(int *imune_muahaha, char test[8]);

void StartGame();

#endif
