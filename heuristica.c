#include "structs.h"
#include "heuristica.h"

MatAdj* criarMatAdj(int n){
    MatAdj *t = (MatAdj*)malloc(sizeof(MatAdj));
    if (t == NULL){
        perror("Failed to allocate memory for MatAdj");
        exit(EXIT_FAILURE);
    }
    t->rows_columns = n;
    t->matAdj = malloc(n * sizeof(int*));
    if (t->matAdj == NULL){
        perror("Failed to allocate memory for matAdj rows");
        free(t);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++){
        t->matAdj[i] = malloc(n * sizeof(int));
        if (t->matAdj[i] == NULL){
            perror("Failed to allocate memory for matAdj columns");
            for(int k=0; k<i; k++){
                free(t->matAdj[k]);
            }
            free(t->matAdj);
            free(t);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < n; j++){
            t->matAdj[i][j] = 0; 
        }
    }
    return t;
}

void lerMatAdj(MatAdj *adjMatrix, FILE *arqEnt, int maxCaminhos){
    int cidadeOrigem, cidadeDestino, pesoCaminho;

    for (int i = 0; i < maxCaminhos; i++){
        if (fscanf(arqEnt, "%d %d %d", &cidadeOrigem, &cidadeDestino, &pesoCaminho) != 3){
            fprintf(stderr, "Error reading path data from file.\n");
            return;
        }

        if (cidadeOrigem >= 1 && cidadeOrigem <= adjMatrix->rows_columns && cidadeDestino >= 1 && cidadeDestino <= adjMatrix->rows_columns){
            adjMatrix->matAdj[cidadeOrigem - 1][cidadeDestino - 1] = pesoCaminho;
            adjMatrix->matAdj[cidadeDestino - 1][cidadeOrigem - 1] = pesoCaminho; // Caminho é bidirecional
        } else {
            fprintf(stderr, "Warning: Invalid city ID in path data: %d, %d\n", cidadeOrigem, cidadeDestino);
        }
    }
}

void freeMatAdj(MatAdj *freeMat) {
    if (freeMat == NULL) return;
    if (freeMat->matAdj != NULL) {
        for (int i = 0; i < freeMat->rows_columns; i++) {
            free(freeMat->matAdj[i]);
        }
        free(freeMat->matAdj);
    }
    free(freeMat);
}

void lerCidades(Cidade vetorCidades[], int maxCidades, FILE *entArq){
    int idCidade, Peso, Habilidade;
    for (int i = 0; i < maxCidades; i++) {
        if (fscanf(entArq, "%d %d %d", &idCidade, &Peso, &Habilidade) != 3) {
            fprintf(stderr, "Error reading city data from file.\n");
            // Considerar tratamento de erro mais robusto.
            return;
        }
        if (idCidade >= 1 && idCidade <= maxCidades) {
            vetorCidades[idCidade - 1].peso = Peso;
            vetorCidades[idCidade - 1].habilidade = Habilidade;
        } else {
             fprintf(stderr, "Warning: Invalid city ID in city data: %d\n", idCidade);
        }
    }
}

int compararRazao(const void *a, const void *b){
    Ordenacao *povoA = (Ordenacao *)a;
    Ordenacao *povoB = (Ordenacao *)b;
    if (povoA->razaoCalculada < povoB->razaoCalculada) return 1;
    if (povoA->razaoCalculada > povoB->razaoCalculada) return -1;

    return 0;
}

void inicializarSolucao(Solucao *s) {
    s->numEtapas = 0;
    s->habilidadeTotal = 0;
    s->pesoTotalAtual = 0;
    s->distanciaTotalPercorrida = 0;
    for (int i = 0; i < MAX_POVOS_DEFINIDOS; i++) {
        s->etapas[i].idCidade = 0;
        s->etapas[i].soldadosRecrutados = 0;
    }
}

