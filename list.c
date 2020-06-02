#include "Header.h"

void removeFromStartOfList(moveCell *move,movesList *movesList) {
    movesList->head=move->next;
    movesList->head->prev = NULL;
    free(move);
}

void removeFromEndOfList(moveCell *move,movesList *movesList) {
    movesList->tail = move->prev;
    movesList->tail->next = NULL;
	free(move);
}

void removeFromMiddleOfList(moveCell *move,movesList *movesList){
	moveCell *prev = move->prev;
	moveCell *next = move->next;
	prev->next=next;
	next->prev = prev;
	free(move);
}

void addToEndOfList(moveCell *move, movesList *movesList) {
    if (movesList ->head == NULL){
        move->prev = NULL;
        movesList->head = move;
        movesList->tail = move;
        return;
    }
    move->prev = movesList->tail;
    movesList->tail->next = move;
    movesList->tail = move;
}

