#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include "list.h"
#include "pathTree.h"

boardPosArray **validMoves(movesArray **moves, char **board) {
	boardPosArray** boardPosArr = initNewBoardPosArr();
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < M; col++) {
			validMove(row, col, &(moves[row][col]), board, &(boardPosArr[row][col]));
		}
	}
	return boardPosArr;
}
bool isPosValid(int row, int col, char **board) {
	return (row < N && col < M && row >= 0 && col >= 0 && board[row][col] != '*');
}
void insertToValidPositions(boardPos *validPositions, Move newMove, int pos, int row, int col) {
	validPositions[pos][0] = row + 'A';
	validPositions[pos][1] = (char)col + 1;
}
void insertToNewMovesArray(movesArray* newMovesArr, Move newMove, int logSize, int row, int col) {
	newMovesArr->moves[logSize] = newMove;
	newMovesArr->size = logSize+1;
}
void insertMove(Move newMove, movesArray* newMovesArr, boardPos *validPositions, int *logSize, int *phySize, int row, int col){
	if (*logSize >= *phySize) {
		*phySize *= 2;
		validPositions = (boardPos*)realloc(validPositions, *phySize);
		newMovesArr->moves = (Move*)realloc(newMovesArr->moves, *phySize);
	}
	insertToValidPositions(validPositions, newMove, *logSize, row, col);
	insertToNewMovesArray(newMovesArr, newMove, *logSize, row, col);
	(*logSize)++;
}
treeNodeListCell *getChildList(boardPos boardPos, boardPosArray **validBoardPosArr, boardPosArray *currentPath, int phySizeCurrentPath);
treeNode *createNewTreeNode(boardPos position, treeNodeListCell * treeNodeListCell);

void validMove(int row, int col, movesArray* moves, char **board, boardPosArray* boardPosArr) {
	int counterPositions = 0;
	int phyPositionsSize = 1;
	movesArray newMovesArr;
	newMovesArr.moves = (Move*)malloc(sizeof(Move));
	boardPos *validPositions = (boardPos*)malloc(sizeof(boardPos));
	for (int i = 0; i < moves->size; i++) {
		int newCol = col + (int)moves->moves[i].cols;
		int newRow = row + (int)moves->moves[i].rows;
		if (isPosValid(newRow, newCol, board)) {
			insertMove(moves->moves[i] , &newMovesArr, validPositions, &counterPositions, &phyPositionsSize, newRow, newCol);
		}
	}
	boardPosArr->size = counterPositions;
	boardPosArr->positions = validPositions;
	*moves = newMovesArr;
}

boardPosArray **initNewBoardPosArr() {
	boardPosArray **newBoardPosArr = (boardPosArray **)malloc(sizeof(boardPosArray*)*N);
	for (int row = 0; row < N; row++) {
		newBoardPosArr[row] = (boardPosArray *)malloc(sizeof(boardPosArray)*M);
	}
	return newBoardPosArr;
}

char **duplicateBoard(char **board){
    char **newBoard = (char **)malloc(N * sizeof(char *));
    for (int i = 0; i < N ; ++i) {
        newBoard[i] = (char *) malloc(M * sizeof(char));
        for (int j = 0; j < M; ++j) {
            newBoard[i][j] = board[i][j];
        }
    }
    return newBoard;
}

int display(movesList *moves_list, boardPos start, char **board) {
    int movesCounter = 0;
    int deletedMovesCounter = 0;
    char **newBoard = duplicateBoard(board);
    int newRow, currRow = start[0] - 'A';
    int newCol, currCol;
    sscanf(start+1, "%d", &currCol);
    currCol--;
    // change to func
    newBoard[currRow][currCol] = '#';
    moveCell *temp;
    moveCell *currMoveNode = moves_list->head;
    while (currMoveNode != NULL){
        newRow = currRow + currMoveNode->move.rows;
        newCol = currCol + currMoveNode->move.cols;
        if (isPosValid(newRow, newCol, board) && newBoard[newRow][newCol] == ' '){
            movesCounter++;
            newBoard[newRow][newCol] = movesCounter;
            currMoveNode = currMoveNode->next;
            currRow = newRow;
            currCol = newCol;
        } else {
            temp = currMoveNode->next;
            removeMoveFromMoveList(currMoveNode, moves_list);
            deletedMovesCounter++;
            currMoveNode = temp;
        }
    }

    printBoard(newBoard);
    return deletedMovesCounter;
}

void removeMoveFromMoveList(moveCell* move,movesList* movesList) {
    if (movesList->head == movesList-> tail){
        movesList->head=NULL;
        movesList->tail=NULL;
    } else if (move->prev == NULL){
        removeFromStartOfList(move, movesList);
    } else if (move->next==NULL) {
        removeFromEndOfList(move, movesList);
    } else {
        removeFromMiddleOfList(move, movesList);
    }
}

