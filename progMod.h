#ifndef PROGMOD_H
#define PROGMOD_H
#include <stdio.h>
#include <stdlib.h>
#include "cityFunctions.h"
#include "matAdj.h"
#include <limits.h>

int functionProgMod(City *povos, MatAdj *cidadePovosDist, int maxPeso, int max_Dist, int* habilidadeMaxima, int *melhorCaminho);


#endif