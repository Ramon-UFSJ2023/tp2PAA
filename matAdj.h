#ifndef MATADJ_H
#define MATADJ_H

#include <stdio.h>

typedef struct {
    int **matAdjProgM;
    int rows_columns;
} MatAdjProgModular;

MatAdjProgModular* criaMatAdjProgMProg(int n);
void lerMatAdjProgMProg(MatAdjProgModular *t, FILE *file, int maxCaminhos);
void freeMatAdjProgMProg(MatAdjProgModular *t);

#endif
