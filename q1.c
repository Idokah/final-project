#define _CRT_SECURE_NO_WARNINGS

#include "Header.h"

boardPosArray **validMoves(movesArray **moves, char **board) {
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
	validPositions[pos][1] = (col + 1) + '0';
}

void insertToNewMovesArray(movesArray* newMovesArr, Move newMove, int logSize, int row, int col) {
	newMovesArr->moves[logSize] = newMove;
	newMovesArr->size = logSize+1;
}

boardPos *insertMove(Move newMove, movesArray* newMovesArr, boardPos *validPositions, int *logSize, int *phySize, int row, int col){
	if (*logSize >= *phySize) {
		(*phySize) ++;
		validPositions = (boardPos*)realloc(validPositions, (*phySize) * sizeof(boardPos));
		assert(validPositions != NULL);
		newMovesArr->moves = (Move*)realloc(newMovesArr->moves, (*phySize) * sizeof(Move));
		assert(newMovesArr->moves != NULL);
	}
	insertToValidPositions(validPositions, newMove, *logSize, row, col);
	insertToNewMovesArray(newMovesArr, newMove, *logSize, row, col);
	(*logSize)++;
	return validPositions;
}

void validMove(int row, int col, movesArray* moves, char **board, boardPosArray* boardPosArr) {
	int counterPositions = 0;
	int phyPositionsSize = 0;
	movesArray newMovesArr;
	newMovesArr.moves = NULL;
	newMovesArr.size = 0;
	boardPos *validPositions = NULL;
	for (int i = 0; i < moves->size; i++) {
		int newCol = col + (int)moves->moves[i].cols;
		int newRow = row + (int)moves->moves[i].rows;
		if (isPosValid(newRow, newCol, board)) {
			validPositions = insertMove(moves->moves[i] , &newMovesArr, validPositions, &counterPositions, &phyPositionsSize, newRow, newCol);
		}
	}
	boardPosArr->size = counterPositions;
	boardPosArr->positions = validPositions;
	*moves = newMovesArr;
}

boardPosArray **initNewBoardPosArr() {
	boardPosArray **newBoardPosArr = (boardPosArray **)malloc(sizeof(boardPosArray*)*N);
	assert(newBoardPosArr != NULL);
	for (int row = 0; row < N; row++) {
		newBoardPosArr[row] = (boardPosArray *)malloc(sizeof(boardPosArray)*M);
		assert(newBoardPosArr[row] != NULL);
	}
	return newBoardPosArr;
}

void extractRowAndColFromBoardPos(boardPos pos, int *row, int *col){
    *row = pos[0] - 'A';
    sscanf(pos+1, "%d", col);
    (*col)--;
}