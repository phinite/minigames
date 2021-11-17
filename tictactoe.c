#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


typedef struct Moves {
	int x;
	int y;
	int player;
}Move;

static char   uc[3][3][2] = { {"a1", "a2", "a3"}, {"b1", "b2", "b3"}, {"c1", "c2", "c3"} };
static char uc_r[3][3][2] = { {"1a", "2a", "3a"}, {"1b", "2b", "3b"}, {"1c", "2c", "3c"} };
static int board[3][3] 	  = { 0 };


void print_board( int board[3][3] );
Move get_move( int board[3][3] ); 
int check_win( Move m, int board[3][3] );



int main() {
	
	Move move;
	move.x = 0;
	move.y = 0;
	move.player = 0;

	int win = 0;
	int turn = 2;
	while ( win == 0 ) {
		print_board(board);
		turn = turn == 1 ? 2 : 1;
		move = get_move(board);
		board[move.y][move.x] = turn;
		move.player = turn;
		win = check_win(move, board);
	}
	printf("Player %d has won! Play again? y/n:   ", turn);
	while ( 1 ) {
		char r = tolower(getchar());
		if ( r == 'y' ) {
			main();
			return 0;
		}
		else if ( r == 'n' ) {
			return 0;
		}
	}
}



void print_board(int board[3][3]) {

	int i, j;
	system("clear");
	for ( i = 0; i <= 2; ++i ) {
		printf(" %c   ", uc[i][0][0]);
		for ( j = 0; j <= 2; ++j ) {
			switch( board[i][j] ) {
				case 1: 
					printf(" X ");
					break;
				case 2:
					printf(" O ");
					break;
				default:
					printf("   ");
			}
			if ( j <= 1  ) printf("|");
			else if (i != 2) printf("\n     ____________\n");
		}
		j = 0;
	}
	printf("\n\n      1   2   3\n");
	return;
}



Move get_move( int board[3][3] ) {
	
	Move m;
	char input[2];
	char c;
	int i,j,x;

	printf("\n\n> ");
	x = 0;
	while ( (c = getchar()) != '\n' ) {
		if ( x > 1 ) {
			printf("invalid move. Please enter a coord\n");
			m = get_move(board);
		}
		input[x] = tolower(c);
		++x;
	}
	if ( x < 1 ) {
		printf("Invalid move");
		m = get_move(board);
	}

	for ( i = 0; i <= 2; ++i ) {
		for ( j = 0; j <= 2; ++j ) {
			// compares user input to a list of valid user input then sets coords
			if ( strncmp(input, uc[i][j], sizeof(input)) == 0 || strncmp(input, uc_r[i][j], sizeof(input)) == 0 ) {
				if ( board[i][j] == 0 ) {
					m.x = j;
					m.y = i;
					return m;
				}
				printf("Invalid move");
				return get_move(board);
			}
		}
		j = 0;
	}
	printf("Didn't recognize move. Please try again.");
	return get_move(board);
}


int check_win( Move m, int board[3][3] ) {
	
	// The board is 3x3 and all the center rows are x or y 1. These two determine how many 1s are in 
	// last move and all of the adjacent tiles.
	int a_cnt = 0;
	int p_cnt = m.x == 1 && m.y == 1 ? 2 : m.x == 1 || m.y == 1 ? 1 : 0;

	int i,j,a,b;
	for ( i = 0; i <= 2; ++i ) {
		for ( j = 0; j <= 2; ++j ) {
			// Check if tile is adjacent
			if ( abs( i - m.y ) < 2 && abs( j - m.x ) < 2 ) {
				// Check if tile is the same player and is not on the same square
				if ( board[i][j] == m.player && ( i == m.y && j == m.x ) != 1 ) {
					a_cnt = j == 1 && i == 1 ? 2 : j == 1 || i == 1 ? 1 : 0;
					if ( p_cnt > a_cnt ) {
						// (pos-adj)+pos
						a = m.x - j;
						b = m.y - i;
						a = a + m.x;
						b = b + m.y;
						if ( board[b][a] == m.player ) {
							return m.player;
						}
					} else if ( p_cnt < a_cnt ) {
						// (adj-pos)+adj
						a = j - m.x;
						b = i - m.y;
						a = a + j;
						b = b + i;
						if ( board[b][a] == m.player ) {
							return m.player;
						}
					} else {
						return 0;
					}
				}
			}
		}
		j = 0;
	}
	return 0;
}

