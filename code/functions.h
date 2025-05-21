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


void ShowTopBar(int lifes, int level, int score, int sword);

int menu(int gameInProgress);

void drawPlayer(int x, int y, int orientation);

void genarateWall(int matriz[16][24]);

int conferePosicao(int x, int y, int matriz[16][24]);

void drawMonsters(int MonstersArray[5][4], int MapArray[16][24]);

void drawLifes(int LifeArray[5][3]);

void generateTextures();

void unloadTextures();

void generateMap(char path[10], int MapArray[16][24], int MonsterArray[5][4], int SwordArray[3], int LifesArray[5][3], int *x_player, int *y_player);

int StartGame();

#endif
