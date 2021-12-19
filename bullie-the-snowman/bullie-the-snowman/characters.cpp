#include "characters.h"

enum matrix_handle { R, C };
/// calc for the new bear position
///  
/// the funcion calculates the new position of the bear and 
/// returns with call by reference the new position in the
/// parameter *pos
/// parameters:
///		"g": the main struct of the game. stores all values
///		"pos": the return position using call by reference
void Dov_move_calc(game* g, int* pos)
{
	int tmp_pos[2];

	if (g->bul.oldpos[R] - g->bear.pos[R] < 0)
		tmp_pos[R] = g->bear.pos[R] - 1;
	else if (g->bul.oldpos[R] - g->bear.pos[R] > 0)
		tmp_pos[R] = g->bear.pos[R] + 1;
	else
		tmp_pos[R] = g->bear.pos[R];

	if (g->bul.oldpos[C] - g->bear.pos[C] < 0)
		tmp_pos[C] = g->bear.pos[C] - 1;
	else if (g->bul.oldpos[C] - g->bear.pos[C] > 0)
		tmp_pos[C] = g->bear.pos[C] + 1;
	else
		tmp_pos[C] = g->bear.pos[C];
	
	if (g->board.board[tmp_pos[R]][tmp_pos[C]] == '*' || !g->start)
	{
		pos[R] = g->bear.pos[R];
		pos[C] = g->bear.pos[C];
	}
	else
	{
		pos[R] = tmp_pos[R];
		pos[C] = tmp_pos[C];
	}
}
/// bear move func
/// 
/// gets: the main struct g
/// returns: changes the position of the bear
/// <param name="g"></param>
void Dov_Move(game* g)
{
	int newpos[2];
	Dov_move_calc(g, newpos);
	g->board.board[g->bear.pos[R]][g->bear.pos[C]] = g->bear.tile;
	g->bear.tile = g->board.board[newpos[R]][newpos[C]];
	if (g->board.board[newpos[R]][newpos[C]] == 'B')
	{
		g->bear.won = 1;
	}
	g->board.board[newpos[R]][newpos[C]] = 'D';
	g->bear.pos[R] = newpos[R];
	g->bear.pos[C] = newpos[C];
}


void Bullie_move_calc(game* g, int dir, int* pos)
{
	switch ((dir != 0) ? dir : g->bul.dir)
	{
	case 1: // right 
	{
		if (g->board.board[pos[R]][pos[C] + 1] == '*' || (pos[C] + 1) > GAME_BOARD_SIZE - 1)
		{
			break;
		}
		if (g->board.board[pos[R]][pos[C] + 1] == '.' || g->board.board[pos[R]][pos[C] + 1] == 'o')
		{
			pos[R] = pos[R];
			pos[C] = pos[C] + 1;
		}
		g->bul.dir = (dir != 0) ? dir : g->bul.dir;
		break;
	}
	case 2: // left
	{
		if (g->board.board[pos[R]][pos[C] - 1] == '*' || (pos[C] - 1) < 0)
		{
			break;
		}
		if (g->board.board[pos[R]][pos[C] - 1] == '.' || g->board.board[pos[R]][pos[C] - 1] == 'o')
		{
			pos[R] = pos[R];
			pos[C] = pos[C] - 1;
		}
		g->bul.dir = (dir != 0) ? dir : g->bul.dir;
		break;
	}
	case 3: // up
	{
		if (g->board.board[pos[R] - 1][pos[C]] == '*' || (pos[R] - 1) < 0)
		{
			break;
		}
		if (g->board.board[pos[R] - 1][pos[C]] == '.' || g->board.board[pos[R] - 1][pos[C]] == 'o')
		{
			pos[R] = pos[R] - 1;
			pos[C] = pos[C];
		}
		g->bul.dir = (dir != 0) ? dir : g->bul.dir;
		break;
	}
	case 4: // down
	{
		if (g->board.board[pos[R] + 1][pos[C]] == '*' || (pos[R] + 1) > GAME_BOARD_SIZE - 1)
		{
			break;
		}
		if (g->board.board[pos[R] + 1][pos[C]] == '.' || g->board.board[pos[R] + 1][pos[C]] == 'o')
		{
			pos[R] = pos[R] + 1;
			pos[C] = pos[C];
		}
		g->bul.dir = (dir != 0) ? dir : g->bul.dir;
		break;
	}
	}
}

void Bullie_Move(game* g)
{
	int newpos[2];
	newpos[R] = g->bul.pos[R];
	newpos[C] = g->bul.pos[C];
	int temp_dir;
	printf("\n 1 = right\n 2 = left\n 3 = up\n 4 = down\n");
	scanf("%d", &temp_dir);
	if (temp_dir == 0 && g->bul.dir == 0)
	{
		return;
	}
	else
	{
		g->start = 1;
		if (temp_dir != 0)
		{
			g->bul.dir = temp_dir;
		}
		Bullie_move_calc(g, temp_dir, newpos);
	}
	if (g->board.board[newpos[R]][newpos[C]] == '.')
	{
		g->bul.points++;
	}
	g->board.board[g->bul.pos[R]][g->bul.pos[C]] = 'o';
	g->board.board[newpos[R]][newpos[C]] = 'B';
	g->bul.oldpos[R] = g->bul.pos[R];
	g->bul.oldpos[C] = g->bul.pos[C];
	g->bul.pos[R] = newpos[R];
	g->bul.pos[C] = newpos[C];
	if (g->bul.points == g->board.points_av)
	{
		g->bul.won = 1;
	}
}