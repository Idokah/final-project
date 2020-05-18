#include <stdlib.h>
#include "Header.h"

void removeFromStartOfList(moveCell *move,movesList *movesList) {
    movesList->head=move->next;
    movesList->head->prev = NULL;
    free(move);
}

void removeFromEndOfList(moveCell *move,movesList *movesList) {
    movesList->tail = move->prev;
    movesList->tail->next=NULL;
    free(move);
}
void removeFromMiddleOfList(moveCell *move,movesList *movesList){
    move->prev->next=move->next;
    free(move);
}
