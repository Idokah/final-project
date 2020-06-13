#include "Header.h"
#include "list.h"

boardPosArray getTreeLongestPath(pathTree *tree);
boardPosArray getTreeLongestPathRec(treeNode *root);
boardPosArray insertToBoardPosStart(boardPosArray boardPosArr,boardPos new);


//void createMovesList(boardPosArray boardPosArray, movesList *ptrMovesList){
movesList *reversedBoardPosArrayToMovesList(boardPosArray boardPosArray){
    int row, col;
    boardPos prev, curr;
    moveCell **prevMoveCell = (moveCell **)malloc(sizeof(moveCell *));//
	movesList *moves = initNewMoveList(NULL, NULL);//
	*prevMoveCell = moves->head;
    for (int i = boardPosArray.size - 2; i >= 0 ; i--) {
        prev[0] = boardPosArray.positions[i+1][0];
        prev[1] = boardPosArray.positions[i+1][1];
        curr[0] = boardPosArray.positions[i][0];
        curr[1] = boardPosArray.positions[i][1];
        row = curr[0] - prev[0];
        col = curr[1] - prev[1];
        moveCell *newMove = initNewMoveCell(initNewMove(row,col), NULL, *prevMoveCell);//
        addToEndOfList(newMove, moves);
        *prevMoveCell = newMove;
    }
    free(prevMoveCell);
    return moves;
}


movesList *findPathCoveringAllBoard(boardPos start, movesArray **moves, char **board){
	movesList *moveList = NULL;
    int validPosNum = getCountOfValidPositions(board);
    pathTree pathTree = findAllPossiblePaths(start, moves, board);
    boardPosArray longestPath = getTreeLongestPath(&pathTree);
    if (longestPath.size == validPosNum){
		moveList = reversedBoardPosArrayToMovesList(longestPath);
    }
	free(longestPath.positions);
    return moveList;
}

int getCountOfValidPositions(char **board){
    int counter = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (board[i][j] == ' ') counter++;
        }
    }
    return counter;
}


// gets path tree and return the longest path in the tree
boardPosArray getTreeLongestPath(pathTree *tree){
    boardPosArray longestPath = getTreeLongestPathRec(tree->head);
    return longestPath;
}


boardPosArray getTreeLongestPathRec(treeNode *root){
    boardPosArray longestPath;
    longestPath.size=0;
    boardPosArray tempCurrPath;
    treeNodeListCell *currChild = root->next_possible_positions;
    if (currChild == NULL) {
        boardPosArray c;
        c.size=1;
        c.positions=(boardPos*)malloc(sizeof(boardPos)); 
        c.positions[0][0]=root->position[0];
        c.positions[0][1]=root->position[1];
        return c;
    }
    while (currChild != NULL) {
        tempCurrPath = getTreeLongestPathRec(currChild->node);
        if (tempCurrPath.size > longestPath.size){
            longestPath = tempCurrPath;
        }
        currChild = currChild->next;
    }
    return insertToBoardPosStart(longestPath,root->position);
}


boardPosArray insertToBoardPosStart(boardPosArray boardPosArr,boardPos new) {
    boardPosArr.positions = realloc(boardPosArr.positions,sizeof(boardPos)*(boardPosArr.size + 1));//
    boardPosArr.positions[boardPosArr.size][0] = new[0];
    boardPosArr.positions[boardPosArr.size][1] = new[1];
    boardPosArr.size++;
    return boardPosArr;
}