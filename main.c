#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "Header.h"
#include "pathTree.h"

int main(){
	Move*  move1 = (Move*)malloc(sizeof(Move));
	move1->cols = 1;
	move1->rows = 1;
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
	boardPosArray** BPosArray = validMoves(moves, board);

    Move *move2 = (Move *)malloc(sizeof(Move));
    move2->cols = 2;
    move2->rows = 1;

    Move *move3 = (Move *)malloc(sizeof(Move));
    move3->cols=0;
    move3->rows=1;

    Move *move4 = (Move *)malloc(sizeof(Move));
    move4->cols=-2;
    move4->rows=2;


    Move *move5 = (Move *)malloc(sizeof(Move));
    move5->cols=2;
    move5->rows=-2;

	moveCell* moveCell1= (moveCell*)malloc(sizeof(moveCell));
	moveCell1->move = *move2;
    moveCell1->next = NULL;
    moveCell1->prev = NULL;

    moveCell* moveCell2= (moveCell*)malloc(sizeof(moveCell));
    moveCell2->move = *move3;
    moveCell2->next = NULL;
    moveCell2->prev = moveCell1;



    moveCell* moveCell3= (moveCell*)malloc(sizeof(moveCell));
    moveCell3->move = *move4;
    moveCell3->next = NULL;
    moveCell3->prev = moveCell2;

    moveCell* moveCell4= (moveCell*)malloc(sizeof(moveCell));
    moveCell4->move = *move5;
    moveCell4->next = NULL;
    moveCell4->prev = moveCell3;


    moveCell1->next = moveCell2;
    moveCell2->next = moveCell3;
    moveCell3->next = moveCell4;

    movesList movesLst;
    movesLst.tail = moveCell4;
    movesLst.head = moveCell1;
    int res = display(&movesLst,"A3",board);
    pathTree treeRes =  findAllPossiblePaths("A3", moves, board);
}
