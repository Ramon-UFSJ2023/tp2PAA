#include <stdlib.h>
#include "board.h"

Board* createBoard(int n) {
    Board *t = (Board*)malloc(sizeof(Board));
    t->rows_columns = n;
    t->board = malloc(n*sizeof(int*));
    for(int i=0; i<n;i++){
        t->board[i] = malloc(n*sizeof(int*));
        for(int j =0; j<n; j++){
            t->board[i][j] = 0;
        }
    }

    return t;
}

void readBoard(Board *MatAdj, FILE *arqEnt, int maxPaths){
    int cityNow=0, cityPos=0, cityAtoB_Weight=0;

    for(int i=0; i< maxPaths; i++){
        fscanf(arqEnt, "%d %d %d", &cityNow, &cityPos, &cityAtoB_Weight);
        MatAdj->board[cityNow][cityPos] = cityAtoB_Weight;
        cityAtoB_Weight=0;
    }
}
