#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "cityFunctions.c"
#include "matAdj.h"
#include "progMod.h"


int main(){
    int instancias=0, maxCidades=0, maxDist=0, maxPeso=0, maxCaminhos=0;
    FILE *arqEnt = fopen("entrada.txt", "r");
    if(arqEnt == NULL) exit(1);
    if(fscanf(arqEnt, "%d", &instancias)!= 1){fclose(arqEnt); exit(1);}

    while(instancias>0){
        if(fscanf(arqEnt, "%d %d %d %d", &maxCidades, &maxDist, &maxPeso, &maxCaminhos)!= 4){break;}

        if(maxCidades<=0){
            fprintf(stderr, "Numero de cidades Invalido.\n");
            instancias--;
            continue;
        }

        City *povos = malloc(maxCaminhos*sizeof(City));
        if(povos == NULL){fprintf(stderr, "Erro na alocação de cidades");break;}
        lerCidades(povos, maxCidades, arqEnt);

        MatAdj *mundoZambis = criaMatAdj(maxCidades);
        lerMatAdj(mundoZambis, arqEnt, maxCaminhos);

        //Logica

        //julia
        printf("Instance Data:\n");
        printf("MaxCities: %d, MaxDist: %d, maxPeso: %d, maxCaminhos: %d\n", maxCidades, maxDist, maxPeso, maxCaminhos);
        for (int i = 0; i < maxCidades; i++) {
            printf("City %d (file ID %d): Peso %d, Hability %d\n", i, i + 1, povos[i].peso_soldado, povos[i].habilidade);
        }
        printf("Adjacency Matrix:\n");
        for (int i = 0; i < maxCidades; i++) {
            for (int j = 0; j < maxCidades; j++) {
                printf("%d ", mundoZambis->matAdj[i][j]);
            }
            printf("\n");
        }
        printf("-----------------------------------\n");
        //julia

        freeMatAdj(mundoZambis);
        free(povos);

    }
    fclose(arqEnt);
    return 0;
}