#include "Header.h"

typedef unsigned char BYTE;

void threeBoardPosToThreeBytes(boardPos *boardPos,BYTE *byteArr,int i, int boardPosCount);

void saveListToBinFile(char *file_name, boardPosArray *pos_arr){
    FILE *file = fopen(file_name, "wb");
    short size=pos_arr->size;
    fwrite(&(size), sizeof(short), 1, file);
    int bytesNum = (((6 * pos_arr->size) / 8 ) + 1);
    BYTE *byteArr = (BYTE *) calloc(bytesNum , sizeof(BYTE));
    for (int i = 0; i < pos_arr->size; i += 3) {
        threeBoardPosToThreeBytes(pos_arr->positions, byteArr, i, pos_arr->size);
    }
    fwrite(byteArr, sizeof(BYTE),bytesNum, file);
    fclose(file);
    free(byteArr);

}

void threeBoardPosToThreeBytes(boardPos *boardPos,BYTE *byteArr,int i, int boardPosCount){
    // boardPos 1
    byteArr[i]|=(boardPos[i][0]-'A')<<5;
    byteArr[i]|=((boardPos[i][1]-1)-'0')<<2;
    if (i+1 >= boardPosCount-1) return;
    // boardPos 2
    byteArr[i]|=((boardPos[i+1][0])-'A')>>1;
    byteArr[i+1]|=((boardPos[i+1][0]-1)-'0')<<7;
    byteArr[i+1]|=((boardPos[i+1][1]-1)-'0')<<4;
    if (i+2 >= boardPosCount-1) return;
    // boardPos 3
    byteArr[i+1]|=((boardPos[i+2][0])-'A')<<1;
    byteArr[i+1]|=((boardPos[i+2][1]-1)-'0')>>2;
    byteArr[i+2]|=((boardPos[i+2][1]-1)-'0')<<6;
    if (i+3 >= boardPosCount-1) return;
    // boardPos 4
    byteArr[i+2]|=((boardPos[i+3][0])-'A')<<3;
    byteArr[i+2]|=((boardPos[i+3][1]-1)-'0');
}