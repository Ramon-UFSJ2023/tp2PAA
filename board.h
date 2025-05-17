#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>

typedef struct {
    int **board;
    int rows_columns;

} Board;

Board* createBoard(int n);
void readBoard(Board *t, FILE *file, int maxPaths);

#endif
