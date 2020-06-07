#include "Header.h"

Move initNewMove(int row, int col) {
    Move newMove;
    newMove.rows = row;
    newMove.cols = col;
    return newMove;
}

moveCell *initNewMoveCell (Move move, moveCell *next, moveCell *prev) {
    moveCell *newMoveCell=(moveCell*)malloc(sizeof(moveCell));//
    newMoveCell->move = move;
    newMoveCell->next = next;
    newMoveCell->prev = prev;
    return newMoveCell;
}

movesList *initNewMoveList(moveCell *head, moveCell *tail) {
    movesList *movesLst=(movesList *)malloc(sizeof(movesList));//
    movesLst->head = head;
    movesLst->tail = tail;
    return movesLst;
}
