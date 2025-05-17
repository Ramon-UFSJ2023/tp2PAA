#include <stdio.h>
#include <stdlib.h>
#include "structs.h"


int main(){
    int instancias=0, maxCitys=0, maxDist=0, maxWeight=0, maxPaths=0, cityNow=0;
    scanf("%d", &instancias);
    FILE *arq = fopen("entrada.txt", "r");

    while(instancias > 0){
        scanf("%d %d %d %d", &maxCitys, &maxDist, &maxWeight, &maxPaths);
        City povos[maxCitys];
        for(int i =0; i<maxCitys;i++){
            scanf("%d", &cityNow);
            scanf("%d", &povos[cityNow].Weight_Soldier);
            scanf("%d", &povos[cityNow].Hability);
        }
        

        instancias--;
    }

    return 0;
}