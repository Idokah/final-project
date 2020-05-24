#define _CRT_SECURE_NO_WARNINGS

#include "Header.h"

Move initNewMove(int row, int col) {
	Move newMove;
	newMove.rows = row;
	newMove.cols = col;
	return newMove;
}

moveCell initNewMoveCell (Move move, moveCell *next, moveCell *prev) {
	moveCell newMoveCell;
	newMoveCell.move = move;
	newMoveCell.next = next;
	newMoveCell.prev = prev;
	return newMoveCell;
}

movesList initNewMoveList(moveCell *head, moveCell *tail) {
	movesList movesLst;
	movesLst.head = head;
	movesLst.tail = tail;
	return movesLst;
}


int main(){
	// init moves
	Move move1 = initNewMove(1, 1);
	Move move2 = initNewMove(2, 1);
	Move move3 = initNewMove(1, 2);
	Move move4 = initNewMove(2, -2);
	Move move5 = initNewMove(-1, -1);

	//init moveArray1
	Move* moveArray1 = (Move*)malloc(sizeof(Move) * 4);
	moveArray1[0] = move1;
	moveArray1[1] = move2;
	moveArray1[2] = move3;
	moveArray1[3] = move4;

	//init moveArray2
	Move* moveArray2 = (Move*)malloc(2 * sizeof(Move));
	moveArray2[0] = move5;
	moveArray2[1] = move1;

	//init moveArrays
	movesArray **moveArrays = (movesArray **)malloc(sizeof(movesArray*)*N);
	for (int row = 0; row < N; row++) {
		moveArrays[row] = (movesArray *)malloc(sizeof(movesArray)*M);
		for (int col = 0; col < M ; col++) {
			if (col == 1 && row == 1) {
				moveArrays[row][col].moves = moveArray2;
				moveArrays[row][col].size = 2;
			}
			else {
				moveArrays[row][col].moves = moveArray1;
				moveArrays[row][col].size = 4;
			}
		}
	}

	//init board
	char **board = (char **)malloc(sizeof(char *)*N);
	for (int row = 0; row < N; row++) {
		board[row] = (char *)malloc(sizeof(char)*M);
		for (int col = 0; col < M; col++) {
			if (col>=3) board[row][col] = '*';
			else board[row][col] = ' ';
		}
	}

	// init moveCells
	moveCell moveCell1 = initNewMoveCell(move1, NULL, NULL);
	moveCell moveCell2 = initNewMoveCell(move2, NULL, &moveCell1);
	moveCell moveCell3 = initNewMoveCell(move3, NULL, &moveCell2);
	moveCell moveCell4 = initNewMoveCell(move4, NULL, &moveCell3);
	moveCell1.next = &moveCell2;
	moveCell2.next = &moveCell3;
	moveCell3.next = &moveCell4;

	// init moveCellsLst
	movesList movesLst = initNewMoveList(&moveCell1, &moveCell4);

	// q1
	boardPosArray** validBoardPosArray = validMoves(moveArrays, board);
    //q2
    int res = display(&movesLst,"A1",board);

	// q3
    pathTree treeRes =  findAllPossiblePaths("A1", moveArrays, board);
}