Solucao recrutar(Cidade vetorCidades[], int numPovos, MatAdj *mundo, int capacidadeNave, int maxDistancia){

    Solucao solucaoFinal;
    inicializarSolucao(&solucaoFinal); 

    if (numPovos <= 0 || capacidadeNave <= 0){
        return solucaoFinal; 
    }

    Ordenacao *povosParaOrdenar = malloc(numPovos * sizeof(Ordenacao));
    if (povosParaOrdenar == NULL){
        perror("Falha ao alocar memoria para ordenacao de povos");
        return solucaoFinal; 
    }
    int povosValidos = 0;
    for (int i = 0; i < numPovos; i++){
        if (vetorCidades[i].peso > 0){ 
            povosParaOrdenar[povosValidos].idOriginal = i;
            povosParaOrdenar[povosValidos].razaoCalculada = (double)vetorCidades[i].habilidade / vetorCidades[i].peso;
            povosValidos++;
        }
    }

    if (povosValidos == 0){ 
        free(povosParaOrdenar);
        return solucaoFinal;
    }


    qsort(povosParaOrdenar, povosValidos, sizeof(Ordenacao), compararRazao);


    bool *visitado = calloc(numPovos, sizeof(bool)); 
    if (visitado == NULL){
        perror("Falha ao alocar memoria para array de visitados");
        free(povosParaOrdenar);
        return solucaoFinal;
    }

    int povoAtual = -1; 

    for (int i = 0; i < povosValidos; i++){
        if (solucaoFinal.pesoTotalAtual >= capacidadeNave){
            break; 
        }
        if (solucaoFinal.numEtapas >= MAX_POVOS_DEFINIDOS){ 
            break; 
        }

        int idCandidato = povosParaOrdenar[i].idOriginal;  //idCadidato = id do povo candidato a prox recrutamento, não achei nome melhor

        if (visitado[idCandidato]){
            continue;
        }

        int distanciaParaCandidato = 0;
        if (solucaoFinal.numEtapas == 0){
            distanciaParaCandidato = 0;
        } else {
            if (povoAtual == -1){ 
                break; 
            }
            distanciaParaCandidato = mundo->matAdj[povoAtual][idCandidato];
        }

        bool podeViajar = false;
        if (solucaoFinal.numEtapas == 0){ 
             podeViajar = true;
        } else {
            if (distanciaParaCandidato > 0 && 
                (solucaoFinal.distanciaTotalPercorrida + distanciaParaCandidato <= maxDistancia)){
                podeViajar = true;
            }
        }

        if (podeViajar){

            int pesoDisponivel = capacidadeNave - solucaoFinal.pesoTotalAtual;
            int numSoldadosRecrutados = 0;
            int pesoSoldadoAtual = vetorCidades[idCandidato].peso; 
            int habilidadeSoldadoAtual = vetorCidades[idCandidato].habilidade;

            if (pesoDisponivel > 0){ 
                numSoldadosRecrutados = pesoDisponivel / pesoSoldadoAtual;
            }

            if (solucaoFinal.numEtapas > 0){ 
                solucaoFinal.distanciaTotalPercorrida += distanciaParaCandidato;
            }
            
            povoAtual = idCandidato; 
            visitado[idCandidato] = true;

            solucaoFinal.etapas[solucaoFinal.numEtapas].idCidade = idCandidato + 1; 
            solucaoFinal.etapas[solucaoFinal.numEtapas].soldadosRecrutados = numSoldadosRecrutados;
            
            if (numSoldadosRecrutados > 0){ 
                solucaoFinal.pesoTotalAtual += numSoldadosRecrutados * pesoSoldadoAtual;
                solucaoFinal.habilidadeTotal += numSoldadosRecrutados * habilidadeSoldadoAtual;
            }
            solucaoFinal.numEtapas++;

        } else if (solucaoFinal.numEtapas > 0){
            }

    }

    free(povosParaOrdenar);
    free(visitado);
    return solucaoFinal;
}