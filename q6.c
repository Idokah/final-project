#include "Header.h"
#define _CRT_SECURE_NO_WARNINGS
boardPosArray readPathFromFile(char *file_name);
void threeBytesToThreeBoardPos(BYTE *data, boardPos *boardPosArr, int i, short boardPosArrSize);
bool isPathExists(pathTree pathTree, boardPosArray path);
bool isPathExistsRec(treeNode *node, boardPos *boardPosArr,int size);


int checkAndDisplayPathFromFile(char *file_name, movesArray **moves, char **board){
    boardPosArray path = readPathFromFile(file_name);
    pathTree pathTree = findAllPossiblePaths(path.positions[0], moves, board);
    isPathExists(pathTree, path);
}

boardPosArray readPathFromFile(char *file_name){
    FILE *file = fopen(file_name,"rb");
    short boardPosArrSize;
    fread(&boardPosArrSize, sizeof(short), 1, file);
    boardPosArray boardPosArray;
    boardPosArray.positions = (boardPos *)malloc(sizeof(boardPos) * boardPosArrSize);
    boardPosArray.size = boardPosArrSize;
    int boardPosSize = ((boardPosArrSize * 6) / 8) + 1;
    BYTE tempData[3];	//we read 3 bytes each time
    int boardPosIndex = 0;
    for (int byteArrIndex = 0; byteArrIndex < boardPosSize; byteArrIndex += 3) {
        fread(tempData, sizeof(BYTE), 3, file);
        threeBytesToThreeBoardPos(tempData, boardPosArray.positions, boardPosIndex , boardPosArrSize);
        boardPosIndex +=4;
    }
    return boardPosArray;
}

void threeBytesToThreeBoardPos(BYTE *data, boardPos *boardPosArr, int boardPosIndex, short boardPosArrSize) {
    BYTE mask1 = 0xE0;	//11100000  byte 1 (most significant byte - the left most one)
    BYTE mask2 = 0x1C;	//00011100  byte 1
    BYTE mask3a = 0x03, mask3b = 0x80;	//0000 0011 1000 0000 bytes 1+2
    BYTE mask4 = 0x70;	//01110000  byte 2
    BYTE mask5 = 0x0E;	//00001110  byte 2
    BYTE mask6a = 0x01, mask6b = 0xC0;	//0000000111000000 bytes 2+3
    BYTE mask7 = 0x38;	//00111000  byte 3 (least significant byte)
    BYTE mask8 = 0x07;	//00000111	byte 3

    // boardPos1
    boardPosArr[boardPosIndex][0] = ((data[0] & mask1) >> 5) + 'A';
    boardPosArr[boardPosIndex][1] = (((data[0] & mask2) >> 2)+1)+'0';
    if (boardPosIndex+1 >= boardPosArrSize) return;
    // boardPos2
    boardPosArr[boardPosIndex+1][0] = (((data[0] & mask3a) << 1) | ((data[1] & mask3b) >> 7))+'A';
    boardPosArr[boardPosIndex+1][1] = (((data[1] & mask4) >> 4)+1)+'0';
    if (boardPosIndex+2 >= boardPosArrSize) return;
    // boardPos3
    boardPosArr[boardPosIndex+2][0] = ((data[1] & mask5) >> 1)+'A';
    boardPosArr[boardPosIndex+2][1] = ((((data[1] & mask6a) << 2) | ((data[2] & mask6b) >> 6))+1)+'0';
    if (boardPosIndex+3 >= boardPosArrSize) return;
    // boardPos4
    boardPosArr[boardPosIndex+3][0] = ((data[2] & mask7) >> 3)+'A';
    boardPosArr[boardPosIndex+3][1] = ((data[2] & mask8)+1)+'0';
}

bool isPathExists(pathTree pathTree, boardPosArray boardPosArr){
	if (isPathExistsRec(pathTree.head, boardPosArr.positions, boardPosArr.size))
		printf("T");
	else printf("F");
}


bool isBoardPosEqual(boardPos boardPos1, boardPos boardPos2) {
	return boardPos1[0] == boardPos2[0] && boardPos1[1] == boardPos2[1];
}

bool isPathExistsRec(treeNode *node, boardPos *boardPosArr, int size){
	if (size == 1)
		return (isBoardPosEqual(boardPosArr[0],node->position));
	else {
		if (isBoardPosEqual(boardPosArr[0], node->position)) {
			treeNodeListCell *curr = node->next_possible_positions;
			while (curr != NULL) {
				if (isPathExistsRec(curr->node, boardPosArr + 1, size - 1))
					return true;
				curr=curr->next;
			}
			return false;
		}
		else return false;
	}

}

