#include "progMod.h"
#define INACESSIVEL (INT_MIN/2)

void functionProgMod(City *povos, MatAdj *cidadePovosDist, int maxPeso, int max_Dist, FILE* arqSaida){
    int totalDistancias= max_Dist+1;
    int totalPeso =maxPeso+1;
    int cidadeFinal =0, pesoFinal=0, distanciaFinal=0;

    int ***tabelaDinamica = malloc(cidadePovosDist->rows_columns*sizeof(int**));
    if(tabelaDinamica == NULL){return;}
    
    for(int cidadeAtual=0; cidadeAtual<cidadePovosDist->rows_columns; cidadeAtual++){
        tabelaDinamica[cidadeAtual] = malloc(totalDistancias * sizeof(int*));
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
                if(habilidadeAtual <= INACESSIVEL) continue;

                //recrutamento
                int pesoSoldado = povos[cidade].peso_soldado;
                if(pesoSoldado <=0) continue;
                int habilidadeCidadeAtual = povos[cidade].habilidade;
                int maxRecrutavel = (maxPeso-pesoCarregado)/pesoSoldado;

                for(int quantidade=1; quantidade <= maxRecrutavel; quantidade++){
                    int novoPeso = pesoCarregado+(quantidade*pesoSoldado);
                    int novaHabilidade = habilidadeAtual+(quantidade*habilidadeCidadeAtual);
                    if(novaHabilidade >tabelaDinamica[cidade][distPercorrida][novoPeso]){
                        tabelaDinamica[cidade][distPercorrida][novoPeso] =novaHabilidade;
                    }
                }

                //indo para outra cidade
                for(int cidadeVizinha =0; cidadeVizinha< cidadePovosDist->rows_columns; cidadeVizinha++){
                    int distanciaCidadeAtoB = cidadePovosDist->matAdj[cidade][cidadeVizinha];
                    if(distanciaCidadeAtoB != INT_MAX && (distPercorrida+ distanciaCidadeAtoB) <totalDistancias){
                        int habilidadeDestino = tabelaDinamica[cidadeVizinha][distPercorrida+distanciaCidadeAtoB][pesoCarregado];
                        if(habilidadeAtual > habilidadeDestino) tabelaDinamica[cidadeVizinha][distPercorrida+distanciaCidadeAtoB][pesoCarregado] = habilidadeAtual;
                    }
                }

            }
        }
    }
    int habilidadeMaximas = 0;
    for(int cidadeAtual =0; cidadeAtual<cidadePovosDist->rows_columns;cidadeAtual++){
        for(int distPercorrida =0; distPercorrida <totalDistancias; distPercorrida++){
            for(int pesoCar =0; pesoCar< totalPeso; pesoCar++){
                if(tabelaDinamica[cidadeAtual][distPercorrida][pesoCar] > habilidadeMaximas){
                    habilidadeMaximas =tabelaDinamica[cidadeAtual][distPercorrida][pesoCar];
                    cidadeFinal= cidadeAtual;
                    pesoFinal = pesoCar;
                    distanciaFinal = distPercorrida;
                }
            }
        }
    }
    int qtdPovos = cidadePovosDist->rows_columns;
    caminhoReverso Caminho[qtdPovos*totalDistancias*totalPeso];
    int cddAtual = cidadeFinal;
    int dstAtual = distanciaFinal;
    int psAtual = pesoFinal;
    int indiceCaminho=0;
    
    while(1){
        int achou=0;
        int pesoSoldado = povos[cddAtual].peso_soldado;
        int habilidadeSoldado =povos[cddAtual].habilidade;

        if(pesoSoldado>0){
            for(int qtd=1; qtd*pesoSoldado<=psAtual;qtd++){
            int pesoAnterior = psAtual -qtd*pesoSoldado;
            int habilidadeAnterior = tabelaDinamica[cddAtual][dstAtual][pesoAnterior];
            if(habilidadeAnterior+qtd*habilidadeSoldado == tabelaDinamica[cddAtual][dstAtual][psAtual]){
                Caminho[indiceCaminho++] = (caminhoReverso){cddAtual, dstAtual, pesoAnterior, qtd};
                psAtual = pesoAnterior;
                achou =1;
                break;

                }
            }
        }
        
        if(achou == 1) continue;

        int moveu=0;
        for(int cidadeAnterior = 0; cidadeAnterior<qtdPovos; cidadeAnterior++){
            int distAresta = cidadePovosDist->matAdj[cidadeAnterior][cddAtual];
            if(distAresta != INT_MAX && dstAtual-distAresta>=0){
                int habilidadeAnterior = tabelaDinamica[cidadeAnterior][dstAtual-distAresta][psAtual];
                if(habilidadeAnterior == tabelaDinamica[cddAtual][dstAtual][psAtual]){
                    Caminho[indiceCaminho++] = (caminhoReverso){cidadeAnterior, dstAtual-distAresta,psAtual,0};
                    cddAtual = cidadeAnterior;
                    dstAtual = dstAtual-distAresta;
                    moveu =1;
                    break;
                }
            }
        }
        if(!moveu) break;
    }
    fprintf(arqSaida,"%d", habilidadeMaximas);
    
    int sddPorCidade[qtdPovos];
    for(int i=0; i<qtdPovos;i++) sddPorCidade[i]=0;
    for(int i=0; i<indiceCaminho;i++) sddPorCidade[Caminho[i].cidade] += Caminho[i].recrutados;

    int apareceu[qtdPovos];
    for(int i=0; i<qtdPovos;i++) apareceu[i]=0;
    for(int i=0; i<indiceCaminho;i++) apareceu[Caminho[i].cidade]=1;

    for(int i=0; i <qtdPovos;i++){
        if(apareceu[i]){
            fprintf(arqSaida, " %d %d", i+1, sddPorCidade[i]);
        }
    }

    printf("\n");
    for(int cidade=0; cidade< cidadePovosDist->rows_columns;cidade++){
        for(int distPercorrida=0; distPercorrida< totalDistancias;distPercorrida++){
            free(tabelaDinamica[cidade][distPercorrida]);
        }
        free(tabelaDinamica[cidade]);
    }
    free(tabelaDinamica);
}
