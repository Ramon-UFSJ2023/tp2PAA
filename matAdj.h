#ifndef MATADJ_H
#define MATADJ_H

#include <stdio.h>

typedef struct {
    int **matAdj;
    int rows_columns;
} MatAdj;

MatAdj* criaMatAdjProg(int n);
void lerMatAdjProg(MatAdj *t, FILE *file, int maxCaminhos);
void freeMatAdjProg(MatAdj *t);

#endif
