#ifndef HEADER1
#define HEADER1

#define M 4
#define N 4

typedef char boardPos[2];
typedef struct _move {
	char rows, cols;
} Move;typedef struct _movesArray {
	unsigned int size;
	Move *moves;
} movesArray;typedef struct _boardPosArray {
	unsigned int size;
	boardPos *positions;
} boardPosArray;boardPosArray ** validMoves(movesArray **moves, char **board);




#endif