#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "cityFunctions.h"
#include "matAdj.h"
#include "progMod.h"
#include "heuristica.h"


int main(){
    int instancias=0, maxCidades=0, maxDist=0, maxPeso=0, maxCaminhos=0, escolha =0;
    FILE *arqEnt = fopen("entrada.txt", "r");
    FILE *arqSaida = fopen("saida.txt", "w");
    if(arqEnt == NULL) exit(1);
    if(fscanf(arqEnt, "%d", &instancias)!= 1){fclose(arqEnt); exit(1);}
    printf("Digite 0 para Prog.Modular\nDigite 1 para Heuristica\n");
    scanf("%d", &escolha);
    while(instancias>0){
        switch (escolha){
        case 0:
            if(fscanf(arqEnt, "%d %d %d %d", &maxCidades, &maxDist, &maxPeso, &maxCaminhos)!= 4){instancias--;break;}
            if(maxCidades<=0){
                fprintf(stderr, "Numero de cidades Invalido.\n");
                instancias--;
                continue;
            }
            City *povos = malloc(maxCidades*sizeof(City));
            if(povos == NULL){fprintf(stderr, "Erro na alocação de cidades");break;}
            lerCidadesProg(povos, maxCidades, arqEnt);

            MatAdjProgModular *mundoZambisProg = criaMatAdjProgM(maxCidades);
            lerMatAdjProgM(mundoZambisProg, arqEnt, maxCaminhos);
            functionProgMod(povos, mundoZambisProg, maxPeso, maxDist, arqSaida);
            freeMatAdjProgM(mundoZambisProg);
            free(povos);
            instancias--;
            escolha = 0;
            break;
        case 1:
            if (fscanf(arqEnt, "%d %d %d %d", &maxCidades, &maxDist, &maxPeso, &maxCaminhos) != 4) {
                fprintf(stderr, "Error reading instance parameters.\n");
                fprintf(arqSaida, "Error processing instance.\n");
                instancias--;
                break;
            }

            if (maxCidades <= 0){
                fprintf(stderr, "Invalid number of cities: %d for an instance.\n", maxCidades);
                fprintf(arqSaida, "0\n"); 

                instancias--;
                continue;
            }
            Cidade *povosHeuristica = malloc(maxCidades * sizeof(Cidade));
            for(int i=0; i<maxCidades; ++i) {
                        povosHeuristica[i].id = 0; 
                        povosHeuristica[i].peso = 0;
                        povosHeuristica[i].habilidade = 0;
                        povosHeuristica[i].razao = 0.0;
                    }
            lerCidades(povosHeuristica, maxCidades, arqEnt);

            MatAdj *mundoZambis = criarMatAdj(maxCidades);
            lerMatAdj(mundoZambis, arqEnt, maxCaminhos);

            Solucao resultadoHeuristica = recrutar(povosHeuristica, maxCidades, mundoZambis, maxPeso, maxDist);

            if (resultadoHeuristica.habilidadeTotal > 0 && resultadoHeuristica.numEtapas > 0){
                fprintf(arqSaida, "%d", resultadoHeuristica.habilidadeTotal);
                for (int k = 0; k < resultadoHeuristica.numEtapas; k++){

                    if (resultadoHeuristica.etapas[k].idCidade > 0) {
                        fprintf(arqSaida, " %d %d", resultadoHeuristica.etapas[k].idCidade, resultadoHeuristica.etapas[k].soldadosRecrutados);
                    }
                }
                fprintf(arqSaida, "\n");
            } else {
                fprintf(arqSaida, "0\n"); 
            }

            freeMatAdj(mundoZambis);
            free(povosHeuristica);
            instancias--;
            escolha =1;
            break;
        
        default:
            fprintf(arqSaida, "Entrada de escolha errada.\n");
            break;
        }
    }
    fclose(arqEnt);
    fclose(arqSaida);
    return 0;
}