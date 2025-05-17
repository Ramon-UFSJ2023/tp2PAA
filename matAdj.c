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
    int cityNow=0, cityPos=0, cityAtoB_Weight=0;

    for(int i=0; i< maxPaths; i++){
        fscanf(arqEnt, "%d %d %d", &cityNow, &cityPos, &cityAtoB_Weight);
        MatAdj->matAdj[cityNow][cityPos] = cityAtoB_Weight;
        cityAtoB_Weight=0;
    }
}
