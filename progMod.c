#include "progMod.h"

void functionProgMod(City povos[], MatAdj *CityPovosDist, int maxPeso, int max_Dist){
    int distM = max_Dist+1;
    int pesoM = maxPeso+1;
    size_t totalStates = (size_t)CityPovosDist->rows_columns*distM*pesoM;

    int *cityDistPeso = malloc(sizeof(int)*totalStates);
    int *reconstruirCaminhos = malloc(sizeof(int)*totalStates);
    int *soldadosRecrutados = malloc(sizeof(int)*totalStates);

    for(size_t i=0; i< totalStates; i++){
        cityDistPeso[i] = INT_MIN;
        reconstruirCaminhos[i] = -1;
        soldadosRecrutados[i] = 0;
    }

    for(int i=0;i< CityPovosDist->rows_columns; i++){
        int idx = i*distM*pesoM+0*pesoM+0;
        cityDistPeso[idx] = 0;
        reconstruirCaminhos[idx] = idx;
    }

    for(int d=0; d<=max_Dist;d++){
        for(int w=0; w <= maxPeso;w++){
            for(int u=0; u<CityPovosDist->rows_columns; u++){
                int base = u*distM*pesoM+d*pesoM+w;
                int cur = cityDistPeso[base];

                if(cur<0) continue;

                for(int v=0; v<CityPovosDist->rows_columns;v++){
                    int distUV = CityPovosDist->matAdj[u][v];
                    if(distUV <=0) continue;
                    int nd = d+distUV;
                    if(nd> max_Dist) continue;

                    int maxK = (maxPeso-w)/ povos[v].peso_soldado;
                    for(int k =0; k<= maxK; k++){
                        int newW = w+k * povos[v].peso_soldado;
                        int idx = v*distM*pesoM+nd*pesoM+newW;
                        int val = cur+k*povos[v].habilidade;
                        if(val > cityDistPeso[idx]){
                            cityDistPeso[idx] = val;
                        }
                    }
                }
            }
        }
    }

}