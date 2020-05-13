#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>

boardPosArray ** validMoves(movesArray **moves, char **board) {
	boardPosArray** boardPosArr = initNewBoardPosArr();
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < M; col++) {
			validMove(row, col, &(moves[row][col]), board, &(boardPosArr[row][col]));
		}
	}
	return boardPosArr;
}

bool isPosValid(int row, int col, char **board) {
	return (row < N && col < M && row >= 0 && col >= 0 && board[row][col] != '*');
}

void insertToValidPositions(boardPos *validPositions, Move newMove, int pos, int row, int col) {
	validPositions[pos][0] = row + 'A';
	validPositions[pos][1] = (char)col + 1;
}

void insertToNewMovesArray(movesArray* newMovesArr, Move newMove, int logSize, int row, int col) {
	newMovesArr->moves[logSize] = newMove;
	newMovesArr->size = logSize+1;
}

void insertMove(Move newMove, movesArray* newMovesArr, boardPos *validPositions, int *logSize, int *phySize, int row, int col){
	if (*logSize >= *phySize) {
		*phySize *= 2;
		validPositions = (boardPos*)realloc(validPositions, phySize);
		newMovesArr->moves = (Move*)realloc(newMovesArr->moves, *phySize);
	}
	insertToValidPositions(validPositions, newMove, *logSize, row, col);
	insertToNewMovesArray(newMovesArr, newMove, *logSize, row, col);
	(*logSize)++;
}

void validMove(int row, int col, movesArray* moves, char **board, boardPosArray* boardPosArr) {
	int counterPositions = 0;
	int phyPositionsSize = 1;
	movesArray newMovesArr;
	newMovesArr.moves = (Move*)malloc(sizeof(Move));
	boardPos *validPositions = (boardPos*)malloc(sizeof(boardPos));
	for (int i = 0; i < moves->size; i++) {
		int newCol = col + (int)moves->moves[i].cols;
		int newRow = row + (int)moves->moves[i].rows;
		if (isPosValid(newRow, newCol, board)) {
			insertMove(moves->moves[i] , &newMovesArr, validPositions, &counterPositions, &phyPositionsSize, newRow, newCol);
		}
	}
	boardPosArr->size = counterPositions;
	boardPosArr->positions = validPositions;
	*moves = newMovesArr;
}

boardPosArray **initNewBoardPosArr() {
	boardPosArray **newBoardPosArr = (boardPosArray **)malloc(sizeof(boardPosArray*)*N);
	for (int row = 0; row < N; row++) {
		newBoardPosArr[row] = (boardPosArray *)malloc(sizeof(boardPosArray)*M);
	}
	return newBoardPosArr;
}

int display(movesList *moves_list, boardPos start, char **board)
{
	printboard();
}

void printboard()
{
	for (int row = 0; row <= 2*(N+1); row++)
	{
		for (int col = 0; col <= 4*M; col++)
		{

			if (row % 2 == 0 && col % 4 == 0)
				printf("+");
			else if (row % 2 == 0)
				printf("-");
			else if (col % 4 == 0)
				printf("|");
			else if (row == 1 && (col - 2) % 4 == 0 && (col - 2) > 0)
				printf("%d", (col - 2) / 4);
			else if (col == 2 && row % 2 == 1&&row>2)
				printf("%c", 'A' + ((row-2)/2));
			else
				printf(" ");
		}
		printf("\n");
	}
}