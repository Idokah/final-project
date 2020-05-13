#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Header.h"



int main(){

	Move*  move1 = (Move*)malloc(sizeof(Move));
	move1->cols = 1;
	move1->rows = 1;
	movesArray movesArr;
	movesArr.size = 1;
	movesArr.moves = move1 ;
	movesArray **moves = (movesArray **)malloc(sizeof(movesArray*)*N);
	for (int row = 0; row < N; row++) {
		moves[row] = (movesArray *)malloc(sizeof(movesArray)*M);
		for (int col = 0; col < M ; col++) {
			moves[row][col].moves = move1;
			moves[row][col].size = 1 ;
		}
	}

	char **board = (char **)malloc(sizeof(char *)*N);
	for (int row = 0; row < N; row++) {
		board[row] = (char *)malloc(sizeof(char)*M);
		for (int col = 0; col < M; col++) {
			if (col>=3) board[row][col] = '*';
			else board[row][col] = ' ';
		}
	}
	boardPosArray** BPosArray=validMoves(moves, board);
	
	printboard();
}
