#include <stdio.h>
#include <stdlib.h>
#include "cityFunctions.h"

void lerCidades(City vetorCidades[], int maxCidade, FILE *entArq){
    int idCidade, peso, habilidade;
    for(int i=0; i<maxCidade; i++){
        if(fscanf(entArq, "%d %d %d", &idCidade, &peso, &habilidade) != 3){fprintf(stderr, "Erro na leitura de povos.\n");return;}
        if(idCidade>= 1 && idCidade<= maxCidade){
            vetorCidades[idCidade-1].peso_soldado =peso;
            vetorCidades[idCidade-1].habilidade = habilidade;
        }else fprintf(stderr, "Erro no indice da cidade.\n");
    }
}