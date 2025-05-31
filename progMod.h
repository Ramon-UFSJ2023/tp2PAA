#ifndef PROGMOD_H
#define PROGMOD_H
#include <stdio.h>
#include <stdlib.h>
#include "cityFunctions.h"
#include "matAdj.h"
#include <limits.h>

void functionProgMod(City *povos, MatAdjProgModular *cidadePovosDist, int maxPeso, int max_Dist, FILE* arqSaida);

typedef struct caminhoReverso{
    int cidade;
    int dist;
    int peso;
    int recrutados;
} caminhoReverso;


#endif