void printBoard(char **board){
    char currCh;
	for (int row = 0; row <= 2*(N+1); row++) {
		for (int col = 0; col <= 4*M; col++) {
			if (row % 2 == 0 && col % 4 == 0)
				printf("+");
			else if (row % 2 == 0)
				printf("-");
			else if (col % 4 == 0)
				printf("|");
			else if (row == 1 && col % 4 == 2 && col > 2)
				printf("%d", col / 4);
			else if (col == 2 && row % 2 == 1 && row > 2)
				printf("%c", 'A' + (row/2)-1);
            else if (col % 4 == 2 && row % 2 == 1 && col > 1 && row > 1) {
                currCh = (char)board[(row - 3) / 2][(col - 6) / 4];
                if (ISDIGIT(currCh))
                    printf("%d", currCh);
                else printf("%c", currCh);
            } else
				printf(" ");
		}
		printf("\n");
	}
}

pathTree createNewPathTree(treeNode * head){
    pathTree *newPathTree = (pathTree *)malloc(sizeof(pathTree));
    newPathTree->head = head;
    return *newPathTree;
}

pathTree findAllPossiblePaths(boardPos start, movesArray **moves, char **board){
    boardPosArray **validBoardPosArr = validMoves(moves, board);
    boardPosArray *currentPath = (boardPosArray *)malloc(sizeof(boardPosArray));
    currentPath->size = 1;
    currentPath->positions[0][0] = start[0];
    currentPath->positions[0][1] = start[1];
    treeNode *root = createNewTreeNode(start, getChildList(start, validBoardPosArr, currentPath, 1));
    return createNewPathTree(root);
}

void extractRowAndColFromBoardPos(boardPos pos, int *row, int *col){
    *row = pos[0] - 'A';
    sscanf(pos+1, "%d", col);
    (*col)--;
}

treeNode *createNewTreeNode(boardPos position, treeNodeListCell * treeNodeListCell){
    treeNode *newNode = malloc(sizeof(treeNode));
    newNode->position[0] = position[0];
    newNode->position[1] = position[1];
    newNode->next_possible_positions = treeNodeListCell;
    return newNode;
}

treeNodeListCell *createNewTreeNodeListCell(treeNode * node, treeNodeListCell * next){
    treeNodeListCell *newTreeNodeListCell = malloc(sizeof(treeNodeListCell));
    newTreeNodeListCell->node = node;
    newTreeNodeListCell->next = next;
    return newTreeNodeListCell;
}

bool isBoardPosAlreadyExists(boardPos boardPos, boardPosArray *boardPosArr){
    for (int i = 0; i < boardPosArr->size; ++i) {
        if (boardPosArr->positions[i]== boardPos) return true;
    }
    return false;
}


//void getList(treeNode* root, boardPosArray **validBoardPosArr, boardPosArray currentPath){
//treeNode *getChildNode(treeNode* root, boardPosArray **validBoardPosArr, boardPosArray *currentPath){
//    int row, col;
//    extractRowAndColFromBoardPos(root->position, &row, &col);
//    boardPosArray boardPosArr = validBoardPosArr[row][col];
//    for (int i = 0; i <boardPosArr.size ; ++i) {
//        if(!isBoardPosAlreadyExists(boardPosArr.positions[i])){
//            createNewTreeNode(boardPosArr.positions[i],validBoardPosArr[boardPosArr.positions[i]])
//        };
//
//    }
//}

void addToEndOfChildList(treeNodeListCell *head, treeNode *newTreeNode){
    treeNodeListCell *newTreeNodeListCell = createNewTreeNodeListCell(newTreeNode, NULL);
    treeNodeListCell *curr = head;
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = newTreeNodeListCell;
}

void updatePathArray(boardPosArray *currentPathArr, int *phySizeCurrentPath, boardPos newBoardPos){
    if (currentPathArr->size <= *phySizeCurrentPath){
        (*phySizeCurrentPath) *= 2;
        currentPathArr->positions  = realloc(currentPathArr->positions, *phySizeCurrentPath);
    }
    currentPathArr->positions[currentPathArr->size][0] = newBoardPos[0] ;
    currentPathArr->positions[currentPathArr->size][1] = newBoardPos[1] ;
    currentPathArr->size++; //if there is a bug here in the future-------> ido's fault.
}

treeNodeListCell *getChildList(boardPos boardPos, boardPosArray **validBoardPosArr, boardPosArray *currentPath, int phySizeCurrentPath){
    int row, col;
    extractRowAndColFromBoardPos(boardPos, &row, &col);
    boardPosArray boardPosArr = validBoardPosArr[row][col];
    if (boardPosArr.size == 0) return NULL;
    // init to empty list with dummy head
    treeNodeListCell *childList = createNewTreeNodeListCell(NULL, NULL);
    for (int i = 0; i < boardPosArr.size; ++i) {
        if (!isBoardPosAlreadyExists(boardPosArr.positions[i], currentPath)){
            updatePathArray(currentPath, &phySizeCurrentPath, boardPosArr.positions[i]);
            treeNode *newTreeNode = createNewTreeNode(boardPosArr.positions[i], getChildList(boardPosArr.positions[i], validBoardPosArr, currentPath, phySizeCurrentPath));
            addToEndOfChildList(childList, newTreeNode);
        }
    }
    return childList;
}