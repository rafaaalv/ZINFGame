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

void loadSoundsAndMusics();

void unloadSoundsAndMusics();

void loadTexturesMenus();

void generateTextures();

void unloadTexturesMenus();

void unloadTextures();

void underlineText(char *string, int x, int y, int size, Color inSideColor, Color outColor);

void ShowTopBar(game gameTopBarStatus);

void generateArrayMap(char path[20], int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT]);

void generateMap(char path[20], int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame, fireBall fireBalls[5]);

int menu(int gameInProgress, player *gamePlayer);

int gameOver();

void restartStatus(int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame, fireBall fireBalls[5], int *imune_muahaha);

void killMonster(game *InGame,  int monster);

void drawPlayer(player atualPlayer, int counter);

void genarateWall(int matriz[SPRITE_HEIGHT][SPRITE_WIDHT]);

int allMonstersKilled(monster monsters[MAX_MONSTERS]);

int nextLevel(status *atualStatus, char file[20], int *muahaha, char test[8]);

void changeLife(status *lifeStatus, int value);

int checkBossArea(int x, int y, int matriz[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame);

int checkPosition(int x, int y, int matriz[SPRITE_HEIGHT][SPRITE_WIDHT]);

int existMonster(game *InGame,  int matriz[SPRITE_HEIGHT][SPRITE_WIDHT]);

int attackMonster(game *InGame);

void chatchSword(game *InGame);

void drawSword(game *InGame);

void bossDificultMode(boss *bossBill, int *counter);

void killBoss(game *InGame, int *counter);

int fireBallsMove(game *InGame, fireBall fireBalls[5], int *counter, int mapArray[SPRITE_HEIGHT][SPRITE_WIDHT], player atualPlayer, int imune_muahaha);

int attackContactBoss(game *InGame);

void attackBoss(boss *bossBill, int *counter, fireBall fireBalls[5]);

void drawBoss(boss *bossBill, int *counter);

void drawMonsters(monster monsters[MAX_MONSTERS], int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], int *monsterCounter, game *InGame);

void drawLifes(life lifes[MAX_LIFES]);

void drawConfetti(int indconf);

int winGame();

void showHighScores(score highscores[5]);

void saveGame(save saveSave, game *InGame);

void loadGame(save loadSave, int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame);

void saves(int option, int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame);

int callMenu(int gameInProgress, int *continueGame, score highscores[5], int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT], game *InGame);

void readHighscores(score highscores[5]);

int updateScores(score highscores[5], score new_score);

void newScore(score highscores[5], int playerScore);

void muahaha(int *imune_muahaha, char test[8]);

void StartGame();

#endif
