#ifndef HEADER1
#define HEADER1
#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define M 5
#define N 4
typedef unsigned char BYTE;

#define ISDIGIT(c) (((((c) >= 0) && ((c) <= 9))) ? (true) : (false))
#define ISNUMBER(c) (((((c) != '*') && ((c) != '#') &&((c) != ' '))) ? (true) : (false))
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

// -------------------init--------------------
Move initNewMove(int row, int col);
moveCell *initNewMoveCell(Move move, moveCell *next, moveCell *prev);
movesList *initNewMoveList(moveCell *head, moveCell *tail);

boardPosArray **validMoves(movesArray **moves, char **board);
void validMove(int row, int col, movesArray* moves, char **board, boardPosArray* boardPosArr);
int display(movesList *moves_list, boardPos start, char **board);
void printBoard(char **board);
boardPosArray **initNewBoardPosArr();
void removeMoveFromMoveList(moveCell* move,movesList* movesList);
pathTree findAllPossiblePaths(boardPos start, movesArray **moves, char **board);
treeNode *createNewTreeNode(boardPos position, treeNodeListCell * treeNodeListCell);
void extractRowAndColFromBoardPos(boardPos pos, int *row, int *col);
bool isPosValid(int row, int col, char **board);
movesList *findPathCoveringAllBoard(boardPos start, movesArray **moves, char **board);
void saveListToBinFile(char *file_name, boardPosArray *pos_arr);
int checkAndDisplayPathFromFile ( char *file_name, movesArray **moves, char **board);
// free
void free2DArray(void** board);
void freeMoveList(movesList* movesLst);
void freePathTree(pathTree tree);

#endif