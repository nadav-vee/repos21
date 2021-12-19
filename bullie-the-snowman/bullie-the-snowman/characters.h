#include "const.h"

typedef struct buli
{
	int dir; // stores the current direction for when 0 is pressed
	int points; // a counter for how many points collected
	int won; // a binary variable to indicate win
	int pos[2]; // current position stored in a tuple
	int oldpos[2]; // old position for the bear to chase
}bullie;

typedef struct Snail_bear
{
	char tile; // stores the cuurent tile that the bear stands on
	int won; // a binary variable to indicate a loss
	int pos[2]; // current position stored in a tuple
}Dov;

typedef struct Board
{
	char board[GAME_BOARD_SIZE][GAME_BOARD_SIZE]; // the board itself
	int points_av = GAME_BOARD_SIZE * GAME_BOARD_SIZE; // stores the amount of point available
}gameBoard;

typedef struct sgame
{
	int start; // binary var, only starts when this turns to one
	bullie bul; // one player
	Dov bear; // one enemy
	gameBoard board; // a board
}game;


void Dov_move_calc(game* g, int* pos);

void Dov_Move(game* g);

void Bullie_move_calc(game* g, int dir, int* pos);

void Bullie_Move(game* g);
