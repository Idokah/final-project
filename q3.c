#include "Header.h"

treeNode *createNewTreeNode(boardPos position, treeNodeListCell * treeNodeListCell) {
	treeNode *newNode = malloc(sizeof(treeNode));
	newNode->position[0] = position[0];
	newNode->position[1] = position[1];
	newNode->next_possible_positions = treeNodeListCell;
	return newNode;
}

treeNodeListCell *createNewTreeNodeListCell(treeNode * node, treeNodeListCell * next) {
	treeNodeListCell *newTreeNodeListCell = malloc(sizeof(treeNodeListCell));
	newTreeNodeListCell->node = node;
	newTreeNodeListCell->next = next;
	return newTreeNodeListCell;
}

bool isBoardPosAlreadyExists(boardPos boardPos, boardPosArray currentPath) {
	for (int i = 0; i < currentPath.size; ++i) {
		if (boardPos[0] == currentPath.positions[i][0] && boardPos[1] == currentPath.positions[i][1]) return true;
	}
	return false;
}

pathTree createNewPathTree(treeNode * head) {
	pathTree *newPathTree = (pathTree *)malloc(sizeof(pathTree));
	newPathTree->head = head;
	return *newPathTree;
}

pathTree findAllPossiblePaths(boardPos start, movesArray **moves, char **board) {
	boardPosArray **validBoardPosArr = validMoves(moves, board);
	boardPosArray currentPath;
	currentPath.size = 0;
	currentPath.positions = NULL;
	int phySize = 0;
	treeNode *root = createNewTreeNode(start, getChildList(start, validBoardPosArr, currentPath, &phySize));
	return createNewPathTree(root);
}

treeNodeListCell *addToEndOfChildList(treeNodeListCell *head, treeNode *newTreeNode) {
	treeNodeListCell *newTreeNodeListCell = createNewTreeNodeListCell(newTreeNode, NULL);
	if (head == NULL) {
		return newTreeNodeListCell;
	}
	treeNodeListCell *curr = head;
	while (curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = newTreeNodeListCell;
	return head;
}

boardPosArray updatePathArray(boardPosArray currentPathArr, int *phySizeCurrentPath, boardPos newBoardPos) {
	if (currentPathArr.size >= *phySizeCurrentPath) {
		(*phySizeCurrentPath) ++ ;
		currentPathArr.positions = realloc(currentPathArr.positions, (*phySizeCurrentPath) * sizeof(boardPos));
	}
	currentPathArr.positions[currentPathArr.size][0] = newBoardPos[0];
	currentPathArr.positions[currentPathArr.size][1] = newBoardPos[1];
	currentPathArr.size++;
	return currentPathArr;
}

treeNodeListCell *getChildList(boardPos boardPos, boardPosArray **validBoardPosArr, boardPosArray currentPath, int *phySizeCurrentPath) {
	//static int phySizeCurrentPath = 0;
	int row, col;
	extractRowAndColFromBoardPos(boardPos, &row, &col);
	boardPosArray boardPosArr = validBoardPosArr[row][col];
	if (boardPosArr.size == 0) return NULL;
	currentPath = updatePathArray(currentPath, phySizeCurrentPath, boardPos);
	treeNodeListCell *headChildList = NULL;
	for (int i = 0; i < boardPosArr.size; ++i) {
		if (!isBoardPosAlreadyExists(boardPosArr.positions[i], currentPath)) {
			treeNode *newTreeNode = createNewTreeNode(boardPosArr.positions[i], getChildList(boardPosArr.positions[i], validBoardPosArr, currentPath, phySizeCurrentPath));
			headChildList = addToEndOfChildList(headChildList, newTreeNode);
		}
	}
	return headChildList;
}
