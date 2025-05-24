#ifndef MATADJ_H
#define MATADJ_H

#include <stdio.h>

typedef struct {
    int **matAdj;
    int rows_columns;
} MatAdj;

MatAdj* criaMatAdj(int n);
void lerMatAdj(MatAdj *t, FILE *file, int maxCaminhos);
void freeMatAdj(MatAdj *t);

#endif
