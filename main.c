#define _CRT_SECURE_NO_WARNINGS

#include "Header.h"

int main() {

	// init moves
	Move move1 = initNewMove(1, 1);
	Move move2 = initNewMove(2, 1);
	Move move3 = initNewMove(1, 2);
	Move move4 = initNewMove(0, 3);
	Move move5 = initNewMove(-1, -1);
	Move move6 = initNewMove(0, -2);
	Move move7 = initNewMove(-2, 1);
	Move move8 = initNewMove(-1, 0);


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

	//init moveArray3 for q4
	Move* moveArray3 = (Move*)malloc(8 * sizeof(Move));
	moveArray3[0] = move1;
	moveArray3[1] = move2;
	moveArray3[2] = move3;
	moveArray3[3] = move4;
	moveArray3[4] = move5;
	moveArray3[5] = move6;
	moveArray3[6] = move7;
	moveArray3[7] = move8;

	//init moveArrays
	movesArray **moveArrays = (movesArray **)malloc(sizeof(movesArray*)*N);
	for (int row = 0; row < N; row++) {
		moveArrays[row] = (movesArray *)malloc(sizeof(movesArray)*M);
		for (int col = 0; col < M; col++) {
			//if (col == 1 && row == 1) {
			//	moveArrays[row][col].moves = moveArray2;
			//	moveArrays[row][col].size = 2;
			//}
			//else {
				moveArrays[row][col].moves = moveArray1;
				moveArrays[row][col].size = 4;
			//}
		}
	}

	//init moveArrays2- for q4
	movesArray **moveArrays2 = (movesArray **)malloc(sizeof(movesArray*)*N);
	for (int row = 0; row < N; row++) {
		moveArrays2[row] = (movesArray *)malloc(sizeof(movesArray)*M);
		for (int col = 0; col < M; col++) {
			moveArrays2[row][col].moves = moveArray3;
			moveArrays2[row][col].size = 8;
		}
	}

	//init board
	char **board = (char **)malloc(sizeof(char *)*N);
	for (int row = 0; row < N; row++) {
		board[row] = (char *)malloc(sizeof(char)*M);
		for (int col = 0; col < M; col++) {
			if (col >= 3) board[row][col] = '*';
			else if (col == 2 && row != 3) board[row][col] = '*';
			else if (col == 1 && row != 1) board[row][col] = '*';
			else board[row][col] = ' ';
		}
	}
	//board[1][4] = ' ';

	// init moveCells
	moveCell *moveCell1 = initNewMoveCell(move1, NULL, NULL);
	moveCell *moveCell2 = initNewMoveCell(move2, NULL, moveCell1);
	moveCell *moveCell3 = initNewMoveCell(move3, NULL, moveCell2);
	moveCell *moveCell4 = initNewMoveCell(move4, NULL, moveCell3);
	moveCell1->next = moveCell2;
	moveCell2->next = moveCell3;
	moveCell3->next = moveCell4;

	// init moveCellsLst
	movesList *movesLst = initNewMoveList(moveCell1, moveCell4);
	// q1
	//boardPosArray** validBoardPosArray = validMoves(moveArrays, board);

	//q2/
	int res = display(movesLst, "A1", board);

	 //q3
    //pathTree treeRes =  findAllPossiblePaths("A1", moveArrays, board);

	//q4
	movesList *pathMoveList = findPathCoveringAllBoard("A1", moveArrays2, board);

	//free2DArray(board);
	//free(moveArray1);
	//free(moveArray2);
	//free(moveArray3);
	//free2DArray(moveArrays);
	//free2DArray(moveArrays2);
	//freeMoveList(movesLst);
	//free(moveArrays);
	//free(moveArrays2);
	//if (pathMoveList)
	//	freeMoveList(pathMoveList);
	//freePathTree(treeRes);
}

