#include <stdio.h>
#include <stdlib.h>
#include "cityFunctions.h"

void readCitys(City vectorCitys[], int maxCitys, FILE *entArq){
    int cityNow=0;
    for(int i=0; i<maxCitys; i++){
        fscanf(entArq,"%d %d %d", &cityNow, &vectorCitys[cityNow].Weight_Soldier, &vectorCitys[cityNow].Hability);
    }
}