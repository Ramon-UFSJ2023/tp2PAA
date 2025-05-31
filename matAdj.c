#include <stdlib.h>
#include "matAdj.h"
#include <limits.h>

#define INACESSIVEL_MAT INT_MAX

MatAdjProgModular* criaMatAdjProgM(int n){
    MatAdjProgModular *t = (MatAdjProgModular*)malloc(sizeof(MatAdjProgModular));
    if(t== NULL) exit(1);

    t->rows_columns = n;
    t->matAdjProgM = malloc(n*sizeof(int*));
    if(t->matAdjProgM == NULL){free(t);exit(1);} //Erro na alocação

    for(int i=0; i<n;i++){
        t->matAdjProgM[i] = malloc(n*sizeof(int));
        if(t->matAdjProgM[i] == NULL){
            for(int j=0; j<i; j++) free(t->matAdjProgM[j]);
            free(t->matAdjProgM);
            free(t);
            exit(1);
        }
        for(int j =0; j<n; j++){
            t->matAdjProgM[i][j] = INACESSIVEL_MAT;
        }
    }
    return t;
}

void lerMatAdjProgM(MatAdjProgModular *adjMatrix, FILE *arqEnt, int maxCaminhos) {
    int cidadeOrigem, cidadeDestino, pesoCaminho;
    for(int i=0; i<maxCaminhos;i++){
        if(fscanf(arqEnt, "%d %d %d", &cidadeOrigem, &cidadeDestino, &pesoCaminho) != 3){fprintf(stderr, "Erro na entrada.\n");return;}
        if((cidadeOrigem>=1 && cidadeOrigem <= adjMatrix->rows_columns)&&(cidadeDestino>=1 && cidadeDestino<=adjMatrix->rows_columns)){
            adjMatrix->matAdjProgM[cidadeOrigem-1][cidadeDestino-1] = pesoCaminho;
            adjMatrix->matAdjProgM[cidadeDestino-1][cidadeOrigem-1] = pesoCaminho;
        }else fprintf(stderr, "Erro na leitura de caminhos.\n");
    }

}

void freeMatAdjProgM(MatAdjProgModular *freeMat){
    if (freeMat == NULL) return;
    if (freeMat->matAdjProgM != NULL) {
        for (int i = 0; i < freeMat->rows_columns; i++) {
            free(freeMat->matAdjProgM[i]);
        }
        free(freeMat->matAdjProgM);
    }
    free(freeMat);
}