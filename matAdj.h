#ifndef MATADJ_H
#define MATADJ_H

#include <stdio.h>

typedef struct {
    int **matAdjProgM;
    int rows_columns;
} MatAdjProgModular;

MatAdjProgModular* criaMatAdjProgM(int n);
void lerMatAdjProgM(MatAdjProgModular *t, FILE *file, int maxCaminhos);
void freeMatAdjProgM(MatAdjProgModular *t);

#endif
