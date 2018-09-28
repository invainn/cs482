#include <tictac_support.h>
#include <stdio.h>
#include <iostream>
#include <climits>

bool check_if_board_empty(int board[][3]) {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(board[i][j] != 0) {
				return false;
			}
		}
	}

	return true;
}

bool check_if_board_full(int board[][3]) {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(board[i][j] == 0) {
				return false;
			}
		}
	}

	return true;
}

/**
	make_move: takes a board state and makes a legal 
	(hopefully optimal) move

	args:
		int [][3] board: 3x3 array of ints representing the 
		board state. The values of board are altered based
		on the move
			0: empty
			1: x
		 -1: o
		
	returns (int):
		the number of steps it took to choose the best move
		(current implementation returns 1 by default, 0 if no move made)
**/

int make_move_helper( int board[][3], int depth, bool maximizing, int player1, int player2 )
{

	// we check winning state of both sides
	int result = check_winning_state(board, player1, player2);

	if(result != 0) {
		return result;
	}

	if(check_if_board_full(board)) {
		return 0;
	}

	if(maximizing) {
		int max_num = INT_MIN;

		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				if(board[i][j] == 0) {
					// make move for minimax
					board[i][j] = player1;

					max_num = std::max(max_num, make_move_helper(board, depth+1, !maximizing, player1, player2));

					board[i][j] = 0;
				}
			}
		}

		return max_num;
	} else {
		int min_num = INT_MAX;

		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				if(board[i][j] == 0) {
					board[i][j] = player2;

					min_num = std::min(min_num, make_move_helper(board, depth+1, !maximizing, player1, player2));

					board[i][j] = 0;
				}
			}
		}

		return min_num;
	}
}

int make_move(int board[][3]) {
	// figure out what move it is
	int state = 0;
	for( int i = 0; i < 3; i++ )
		for( int j = 0; j < 3; j++ )
			state += board[i][j];

	state = -state;
	if( state == 0 )
		state = 1;
	
	int max = INT_MIN;
	int max_row = 0;
	int max_col = 0;

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(board[i][j] == 0) {
				board[i][j] = state;

				int value = make_move_helper(board, 0, false, state, -state);

				board[i][j] = 0;

				if(value > max) {
					max = value;
					max_row = i;
					max_col = j;	
				}
			}
		}
	}	

	board[max_row][max_col] = state;
	return 1;
}

// this could be done better
int check_winning_state(int board [][3], int player1, int player2) {
	for(int i = 0; i < 3; i++) {
		if(board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
			if(board[i][0] == player1) {
				return 5; 
			} else if(board[i][0] == player2) {
				return -5;
			}
		}
	}

	for(int i = 0; i < 3; i++) {
		if(board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
			if(board[0][i] == player1) {
				return 5; 
			} else if(board[0][i] == player2){
				return -5;
			}
		}
	}

	if(board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
			if(board[0][0] == player1) {
				return 5; 
			} else if(board[0][0] == player2){
				return -5;
			}
	}
	
	if(board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
			if(board[0][2] == player1) {
				return 5; 
			} else if(board[0][2] == player2){
				return -5;
			}
	}

	return 0;
}