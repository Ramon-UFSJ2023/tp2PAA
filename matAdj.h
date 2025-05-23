#ifndef MATADJ_H
#define MATADJ_H

#include <stdio.h>

typedef struct {
    int **matAdj;
    int rows_columns;

} MatAdj;

MatAdj* createMatAdj(int n);
void readMatAdj(MatAdj *t, FILE *file, int maxPaths);
void freeMatAdj(MatAdj *t);

#endif
