#include <stdlib.h>
#include "matAdj.h"

MatAdj* criaMatAdj(int n) {
    MatAdj *t = (MatAdj*)malloc(sizeof(MatAdj));
    if(t== NULL) exit(1);

    t->rows_columns = n;
    t->matAdj = malloc(n*sizeof(int*));
    if(t->matAdj == NULL){free(t);exit(1);} //Erro na alocação

    for(int i=0; i<n;i++){
        t->matAdj[i] = malloc(n*sizeof(int));
        if(t->matAdj[i] == NULL){
            for(int j=0; j<i; j++) free(t->matAdj[j]);
            free(t->matAdj);
            free(t);
            exit(1);
        }
        for(int j =0; j<n; j++){
            t->matAdj[i][j] = 0;
        }
    }
    return t;
}

void lerMatAdj(MatAdj *adjMatrix, FILE *arqEnt, int maxCaminhos) {
    int cidadeOrigem, cidadeDestino, pesoCaminho;
    for(int i=0; i<maxCaminhos;i++){
        if(fscanf(arqEnt, "%d %d %d", &cidadeOrigem, &cidadeDestino, &pesoCaminho) != 3){fprintf(stderr, "Erro na entrada.\n");return;}
        if((cidadeOrigem>=1 && cidadeOrigem <= adjMatrix->rows_columns)&&(cidadeDestino>=1 && cidadeDestino<=adjMatrix->rows_columns)){
            adjMatrix->matAdj[cidadeOrigem-1][cidadeDestino-1] = pesoCaminho;
            adjMatrix->matAdj[cidadeDestino-1][cidadeOrigem-1] = pesoCaminho;
        }else fprintf(stderr, "Erro na leitura de caminhos.\n");
    }

}

void freeMatAdj(MatAdj *freeMat){
    if (freeMat == NULL) return;
    if (freeMat->matAdj != NULL) {
        for (int i = 0; i < freeMat->rows_columns; i++) {
            free(freeMat->matAdj[i]);
        }
        free(freeMat->matAdj);
    }
    free(freeMat);
}