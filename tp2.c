#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cidade {
    int peso;
    int Hability;
} Cidade;

typedef struct {
    int **matAdj;
    int rows_columns;
} MatAdj;

MatAdj* criarMatAdj(int n);
void lerMatAdj(MatAdj *t, FILE *file, int maxCaminhos);
void freeMatAdj(MatAdj *t);
void lerCidades(Cidade vetorCidades[], int maxCidades, FILE *entArq);

MatAdj* criarMatAdj(int n) {
    MatAdj *t = (MatAdj*)malloc(sizeof(MatAdj));
    if (t == NULL) {
        perror("Failed to allocate memory for MatAdj");
        exit(EXIT_FAILURE);
    }
    t->rows_columns = n;
    t->matAdj = malloc(n * sizeof(int*));
    if (t->matAdj == NULL) {
        perror("Failed to allocate memory for matAdj rows");
        free(t);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        // CORREÇÃO: Alocar espaço para 'n' inteiros, não 'n' ponteiros de inteiro.
        t->matAdj[i] = malloc(n * sizeof(int));
        if (t->matAdj[i] == NULL) {
            perror("Failed to allocate memory for matAdj columns");
            // Liberar memória já alocada em caso de falha
            for(int k=0; k<i; k++){
                free(t->matAdj[k]);
            }
            free(t->matAdj);
            free(t);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < n; j++) {
            t->matAdj[i][j] = 0; // Inicializa com 0 (sem caminho)
        }
    }
    return t;
}

void lerMatAdj(MatAdj *adjMatrix, FILE *arqEnt, int maxCaminhos) {
    int cidadeOrigem, cidadeDestino, pesoCaminho;

    for (int i = 0; i < maxCaminhos; i++) {
        if (fscanf(arqEnt, "%d %d %d", &cidadeOrigem, &cidadeDestino, &pesoCaminho) != 3) {
            fprintf(stderr, "Error reading path data from file.\n");
            // Considerar tratamento de erro mais robusto, como liberar memória e sair.
            return;
        }
        // CORREÇÃO: Ajustar para 0-indexed, pois os IDs no arquivo são 1-indexed.
        // Adicionar verificação de limites para segurança.
        if (cidadeOrigem >= 1 && cidadeOrigem <= adjMatrix->rows_columns &&
            cidadeDestino >= 1 && cidadeDestino <= adjMatrix->rows_columns) {
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

void lerCidades(Cidade vetorCidades[], int maxCidades, FILE *entArq) {
    int idCidade, Peso, Habilidade;
    for (int i = 0; i < maxCidades; i++) {
        if (fscanf(entArq, "%d %d %d", &idCidade, &Peso, &Habilidade) != 3) {
            fprintf(stderr, "Error reading city data from file.\n");
            // Considerar tratamento de erro mais robusto.
            return;
        }
        // CORREÇÃO: Ajustar para 0-indexed. O ID da cidade no arquivo (idCidade) é 1-indexed.
        // Adicionar verificação de limites para segurança.
        if (idCidade >= 1 && idCidade <= maxCidades) {
            vetorCidades[idCidade - 1].peso = Peso;
            vetorCidades[idCidade - 1].Hability = Habilidade;
        } else {
             fprintf(stderr, "Warning: Invalid city ID in city data: %d\n", idCidade);
        }
    }
}

int main() {
    int instancias = 0, maxCidades = 0, maxDist = 0, maxPeso = 0, maxCaminhos = 0;
    FILE *arq = fopen("entrada.txt", "r");
    if (arq == NULL) {
        perror("Failed to open entrada.txt");
        return EXIT_FAILURE;
    }

    if (fscanf(arq, "%d", &instancias) != 1) {
        fprintf(stderr, "Error reading number of instances.\n");
        fclose(arq);
        return EXIT_FAILURE;
    }

    while (instancias > 0) {
        if (fscanf(arq, "%d %d %d %d", &maxCidades, &maxDist, &maxPeso, &maxCaminhos) != 4) {
            fprintf(stderr, "Error reading instance parameters.\n");
            // Se uma instância não puder ser lida, pode ser melhor parar.
            break; 
        }

        if (maxCidades <= 0) { // Adicionado para evitar alocação de tamanho zero/negativo
            fprintf(stderr, "Invalid number of cities: %d\n", maxCidades);
            instancias--;
            continue; 
        }

        Cidade *povos = malloc(maxCidades * sizeof(Cidade));
        if (povos == NULL) {
            perror("Failed to allocate memory for povos");
            // Se a alocação falhar, pode ser melhor parar.
            break;
        }
        lerCidades(povos, maxCidades, arq);

        MatAdj *mundoZambis = criarMatAdj(maxCidades);
        lerMatAdj(mundoZambis, arq, maxCaminhos);

        // Aqui você adicionaria a lógica do problema usando 'povos' e 'mundoZambis'.
        // Por exemplo, imprimir os dados lidos para verificar:
        
        printf("Instance Data:\n");
        printf("MaxCities: %d, MaxDist: %d, maxPeso: %d, maxCaminhos: %d\n", maxCidades, maxDist, maxPeso, maxCaminhos);
        for (int i = 0; i < maxCidades; i++) {
            printf("City %d (file ID %d): Peso %d, Hability %d\n", i, i + 1, povos[i].peso, povos[i].Hability);
        }
        printf("Adjacency Matrix:\n");
        for (int i = 0; i < maxCidades; i++) {
            for (int j = 0; j < maxCidades; j++) {
                printf("%d ", mundoZambis->matAdj[i][j]);
            }
            printf("\n");
        }
        printf("-----------------------------------\n");
        

        freeMatAdj(mundoZambis);
        free(povos); // Não se esqueça de liberar 'povos'

        // Resetar variáveis não é estritamente necessário aqui, pois são lidas novamente no início do loop.
        // maxCidades=0, maxDist=0, maxPeso=0, maxCaminhos=0; 
        instancias--;
    }

    fclose(arq);
    return 0;
}