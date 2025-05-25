#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "cityFunctions.h"
#include "matAdj.h"
#include "progMod.h"


int main(){
    int instancias=0, maxCidades=0, maxDist=0, maxPeso=0, maxCaminhos=0;
    FILE *arqEnt = fopen("entrada.txt", "r");
    if(arqEnt == NULL) exit(1);
    if(fscanf(arqEnt, "%d", &instancias)!= 1){fclose(arqEnt); exit(1);}

    while(instancias>0){
        int a=0;
        if(fscanf(arqEnt, "%d %d %d %d", &maxCidades, &maxDist, &maxPeso, &maxCaminhos)!= 4){break;}

        if(maxCidades<=0){
            fprintf(stderr, "Numero de cidades Invalido.\n");
            instancias--;
            continue;
        }

        City *povos = malloc(maxCidades*sizeof(City));
        if(povos == NULL){fprintf(stderr, "Erro na alocação de cidades");break;}
        lerCidades(povos, maxCidades, arqEnt);

        MatAdj *mundoZambis = criaMatAdj(maxCidades);
        lerMatAdj(mundoZambis, arqEnt, maxCaminhos);
        a = functionProgMod(povos, mundoZambis, maxPeso, maxDist);

        printf("%d\n\n", a);
    
        freeMatAdj(mundoZambis);
        free(povos);
        instancias--;
    }
    fclose(arqEnt);
    return 0;
}