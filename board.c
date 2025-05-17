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

void readBoard(Board *t, FILE *file) {
    for (int i = t->rows_columns - 1; i >= 0; i--) {
        for (int j = 0; j < t->rows_columns; j++) {
            if ((i + j) % 2 == 0) {
                int value;
                if (fscanf(file, "%d", &value) == 1) {
                    t->board[i][j] = value;
                }
            }
        }
    }
}
