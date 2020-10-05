#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tic-tac-toe.h"

void gameSetup(Game *game){
    defineGameMode(game); 
    definePlayers(game);
}

int getPosition(char **board, char *name){
    int position = 0;

    do{
        position = 0;
        while ((position < 1 || position > 9)){
            printf("\nPlayer %s is your turn, select a position:\n-> ", name);
            scanf("%d", &position);

            printf("\n");
        }
    }while(verifyPlayerMove(board, position));
    
    return position;
}

int getBotPositiom(char **board){
    int position =  1 + (rand() % 9);

    while (verifyPlayerMove(board, position)){
        position = 1 + (rand() % 9);
    }
     
    return position;
}

int checkVictory(Game *match, int verifyVictory, int player){
    if(verifyVictory == 1){
        printGameBoard(match->gameboard);
        printf("Congratulations %s you win!\n", match->players[player].name);

        return 1;
    }

    return 0;
}

int runGame(Game *match, int movementeCount){
    int verifyVictory = 0, player = 0, position = 0;

    if(movementeCount % 2 == 1){
        position = getPosition(match->gameboard, match->players[0].name);

        verifyVictory = getPlayerMove(match->gameboard, position, match->players[0].character);
        player = 0;
    }
    else{
        if(match->gameMode == 1){
            printf("\nIt is the bot's turn\n");
            position = getBotPositiom(match->gameboard);
        }   
        else{
            position = getPosition(match->gameboard, match->players[1].name);
        }
        
        verifyVictory = getPlayerMove(match->gameboard, position, match->players[1].character);

        player = 1;
    }

    return checkVictory(match, verifyVictory, player);
}

void checkTie(Game *match, int movementeCount){
    if(movementeCount == 10){
        printGameBoard(match->gameboard);
        printf("It is a tie!\n");
    }
}

int main(){
    Game *match;
    int movementeCount = 1;

    match = malloc(sizeof(Game));

    createGameMatch(match);

    gameSetup(match);

    do{
        printGameBoard(match->gameboard);

        if(runGame(match, movementeCount)){
            break;
        }

        movementeCount++;
    }while(movementeCount <= 9);

    checkTie(match, movementeCount);   

    cleanGame(match);

    return 0; 
}