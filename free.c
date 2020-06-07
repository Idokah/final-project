#include "Header.h"

void freePathTreeRec(treeNode *treeNode);

void free2DArray(void** board) {
	for (int i = 0; i < N; i++)
		free(board[i]);
	free(board);
}

void freeMoveList(movesList* movesLst) {
	moveCell* curr = movesLst->head;
	moveCell* next = NULL;
	while (curr != NULL) {
		next = curr->next;
		free(curr);
		curr = next;
	}
	free(movesLst);
}

void freePathTree(pathTree tree) {
	freePathTreeRec(tree.head);
}

// TODO -need to ensure
void freePathTreeRec(treeNode *treeNode){
	treeNodeListCell *currChild = treeNode->next_possible_positions;
	if (currChild == NULL) {
		free(treeNode);
		return; 
	}
	treeNodeListCell *next = NULL;
	while (currChild != NULL) {
		next = currChild->next;
		freePathTreeRec(currChild->node);
		currChild = next;
	}
}