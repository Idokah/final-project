#ifndef HEADER1
#define HEADER1

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "list.h"
//#include "pathTree.h"


#define M 5
#define N 4

#define ISDIGIT(c) (((((c) >= 0) && ((c) <= 9))) ? (true) : (false))

typedef char boardPos[2];

typedef struct _move {
	char rows, cols;
} Move;

typedef struct _movesArray {
	unsigned int size;
	Move *moves;
} movesArray;

typedef struct _boardPosArray {
	unsigned int size;
	boardPos *positions;
} boardPosArray;

typedef struct _moveCell {
	Move move;
	struct _moveCell *next, *prev;
} moveCell;

typedef struct _movesList {
	moveCell * head;
	moveCell * tail;
} movesList;

// -------------------------tree-------------------------

typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode{
    boardPos position;
    treeNodeListCell *next_possible_positions;
} treeNode;

typedef struct _treeNodeListCell {
    treeNode * node;
    struct _treeNodeListCell * next;
} treeNodeListCell;

typedef struct _pathTree {
    treeNode * head;
} pathTree;


boardPosArray **validMoves(movesArray **moves, char **board);
void validMove(int row, int col, movesArray* moves, char **board, boardPosArray* boardPosArr);
int display(movesList *moves_list, boardPos start, char **board);
void printBoard(char **board);
boardPosArray **initNewBoardPosArr();
void removeMoveFromMoveList(moveCell* move,movesList* movesList);
pathTree findAllPossiblePaths(boardPos start, movesArray **moves, char **board);
treeNodeListCell *getChildList(boardPos boardPos, boardPosArray **validBoardPosArr, boardPosArray currentPath);
treeNode *createNewTreeNode(boardPos position, treeNodeListCell * treeNodeListCell);
void extractRowAndColFromBoardPos(boardPos pos, int *row, int *col);
bool isPosValid(int row, int col, char **board);

// -------lists-------
void removeFromStartOfList(moveCell *move,movesList *movesList);
void removeFromEndOfList(moveCell *move,movesList *movesList);
void removeFromMiddleOfList(moveCell *move,movesList *movesList);

#endif