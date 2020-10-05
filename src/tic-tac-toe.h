#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H
#define MAX_BOARD_SIZE 3
#define MAX_PLAYERS 2

typedef struct player {
    char *name;
    char character;
} Player;

typedef struct game {
    Player *players;
    char **gameboard;
    int gameMode;
} Game;

void createGameMatch(Game *game);

void cleanGame(Game *game);

void defineGameMode(Game *game);

void definePlayers(Game *game);

void printGameBoard(char **board);

int verifyPlayerMove(char **board, int position);

int getPlayerMove(char **board, int position, char character);

#endif
