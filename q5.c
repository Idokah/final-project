#include "Header.h"


void fourBoardPosToThreeBytes(boardPos *boardPos,BYTE *byteArr,int i, int boardPosSize, int boardPosIndex);

void saveListToBinFile(char *file_name, boardPosArray *pos_arr){
    FILE *file = fopen(file_name, "wb");
    short size = pos_arr->size;
    fwrite(&(size), sizeof(short), 1, file);
    int bytesNum = (((6 * pos_arr->size) / 8 ) + 1);
    BYTE *byteArr = (BYTE *)calloc(bytesNum , sizeof(BYTE));
	assert(byteArr != NULL);
    int boardPosIndex = 0;
    for (int byteArrIndex = 0; byteArrIndex < pos_arr->size; byteArrIndex += 3) {
        fourBoardPosToThreeBytes(pos_arr->positions, byteArr, byteArrIndex, pos_arr->size, boardPosIndex);
        boardPosIndex += 4;
    }
    fwrite(byteArr, sizeof(BYTE),bytesNum, file);
    fclose(file);
    free(byteArr);

}

void fourBoardPosToThreeBytes(boardPos *boardPos,BYTE *byteArr,int byteArrIndex, int boardPosSize, int boardPosIndex){
    // boardPos 1
    byteArr[byteArrIndex] |= (boardPos[boardPosIndex][0]-'A') <<5;
    byteArr[byteArrIndex] |= ((boardPos[boardPosIndex][1]-1)-'0') <<2;
    if (boardPosIndex + 1 >= boardPosSize) return;
    // boardPos 2
    byteArr[byteArrIndex] |= ((boardPos[boardPosIndex+1][0])-'A') >>1;
    byteArr[byteArrIndex+1] |= ((boardPos[boardPosIndex+1][0]-1)-'0') <<7;
    byteArr[byteArrIndex+1] |= ((boardPos[boardPosIndex+1][1]-1)-'0') <<4;
    if (boardPosIndex + 2 >= boardPosSize) return;
    // boardPos 3
    byteArr[byteArrIndex+1] |= ((boardPos[boardPosIndex+2][0])-'A') <<1;
    byteArr[byteArrIndex+1] |= ((boardPos[boardPosIndex+2][1]-1)-'0') >>2;
    byteArr[byteArrIndex+2] |= ((boardPos[boardPosIndex+2][1]-1)-'0') <<6;
    if (boardPosIndex + 3 >= boardPosSize) return;
    // boardPos 4
    byteArr[byteArrIndex+2] |= ((boardPos[boardPosIndex+3][0])-'A') <<3;
    byteArr[byteArrIndex+2] |= ((boardPos[boardPosIndex+3][1]-1)-'0');
}