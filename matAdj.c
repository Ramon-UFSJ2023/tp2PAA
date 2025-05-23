#include <stdlib.h>
#include "matAdj.h"

MatAdj* createMatAdj(int n) {
    MatAdj *t = (MatAdj*)malloc(sizeof(MatAdj));
    t->rows_columns = n;
    t->matAdj = malloc(n*sizeof(int*));
    for(int i=0; i<n;i++){
        t->matAdj[i] = malloc(n*sizeof(int*));
        for(int j =0; j<n; j++){
            t->matAdj[i][j] = 0;
        }
    }

    return t;
}

void readMatAdj(MatAdj *MatAdj, FILE *arqEnt, int maxPaths){
    int cityOrigem=0, cityDestiny=0, cityAtoB_Weight=0;

    for(int i=0; i< maxPaths; i++){
        fscanf(arqEnt, "%d %d %d", &cityOrigem, &cityDestiny, &cityAtoB_Weight);
        MatAdj->matAdj[cityOrigem][cityDestiny] = cityAtoB_Weight;
        MatAdj->matAdj[cityDestiny][cityOrigem] = cityAtoB_Weight;
        cityAtoB_Weight=0;
    }
}

void freeMatAdj(MatAdj *freeMat){
    for (int i = 0; i < freeMat->rows_columns; i++){
        free(freeMat->matAdj[i]);
    }
    free(freeMat->matAdj);
    free(freeMat);
}