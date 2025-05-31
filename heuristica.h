#ifndef HEURISTICA_H
#define HEURISTICA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

    MatAdj* criarMatAdj(int n);
    void lerMatAdj(MatAdj *t, FILE *file, int maxCaminhos);
    void freeMatAdj(MatAdj *t);
    void lerCidades(Cidade vetorCidades[], int maxCidades, FILE *entArq);
    void lerCidades(Cidade vetorCidades[], int maxCidades, FILE *entArq);
    int compararRazao(const void *a, const void *b);
    void inicializarSolucao(Solucao *s);
    Solucao recrutar(Cidade vetorCidades[], int numPovos, MatAdj *mundo, int capacidadeNave, int maxDistancia);

#endif