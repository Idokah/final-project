#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Header.h"

boardPosArray ** validMoves(movesArray **moves, char **board);
boardPosArray ** validMove(int row, int col, movesArray move, char **board);
boardPosArray **initNewBoardPosArr();

void addItemToArr(boardPos* arr, int size, boardPos newItem);
int main(){
	Move*  move1 = (Move*)malloc(sizeof(Move));
	move1->cols = 1;
	move1->rows = 1;
	movesArray movesArr;
	movesArr.size = 4;
	movesArr.moves = move1 ;
	movesArray **moves = (movesArray **)malloc(sizeof(movesArray *)*N);
	for (int i = 0; i < 4; i++) {
		moves[i] = (movesArray *)malloc(sizeof(movesArray)*M);
		for (int j = 0; j < 4; j++) {
			moves[i][j].moves = move1;
			moves[i][j].size = 4;
		}
	}

	char **board = (char **)malloc(sizeof(char *)*N);
	for (int i = 0; i < 4; i++) {
		board[i] = (char *)malloc(sizeof(char)*M);
		for (int j = 0; j < 4; j++) {
			if (j<=1) board[i][j] = ' ';
			else board[i][j] = '*';
		}
	}
	validMoves(moves, board);
}

boardPosArray ** validMoves(movesArray **moves, char **board){
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			validMove( i,j,moves[i][j], board);
		}
	}
	return NULL;
}

boardPosArray ** validMove(int row,int col, movesArray move, char **board) {
	boardPosArray** newBoardPosArr= initNewBoardPosArr();
	for (int i = 0; i < move.size; i++) {
		int newCol = col + (int)move.moves[i].cols;
		int newRow = row + (int)move.moves[i].rows;
		if (newRow < N && newCol < M && newRow >= 0 && newCol >= 0 && board[newRow][newCol] != '*') {
			// add to new borad
			boardPos newBoardPos = "A1";
			//boardPos *newBoardPos = (boardPos *)malloc(sizeof(boardPos));
			//*newBoardPos[0] = newRow + 'A';
			//*newBoardPos[1] = (char)(newCol + 1);
			addItemToArr(newBoardPosArr[row][col].positions, newBoardPosArr[row][col].size, newBoardPos);
			newBoardPosArr[row][col].size++;
			//newBoard[row][col].positions = newBoardPos;
		}
		else {
			//removeIndexFromArr(move.moves, i);
			// remove from moves array
		}

	}
}


boardPosArray **initNewBoardPosArr() {
	//boardPosArray **newBoardPosArr = (boardPosArray **)malloc(sizeof(boardPosArray*)*N*M);
	boardPosArray **newBoardPosArr = (boardPosArray **)malloc(sizeof(boardPosArray*)*N);
	for (int i = 0; i < N; i++) {
		newBoardPosArr[i] = (boardPosArray *)malloc(sizeof(boardPosArray)*M);
		for (int j = 0; j < M; j++) {
			newBoardPosArr[i][j].size = 0;
			newBoardPosArr[i][j].positions = (boardPos*)malloc(sizeof(boardPos));
		}
	}
	return newBoardPosArr;
}

//
//boardPosArray **initNewBoardPosArr() {
//	//boardPosArray **newBoardPosArr = (boardPosArray **)malloc(sizeof(boardPosArray*)*N*M);
//	boardPosArray **newBoardPosArr = (boardPosArray **)malloc(sizeof(boardPosArray*)*N);
//	for (int i = 0; i < N; i++) {
//		newBoardPosArr[i] = (boardPosArray *)malloc(sizeof(boardPosArray)*M);
//		for (int j = 0; j < M; j++) {
//			newBoardPosArr[i][j].size = 0;
//			newBoardPosArr[i][j].positions = (boardPos*)malloc(sizeof(boardPos));
//		}
//	}
//	return newBoardPosArr;
//}


void addItemToArr(boardPos* arr, int size, boardPos newItem){

	arr=(boardPos*)realloc(arr,(size+1)*sizeof(boardPos));
	sscanf(newItem, "%s", &(arr[size]));
}

//void removeIndexFromArr(Move *moves, int index) {
//
//}
