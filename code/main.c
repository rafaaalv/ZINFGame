#include "raylib.h"
#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int main()
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
    InitWindow(LARGURA, ALTURA, "ZINFAGEDON"); //Inicializa janela, com certo tamanho e titulo
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
            if(monsterCounter%4 == 0){
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
                    PlaySound(nextLevelSound);
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
    unloadTextures(); //Descarrega as texturas para liberar espaco na memoria
    return 0;
}
