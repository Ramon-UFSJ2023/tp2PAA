#include "progMod.h"

void functionProgMod(City povos[], MatAdj *CityPovosDist, int max_Weight, int max_Dist){
    int distM = max_Dist+1;
    int weightM = max_Weight+1;
    size_t totalStates = (size_t)CityPovosDist->rows_columns*distM*weightM;

    int *cityDistPeso = malloc(sizeof(int)*totalStates);
    int *reconstruirCaminhos = malloc(sizeof(int)*totalStates);
    int *soldierRecrutados = malloc(sizeof(int)*totalStates);

    for(size_t i=0; i< totalStates; i++){
        cityDistPeso[i] = INT_MIN;
        reconstruirCaminhos[i] = -1;
        soldierRecrutados[i] = 0;
    }

    for(int i=0;i< CityPovosDist->rows_columns; i++){
        int idx = i*distM*weightM+0*weightM+0;
        cityDistPeso[idx] = 0;
        reconstruirCaminhos[idx] = idx;
    }

    for(int d=0; d<=max_Dist;d++){
        for(int w=0; w <= max_Weight;w++){
            for(int u=0; u<CityPovosDist->rows_columns; u++){
                int base = u*distM*weightM+d*weightM+w;
                int cur = cityDistPeso[base];

                if(cur<0) continue;

                for(int v=0; v<CityPovosDist->rows_columns;v++){
                    int distUV = CityPovosDist->matAdj[u][v];
                    if(distUV <=0) continue;
                    int nd = d+distUV;
                    if(nd> max_Dist) continue;

                    int maxK = (max_Weight-w)/ povos[v].Weight_Soldier;
                    for(int k =0; k<= maxK; k++){
                        int newW = w+k * povos[v].Weight_Soldier;
                        int idx = v*distM*weightM+nd*weightM+newW;
                        int val = cur+k*povos[v].Hability;
                        if(val > cityDistPeso[idx]){
                            cityDistPeso[idx] = val;
                        }
                    }
                }
            }
        }
    }

}