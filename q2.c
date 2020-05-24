#define _CRT_SECURE_NO_WARNINGS

#include "Header.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

char **duplicateBoard(char **board) {
	char **newBoard = (char **)malloc(N * sizeof(char *));
	for (int i = 0; i < N; ++i) {
		newBoard[i] = (char *)malloc(M * sizeof(char));
		for (int j = 0; j < M; ++j) {
			newBoard[i][j] = board[i][j];
		}
	}
	return newBoard;
}

int display(movesList *moves_list, boardPos start, char **board) {
	int movesCounter = 0;
	int deletedMovesCounter = 0;
	char **newBoard = duplicateBoard(board);
	int newRow, currRow = start[0] - 'A';
	int newCol, currCol;
	sscanf(start + 1, "%d", &currCol);
	currCol--;
	// change to func
	newBoard[currRow][currCol] = '#';
	moveCell *temp;
	moveCell *currMoveNode = moves_list->head;
	while (currMoveNode != NULL) {
		newRow = currRow + currMoveNode->move.rows;
		newCol = currCol + currMoveNode->move.cols;
		if (isPosValid(newRow, newCol, board) && newBoard[newRow][newCol] == ' ') {
			movesCounter++;
			newBoard[newRow][newCol] = movesCounter;
			currMoveNode = currMoveNode->next;
			currRow = newRow;
			currCol = newCol;
		}
		else {
			temp = currMoveNode->next;
			removeMoveFromMoveList(currMoveNode, moves_list);
			deletedMovesCounter++;
			currMoveNode = temp;
		}
	}

	printBoard(newBoard);
	return deletedMovesCounter;
}

void removeMoveFromMoveList(moveCell* move, movesList* movesList) {
	if (movesList->head == movesList->tail) {
		movesList->head = NULL;
		movesList->tail = NULL;
	}
	else if (move->prev == NULL) {
		removeFromStartOfList(move, movesList);
	}
	else if (move->next == NULL) {
		removeFromEndOfList(move, movesList);
	}
	else {
		removeFromMiddleOfList(move, movesList);
	}
}

void printBoard(char **board) {
	char currCh;
	for (int row = 0; row <= 2 * (N + 1); row++) {
		for (int col = 0; col <= 4 * M; col++) {
			if (row % 2 == 0 && col % 4 == 0)
				printf("+");
			else if (row % 2 == 0)
				printf("-");
			else if (col % 4 == 0)
				printf("|");
			else if (row == 1 && col % 4 == 2 && col > 2)
				printf("%d", col / 4);
			else if (col == 2 && row % 2 == 1 && row > 2)
				printf("%c", 'A' + (row / 2) - 1);
			else if (col % 4 == 2 && row % 2 == 1 && col > 1 && row > 1) {
				currCh = (char)board[(row - 3) / 2][(col - 6) / 4];
				if (ISDIGIT(currCh))
					printf("%d", currCh);
				else printf("%c", currCh);
			}
			else
				printf(" ");
		}
		printf("\n");
	}
}
