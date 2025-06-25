#include "raylib.h"
#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int main()
{
    status InGameStatus; //DECLARA O STATUS DO JOGO
    game InGame; //DECLARA O JOGO
    monster monsters[MAX_MONSTERS]; //DECLARA OS MONSTROS
    score Highscores[5]; //DECLARA OS SCORES
    fireBall fireBalls[5]; //DECLARA AS FIREBALLS
    boss bossBill; //DECLARA O BOSS
    player atualPlayer; //DECLARA O PLAYER
    sword atualSword; //DECLARA A ESPADA
    life lifes[MAX_LIFES]; //DECLARA AS VIDAS
    int MapArray[SPRITE_HEIGHT][SPRITE_WIDHT]; //DECLARA UMA MATRIZ QUE REPRESENTA O MAPA
    int i, j;
    int gameOption; //DECLARA UMA VARIAVEL QUE REPRESENTA A OPCAO DE JOGO ATUAL (1 = GAME OVER; 2 = GANHOU O JOGO; 3 = MENU)
    int continueGame = 1; //DECLARA UMA VARIAVEL QUE PODE SER 1(O JOGO DEVE CONTINUAR) OU 0 (O JOGO DEVE PARAR)
    int MenuAnswer; //DECLARA UMA VARIAVEL QUE REPRESENTA A RESPOSTA DO MENU
    int imuneCounter = 0; //DECLARA UM CONTADOR UTILIZADO NA IMUNIDADE DO PLAYER
    int x_player, y_player; //DECLARA VARIAVEIS PARA AS COORDENADAS X E Y DO PLAYER
    int orientation = 1; //DECLARA UMA VARIAVEL PARA A ORIENTACAO DO PLAYER (COMECA NO 1 (LESTE))
    int monsterKilled; //DECLARA UMA VARIAVEL PARA SALVAR O INDICE DE UM MONSTRO MORTO
    int bossCounter = 0; //DECLARA UM CONTADOR UTILIZADO PARA O ATAQUE DO BOSS
    int imune_muahaha = 0; //DECLARA UMA VARIAVEL QUE PODE SER 1(O CHEAT MUAHAHA FOI ATIVADO) OU 0 (O CHEAT NAO FOI ATIVADO)
    int moveCounter = 0; //DECLARA UM CONTADOR UTILIZADO PARA A MOVIMENTACAO DOS MONSTROS E DO PLAYER
    char atualFile[20]; //DECLARA UMA STRING QUE REPRESENTA O CAMINHO PARA O ARQUIVO DO MAPA ATUAL
    char test[8] = {0,0,0,0,0,0,0,'\0'}; //DECLARA UMA STRING DE TESTE PARA CONFERIR O CHEAT DO MUAHAHA

    InGame.atualPlayer = atualPlayer;
    InGame.atualStatus = InGameStatus;
    memcpy(InGame.monsters, monsters, sizeof(monster) * MAX_MONSTERS);
    InGame.atualSword = atualSword;
    memcpy(InGame.lifes, lifes, sizeof(life) * MAX_LIFES);
    InGame.bossBill = bossBill;

    srand(time(NULL));

    InGame.atualPlayer.person = 0; //INICIALIZA O PERSONAGEM COMO O DIPPER
    readHighscores(Highscores); //LE OS HIGHSCORES SALVOS
    restartStatus(MapArray, &InGame, fireBalls, &imune_muahaha); //REINICIA O STATUS
    InitWindow(LARGURA, ALTURA, "ZINFAGEDON"); //Inicializa janela, com certo tamanho e titulo
    InitAudioDevice();
    generateTextures();
    PlayMusicStream(gameMusic);
    SetWindowIcon(iconImage);
    SetTargetFPS(60);// Ajusta a janela para 60 frames por segundo
    callMenu(0, &continueGame, Highscores, MapArray, &InGame);
    while(continueGame){ //ENQUANTO O JOGO CONTINUA
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
            if(moveCounter%4 == 0){// ATUALIZA A POSICAO DO JOGADOR A CADA 4 FRAMES
                InGame.atualPlayer.x = x_player;
                InGame.atualPlayer.y = y_player;
                InGame.atualPlayer.orientation = orientation;
            }
            if(IsKeyPressed(KEY_TAB)){// CHAMA O MENU DE PAUSE
                gameOption = 3;
                break;
            }
            if((InGame.atualSword.alive)&&(InGame.atualSword.x == InGame.atualPlayer.x)&&(InGame.atualSword.y == InGame.atualPlayer.y)){
                chatchSword(&InGame); //SE O JOGADOR ESTIVER NA MESMA POSICAO DA ESPADA, ELE A PEGA
            }
            if(InGame.atualStatus.sword){
                if(IsKeyPressed(KEY_J)){ //SE O JOGADOR ATACAR
                    monsterKilled = existMonster(&InGame, MapArray); //CONFERE SE EXISTE MONSTRO NA AREA DE ATAQUE E SALVA O INDICE DELE, SE EXISITIR
                    if(monsterKilled > -1){ //E SE EXISTIR MONSTRO NA AREA DE ATAQUE
                        killMonster(&InGame, monsterKilled); //MATA O MONSTRO COM O INDICE SALVO
                    }
                    killBoss(&InGame, &bossCounter); //DANIFICA O BOSS, SE TIVER NA AREA DE ATAQUE
                }
            }
            for(i = 0; i < 5; i++){
                    //SE O JOGADOR ESTIVER NA MESMA POSICAO DE ALGUMA DAS VIDAS
                if((InGame.lifes[i].alive)&&(InGame.lifes[i].x == InGame.atualPlayer.x)&&(InGame.lifes[i].y== InGame.atualPlayer.y)){
                    InGame.lifes[i].alive = 0; // A VIDA EH DECLARADA COMO COLETADA
                    PlaySound(lifeSound);
                    changeLife(&InGame.atualStatus, 1); // AUMENTA A VIDA DO JOGADOR EM 1
                }
            }
            if((allMonstersKilled(InGame.monsters))&&(InGame.bossBill.lifes == 0)){//SE TODOS OS MONSTROS E O BOSS FORAM MORTOS
                if(nextLevel(&InGame.atualStatus, atualFile, &imune_muahaha)){ //E SE EXISTIR PROXIMO NIVEL
                    PlaySound(nextLevelSound);
                    generateMap(atualFile, MapArray, &InGame, fireBalls); //GERA O PROXIMO NIVEL
                } else{// SENAO EXISTIR PROXIMO NIVEL
                    gameOption = 2; //GANHOU O JOGO
                    break;
                }
            }
            if(InGame.atualStatus.lifes <= 0){ //SE A VIDA DO JOGADOR FICAR MENOR OU IGUAL A 0
                gameOption = 1; //GAME OVER
                break;
            }
            muahaha(&imune_muahaha, test); //TESTA SE O JOGADOR DIGITOU MUAHAHA
            if(!InGame.atualPlayer.imune && !imune_muahaha){ //SE O JOGADOR NAO ATIVOU O CHEAT MUAHAHA E NAO ESTA IMUNE
                if(attackMonster(&InGame) || attackContactBoss(&InGame)){ //E SE O MONSTRO OU O BOSS ATACARAM O JOGADOR
                    InGame.atualPlayer.imune = 1; //O PLAYER GANHA IMUNIDADE
                    imuneCounter = 0; //E O CONTADOR DA IMUNIDADE EH ZERADO
                }
            }
            else imuneCounter++; //SE O JOGADOR NAO ESTIVER IMUNE, O CONTADOR DE IMUNIDADE AUMENTA
            if(imuneCounter > 119) //SE O PLAYER ESTEVE IMUNE POR 2 SEGUNDOS,
                InGame.atualPlayer.imune = 0; //O PLAYER PERDE A IMUNIDADE
            if(fireBallsMove(&InGame, fireBalls, &bossCounter, MapArray, imune_muahaha)){ //SE UMA BOLA DE FOGO ATINGIR O PLAYER
                InGame.atualPlayer.imune = 1; // O PLAYER GANHA IMUNIDADE
                imuneCounter = 0; //E O CONTADOR DA IMUNIDADE EH ZERADO
                if(InGame.bossBill.attack == 3){ //SE O BOSS ESTIVER NO MODO INICIAL,
                    changeLife(&InGame.atualStatus, -2); //O PLAYER PERDE DUAS VIDAS
                    if(InGame.atualPlayer.x >= 2*SPRITE_SIZE) // E SE O PLAYER ESTIVER A MAIS DE DOIS SPRITES LONGE DO LADO ESQUERDO DA TELA,
                    InGame.atualPlayer.x -= 2*SPRITE_SIZE; // O PLAYER VOLTA DOIS SPRITES PARA A ESQUERDA
                    else if(InGame.atualPlayer.x >= SPRITE_SIZE) //SENÃO, SE O PLATER ESTIVER A MAIS DE UM SPRITE LONGE DO LADO ESQUERDO DA TELA,
                    InGame.atualPlayer.x -= SPRITE_SIZE; //O PLAYER VOLTA UM SPRITE PARA A ESQUERDA
                }
                else{ //SE O BOSS ESTIVER NO MODO DIFICIL,
                    changeLife(&InGame.atualStatus, -3); //O PLAYER PERDE TRES VIDAS
                    if(InGame.atualPlayer.x >= 2*SPRITE_SIZE) // E SE O PLAYER ESTIVER A MAIS DE DOIS SPRITES LONGE DO LADO ESQUERDO DA TELA,
                    InGame.atualPlayer.x -= 2*SPRITE_SIZE; // O PLAYER VOLTA DOIS SPRITES PARA A ESQUERDA
                    else if(InGame.atualPlayer.x >= SPRITE_SIZE) //SENÃO, SE O PLATER ESTIVER A MAIS DE UM SPRITE LONGE DO LADO ESQUERDO DA TELA,
                    InGame.atualPlayer.x -= SPRITE_SIZE; //O PLAYER VOLTA UM SPRITE PARA A ESQUERDA
                }
            }
            if(checkBossArea(x_player, y_player, MapArray, &InGame)){ //SE O PLAYER INVADIR A AREA DO BOSS,
                InGame.atualPlayer.x -= 4*SPRITE_SIZE; //O PLAYER VOLTA 4 SPRITES PARA A ESQUERDA
                changeLife(&InGame.atualStatus, -1); //E PERDE UMA VIDA
            }
            drawPlayer(InGame.atualPlayer, moveCounter); //DESENHA O PLAYER
            genarateWall(MapArray); //GERA AS PAREDES
            drawBoss(&InGame.bossBill, &bossCounter); // DESENHA O BOSS
            attackBoss(&InGame.bossBill, &bossCounter, fireBalls); //O BOSS ATACA
            drawMonsters(MapArray, &moveCounter, &InGame);// DESENHA OS MONSTROS
            drawLifes(InGame.lifes);// DESENHA AS VIDAS
            drawSword(&InGame); //DESENHA A ESPADA
            ShowTopBar(InGame); //EXIBE A TOPBAR
            BeginDrawing(); //Inicia o ambiente de desenho na tela
            EndDrawing(); //Finaliza o ambiente de desenho na tela
            ClearBackground(WHITE);
        }
        //CHAMA AS FUNCOES BASEADO NA RESPOSTA DO USUARIO DOS MENUS DE GAME OVER, GANHOU O JOGO OU MENU DE PAUSE
        switch(gameOption){// 1 -> game over, 2 -> ganhou, 3 -> menu de pause
            case 1:
                MenuAnswer = gameOver(); //MENU DE GAME OVER
                if(MenuAnswer == 0){
                    restartStatus(MapArray, &InGame, fireBalls, &imune_muahaha); //REINICIA O JOGO
                } else if(MenuAnswer == 1){
                    saves(1, MapArray, &InGame); //CARREGA UM JOGO SALVO
                } else if(MenuAnswer == 2){
                    if(callMenu(0, &continueGame, Highscores, MapArray, &InGame)){ //VOLTA PARA O MENU INICIAL
                        restartStatus(MapArray, &InGame, fireBalls, &imune_muahaha);
                    }
                } else {
                    continueGame = 0; //SAI DO JOGO
                }
                break;
            case 2:
                MenuAnswer = winGame(); //GANHOU O JOGO
                if(MenuAnswer == 0){ //INICIAR NOVO JOGO
                    newScore(Highscores, InGame.atualStatus.score); //TESTA O NOVO SCORE OBTIDO
                    restartStatus(MapArray, &InGame, fireBalls, &imune_muahaha); //REINICIA O JOGO
                } else if(MenuAnswer == 1){ //RETORNAR AO MENU
                    newScore(Highscores, InGame.atualStatus.score); //TESTA O NOVO SCORE OBTIDO
                    if(callMenu(0, &continueGame, Highscores, MapArray, &InGame)){ //RETORNA AO MENU INICIAL
                        restartStatus(MapArray, &InGame, fireBalls, &imune_muahaha);
                    }
                } else { //SAIR DO JOGO
                    newScore(Highscores, InGame.atualStatus.score); //TESTA O NOVO SCORE OBTIDO
                    continueGame = 0; //SAI DO JOGO
                }
                break;
            case 3:
                if(callMenu(1, &continueGame, Highscores, MapArray, &InGame)){ //CHAMA O MENU DE PAUSE
                    restartStatus(MapArray, &InGame, fireBalls, &imune_muahaha);
                }
        }
    }
    CloseWindow(); // Fecha a janela
    unloadTextures(); //Descarrega as texturas para liberar espaco na memoria
    return 0;
}
