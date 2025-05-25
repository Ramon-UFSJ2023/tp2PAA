#include "progMod.h"
int maximo(int a, int b){return a>b ? a : b;}
#define INACESSIVEL (INT_MIN/2)

int functionProgMod(City *povos, MatAdj *cidadePovosDist, int maxPeso, int max_Dist, int* habilidadeMaxima, int *melhorCaminho){
    int totalDistancias= max_Dist+1;
    int totalPeso =maxPeso+1;

    int ***tabelaDinamica = malloc(cidadePovosDist->rows_columns*sizeof(int**));
    if(tabelaDinamica == NULL){habilidadeMaxima = 0; return;}
    
    for(int cidadeAtual=0; cidadeAtual<cidadePovosDist->rows_columns; cidadeAtual++){
        for(int distPercorrida = 0; distPercorrida<totalDistancias;distPercorrida++){
            tabelaDinamica[cidadeAtual][distPercorrida] = malloc((totalPeso)*sizeof(int));
            for(int pesoCarr=0; pesoCarr<totalPeso;pesoCarr++){
                tabelaDinamica[cidadeAtual][distPercorrida][pesoCarr] = INACESSIVEL;
            }
        }
    }
    for(int cidades =0; cidades<cidadePovosDist->rows_columns;cidades++) tabelaDinamica[cidades][0][0] = 0;
    
    
    for(int distPercorrida =0; distPercorrida <totalDistancias; distPercorrida++){
        for(int pesoCarregado = 0; pesoCarregado< totalPeso; pesoCarregado++){
            for(int cidade =0; cidade< cidadePovosDist->rows_columns; cidade++){
                int habilidadeAtual = tabelaDinamica[cidade][distPercorrida][pesoCarregado];
                if(habilidadeAtual < INACESSIVEL) continue;

                //recrutamento
                int pesoSoldado = povos[cidade].peso_soldado;
                int habilidadeCidadeAtual = povos[cidade].habilidade;
                int maxRecrutavel = (maxPeso-pesoCarregado)/pesoSoldado;
                for(int quantidade =1; quantidade <= maxRecrutavel; quantidade++){
                    int novoPeso = pesoCarregado+(quantidade*pesoSoldado);
                    int novaHabilidade = habilidadeAtual+(quantidade*habilidadeCidadeAtual);
                    if(novaHabilidade >tabelaDinamica[cidade][distPercorrida][novoPeso]){
                        tabelaDinamica[cidade][distPercorrida][novoPeso] =novaHabilidade;
                    }
                }
                //indo para outra cidade
                for(int cidadeVizinha =0; cidadeVizinha< cidadePovosDist->rows_columns; cidadeVizinha++){
                    int distanciaCidadeAtoB = cidadePovosDist->matAdj[cidade][cidadeVizinha];
                    if(distanciaCidadeAtoB < INACESSIVEL && distPercorrida+ distanciaCidadeAtoB <totalDistancias){
                        int habilidadeDestino = tabelaDinamica[cidadeVizinha][distPercorrida+distanciaCidadeAtoB][pesoCarregado];
                        if(habilidadeAtual > habilidadeDestino) tabelaDinamica[cidadeVizinha][distPercorrida+distanciaCidadeAtoB][pesoCarregado] = habilidadeAtual;
                    }
                }

            }
        }
    }
    int habilidadeMaxima = 0;
    for(int cidadeAtual =0; cidadeAtual<cidadePovosDist->rows_columns;cidadeAtual++){
        for(int distPercorrida =0; distPercorrida <totalDistancias; distPercorrida++){
            for(int pesoCar =0; pesoCar< totalPeso; pesoCar++){
                if(tabelaDinamica[cidadeAtual][distPercorrida][pesoCar] > habilidadeMaxima) habilidadeMaxima =tabelaDinamica[cidadeAtual][distPercorrida][pesoCar]; 
            }
        }
    }
    return habilidadeMaxima;
}