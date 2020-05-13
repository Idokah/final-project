#ifndef HEADER1
#define HEADER1
#include <stdbool.h>

#define M 5
#define N 4

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


boardPosArray ** validMoves(movesArray **moves, char **board);
void validMove(int row, int col, movesArray* moves, char **board, boardPosArray* boardPosArr);
int display(movesList *moves_list, boardPos start, char **board);
void printboard();
boardPosArray **initNewBoardPosArr();
#endif