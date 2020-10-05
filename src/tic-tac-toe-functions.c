#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tic-tac-toe.h"

void createGameMatch(Game *game){
    int count = 0;

    game->gameboard = malloc(MAX_BOARD_SIZE * sizeof(char *));

    game->players = malloc(MAX_PLAYERS * sizeof(Player));

    for(int i = 0; i < MAX_BOARD_SIZE; i++)
        game->gameboard[i] = malloc(MAX_BOARD_SIZE * sizeof(char));

    for(int i = 0; i < MAX_PLAYERS; i++){
        game->players[i].name = malloc(25 * sizeof(char));
        strcpy(game->players[i].name, "");

        if(i == 0)
            game->players[i].character = 'X';
        else
            game->players[i].character = 'O';
    }
 
    for(int i = 0; i < MAX_BOARD_SIZE; i++){
        for(int j = 0; j < MAX_BOARD_SIZE; j++){
            game->gameboard[i][j] = '1' + count;
            count++;
        }
    }
}

void defineGameMode(Game *game){
    int answer = 0;

    do{
        printf("Select the game mode:\n1 -> Single Player\n2 -> Multiplayer\n---> ");
        scanf("%d", &answer);
        printf("\n\n");
    }while(answer != 1 && answer != 2);

    game->gameMode = answer;
}

void getPlayerName(Game *game, int x){
    printf("Player '%c' what is your name:\n--> ", game->players[x].character);
    scanf("%s", game->players[x].name);
}

void definePlayers(Game *game){
    if(game->gameMode == 2){
        for(int x = 0; x < MAX_PLAYERS; x++){
            getPlayerName(game, x);
            printf("\n");
        }
    }
    else{
        getPlayerName(game, 0);
        strcpy(game->players[1].name, "BOT");
    }
}

void printGameBoard(char **board){
    for(int i = 0; i < MAX_BOARD_SIZE; i++){
        for(int j = 0; j < MAX_BOARD_SIZE; j++){
            printf("_%c_", board[i][j]);
        }
        printf("\n");
    }
}

int vetifyLines(char **board, char character){
    int count = 0;

    for(int i = 0; i < MAX_BOARD_SIZE; i++){
        for(int j = 0; j < MAX_BOARD_SIZE; j++){
            if(board[i][j] == character)
                count++;
            else
                break;
        }

        if(count == MAX_BOARD_SIZE)
            return 1;
        else
            count = 0;
    }

    return 0;
}

int vetifyColumns(char **board, char character){
    int count = 0;

    for(int i = 0; i < MAX_BOARD_SIZE; i++){
        for(int j = 0; j < MAX_BOARD_SIZE; j++){
            if(board[j][i] == character)
                count++;
            else
                break;
        }

        if(count == MAX_BOARD_SIZE)
            return 1;
        else
            count = 0;
    }

    return 0;
}

int vetifyDiagonal(char **board, char character){
    int count = 0, k = MAX_BOARD_SIZE - 1;

    for(int i = 0; i < MAX_BOARD_SIZE; i++){
        if(board[i][i] == character)
            count ++;
        else
            break;
    }

    if(count == MAX_BOARD_SIZE)
        return 1;

    count = 0;

    for(int i = 0; i < MAX_BOARD_SIZE; i++){
        if(board[i][k - i] == character)
            count ++;
        else
            break;
    }

    if(count == MAX_BOARD_SIZE)
        return 1;

    return 0;
}

int vetifyVictory(char **board, char character){
    if(vetifyColumns(board, character) || vetifyLines(board, character) || vetifyDiagonal(board, character))
        return 1;

    return 0;
}

int getPlayerMove(char **board, int position, char character){
    int line = 0, column = 0;

    line = (position - 1) / (MAX_BOARD_SIZE);
    column = (position - 1) % (MAX_BOARD_SIZE);

    board[line][column] = character;

    return vetifyVictory(board, character);
}

int verifyPlayerMove(char **board, int position){
    int line = 0, column = 0;

    line = (position - 1) / (MAX_BOARD_SIZE);
    column = (position - 1) % (MAX_BOARD_SIZE);

    if(board[line][column] == 'X' || board[line][column] == 'O')
        return 1;
    
    return 0;
}

void cleanGame(Game *game){
    for(int i = 0; i < 3; i++)
        free(game->gameboard[i]);
    
    for(int i = 0; i < 2; i++)
        free(game->players[i].name);

    free(game->gameboard);
    free(game->players);
    free(game);
}