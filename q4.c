#include "Header.h"
#include "list.h"

int getCountOfValidPositions(char **board);
boardPosArray getTreeLongestPath(pathTree *tree);
boardPosArray getTreeLongestPathRec(treeNode *root);
boardPosArray insertToBoardPosStart(boardPosArray boardPosArr,boardPos new);

// move to generic place
movesList initNewMoveList1(moveCell *head, moveCell *tail) {
    movesList movesLst;
    movesLst.head = head;
    movesLst.tail = tail;
    return movesLst;
}

void getMovesList(boardPosArray boardPosArray, movesList *ptrMovesList){
    int row, col;
    boardPos prev, curr;
    moveCell *prevMoveCell = NULL;
    movesList moves = initNewMoveList1(NULL,NULL);
    for (int i = 0; i < boardPosArray.size - 1; ++i) {
        prev[0] = boardPosArray.positions[i][0];
        prev[1] = boardPosArray.positions[i][1];
        curr[0] = boardPosArray.positions[i+1][0];
        curr[1] = boardPosArray.positions[i+1][1];
        row = curr[0] - prev[0];
        col = curr[1] - prev[1];
        moveCell newMove = initNewMoveCell(initNewMove(row,col), NULL, prevMoveCell);
        addToEndOfList(&newMove, &moves);
        prevMoveCell = &newMove;
    }
    moves.tail = prevMoveCell;
    *ptrMovesList = moves;
    // free boardPosArray?
}

movesList *findPathCoveringAllBoard(boardPos start, movesArray **moves, char **board){
    int validPosNum = getCountOfValidPositions(board);
    pathTree pathTree = findAllPossiblePaths(start, moves, board);
    boardPosArray longestPath = getTreeLongestPath(&pathTree);
//    if (longestPath.size == validPosNum){
//        getMovesList(longestPath);
//    }
    return NULL;
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
    boardPosArr.size++;
    boardPosArr.positions=realloc(boardPosArr.positions,sizeof(boardPos)*(boardPosArr.size));
//    for (int i = 1; i < boardPosArr.size ; i++){
//        boardPosArr.positions[i][0]=boardPosArr.positions[i-1][0];
//        boardPosArr.positions[i][1]=boardPosArr.positions[i-1][1];
//    }
//
    // not very efficient - maybe insert straight into list
    for (int i = boardPosArr.size - 1 ; i >= 1 ; i--){
        boardPosArr.positions[i][0] = boardPosArr.positions[i-1][0];
        boardPosArr.positions[i][1] = boardPosArr.positions[i-1][1];
    }
    boardPosArr.positions[0][0] = new[0];
    boardPosArr.positions[0][1] = new[1];
    return boardPosArr;
}