#include "Header.h"
treeNodeListCell *getChildList(boardPos boardPos, boardPosArray **validBoardPosArr, boardPosArray *currentPath, int *phySizeCurrentPath, int logSizeCurrentPath);
void updatePathArray(boardPosArray *currentPathArr, int *phySizeCurrentPath, boardPos newBoardPos, int logSizeCurrentPath);
bool isBoardPosAlreadyExists(boardPos boardPos, boardPosArray currentPath, int logSizeCurrentPath);


treeNode *createNewTreeNode(boardPos position, treeNodeListCell * treeNodeListCell) {
	treeNode *newNode = malloc(sizeof(treeNode));
	assert(newNode != NULL);
	newNode->position[0] = position[0];
	newNode->position[1] = position[1];
	newNode->next_possible_positions = treeNodeListCell;
	return newNode;
}

treeNodeListCell *createNewTreeNodeListCell(treeNode * node, treeNodeListCell * next) {
	treeNodeListCell *newTreeNodeListCell = malloc(sizeof(treeNodeListCell));
	assert(newTreeNodeListCell != NULL);
	newTreeNodeListCell->node = node;
	newTreeNodeListCell->next = next;
	return newTreeNodeListCell;
}

bool isBoardPosAlreadyExists(boardPos boardPos, boardPosArray currentPath,int logSizeCurrentPath) {
	for (int i = 0; i < logSizeCurrentPath; ++i) {
		if (boardPos[0] == currentPath.positions[i][0] && boardPos[1] == currentPath.positions[i][1]) return true;
	}
	return false;
}

pathTree createNewPathTree(treeNode * head) {
	pathTree *newPathTree = (pathTree *)malloc(sizeof(pathTree));
	assert(newPathTree != NULL);
	newPathTree->head = head;
	return *newPathTree;
}

pathTree findAllPossiblePaths(boardPos start, movesArray **moves, char **board) {
	boardPosArray **validBoardPosArr = validMoves(moves, board);
	boardPosArray currentPath;
	currentPath.size = 0;
	currentPath.positions = NULL;
	int phySize = 0;
	treeNode *root = createNewTreeNode(start, getChildList(start, validBoardPosArr, &currentPath, &phySize,0));
	free(currentPath.positions);
	free(validBoardPosArr);
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

void updatePathArray(boardPosArray *currentPathArr, int *phySizeCurrentPath, boardPos newBoardPos, int logSizeCurrentPath) {
	if (logSizeCurrentPath >= *phySizeCurrentPath) {
		(*phySizeCurrentPath)++;
		currentPathArr->positions = realloc(currentPathArr->positions, (*phySizeCurrentPath) * sizeof(boardPos));
		assert(currentPathArr->positions != NULL);
	}
	currentPathArr->positions[logSizeCurrentPath][0] = newBoardPos[0];
	currentPathArr->positions[logSizeCurrentPath][1] = newBoardPos[1];
	return (logSizeCurrentPath+1);
}


treeNodeListCell *getChildList(boardPos boardPos, boardPosArray **validBoardPosArr, boardPosArray *currentPath, int *phySizeCurrentPath,int logSizeCurrentPath) {
	int row, col;
	extractRowAndColFromBoardPos(boardPos, &row, &col);
	boardPosArray boardPosArr = validBoardPosArr[row][col];
	if (boardPosArr.size == 0) return NULL;
	updatePathArray(currentPath,phySizeCurrentPath, boardPos,logSizeCurrentPath);
	treeNodeListCell *headChildList = NULL;
	for (int i = 0; i < boardPosArr.size; ++i) {
		if (!isBoardPosAlreadyExists(boardPosArr.positions[i], *currentPath,logSizeCurrentPath)) {
			treeNode *newTreeNode = createNewTreeNode(boardPosArr.positions[i], getChildList(boardPosArr.positions[i], validBoardPosArr, currentPath, phySizeCurrentPath,logSizeCurrentPath+1));
			headChildList = addToEndOfChildList(headChildList, newTreeNode);
		}
	}
	return headChildList;
}
