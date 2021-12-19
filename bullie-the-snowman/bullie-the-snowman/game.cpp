#include "const.h"
#include "game.h"

void board_init(game* g)
{
	int c = 1, r = 1;
	g->board.points_av = GAME_BOARD_SIZE * GAME_BOARD_SIZE;
	for (int i = 0; i < GAME_BOARD_SIZE; i++)
	{
		for (int j = 0; j < GAME_BOARD_SIZE; j++)
		{
			g->board.board[i][j] = '.';
		}
	}
	printf("Please provide game borders\n");
	scanf("%d %d", &r, &c);
	while (r != 0 && c != 0)
	{
		printf("Please provide game borders\n");
		g->board.board[r - 1][c - 1] = '*';
		scanf("%d %d", &r, &c);
		g->board.points_av--;
	}
	do
	{
	printf("Please provide Bullie position\n");
	scanf("%d %d", &r, &c);
	if (g->board.board[r - 1][c - 1] == '*' || r > GAME_BOARD_SIZE || c > GAME_BOARD_SIZE)
		printf("There's a wall\n");
	} while (g->board.board[r - 1][c - 1] == '*' || r > GAME_BOARD_SIZE || c > GAME_BOARD_SIZE);
	g->board.board[r - 1][c - 1] = 'B';
	g->bul.pos[0] = r - 1;
	g->bul.pos[1] = c - 1;
	g->bul.oldpos[1] = r - 1;
	g->bul.oldpos[1] = c - 1;
	g->bul.dir = 0;
	g->bul.points = 1;
	g->bul.won = 0;

	do
	{
	printf("Please provide D (snail bear) position\n");
	scanf("%d %d", &r, &c);
	if (g->board.board[r - 1][c - 1] == '*' || g->board.board[r - 1][c - 1] == 'B')
		printf("position taken by either bullie or a wall\n");
	} while (g->board.board[r - 1][c - 1] == '*' || g->board.board[r - 1][c - 1] == 'B');
	g->board.board[r - 1][c - 1] = 'D';
	g->bear.pos[0] = r - 1;
	g->bear.pos[1] = c - 1;
	g->bear.tile = '.';
	g->start = 0;
	g->bear.won = 0;
	
	board_display(g);
}

void board_display(game* g)
{
	printf("score: %d\nout of: %d\n", g->bul.points, g->board.points_av);
	for (int i = 0; i < GAME_BOARD_SIZE; i++)
	{
		for (int j = 0; j < GAME_BOARD_SIZE; j++)
		{
			printf("| %c", g->board.board[i][j]);
		}
		printf("|\n");
	}

	
}

void Game()
{
	game* g = (game*)malloc(sizeof(game));
	board_init(g);
	while (!g->bul.won && !g->bear.won)
	{
		Bullie_Move(g);
		Dov_Move(g);
		board_display(g);
	}
	if (g->bul.won)
		printf("\n~%10| You Win! |%10~\n");
	else
		printf("\n~%10| You lost :( |%10~\n");
}
