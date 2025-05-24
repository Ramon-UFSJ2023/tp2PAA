#include "progMod.h"
int maximo(int a, int b){return a>b ? a : b;}
#define INACESSIVEL (INT_MIN/2)

void functionProgMod(City *povos, MatAdj *cidadePovosDist, int maxPeso, int max_Dist, int* habilidadeMaxima, int *melhorCaminho){
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
    for(int cidades =0; cidades<cidadePovosDist->rows_columns;cidades++) tabelaDinamica[cidades][0][0];

    
}