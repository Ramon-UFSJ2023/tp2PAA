#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "cityFunctions.c"
#include "matAdj.h"


int main(){
    int instancias=0, maxCitys=0, maxDist=0, maxWeight=0, maxPaths=0;
    FILE *arq = fopen("entrada.txt", "r");
    fscanf(arq ,"%d", &instancias);
    

    while(instancias > 0){
        fscanf(arq, "%d %d %d %d", &maxCitys, &maxDist, &maxWeight, &maxPaths);

        City povos[maxCitys];
        readCitys(povos, maxCitys, arq);

        MatAdj *CityPovos = createMatAdj(maxCitys);
        readMatAdj(CityPovos, arq, maxPaths);



        freeMatAdj(CityPovos);
        maxCitys=0, maxDist=0, maxWeight=0, maxPaths=0;
        instancias--;
    }

    return 0;
}