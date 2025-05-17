#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "cityFunctions.c"
#include "board.c"


int main(){
    int instancias=0, maxCitys=0, maxDist=0, maxWeight=0, maxPaths=0;
    scanf("%d", &instancias);
    FILE *arq = fopen("entrada.txt", "r");

    while(instancias > 0){
        scanf("%d %d %d %d", &maxCitys, &maxDist, &maxWeight, &maxPaths);

        City povos[maxCitys];
        readCitys(povos, maxCitys, arq);

        Board *C = createBoard(maxCitys);
        readBoard(C, arq, maxPaths);



        maxCitys=0, maxDist=0, maxWeight=0, maxPaths=0;
        instancias--;
    }

    return 0;
}