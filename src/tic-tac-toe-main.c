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

int main(){
    Game *match;
    int movementeCount = 1, position = 0, verifyVictory = 0, player = 0;

    match = malloc(sizeof(Game));

    createGameMatch(match);

    gameSetup(match);

    do{
        printGameBoard(match->gameboard);

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

        if(verifyVictory == 1){
            printGameBoard(match->gameboard);

            printf("Congratulations %s you win!\n", match->players[player].name);
            break;
        }

        movementeCount++;
    }while(movementeCount <= 9);

    if(movementeCount == 10){
        printGameBoard(match->gameboard);
        printf("It is a tie!\n");
    }

    cleanGame(match);

    return 0; 
}