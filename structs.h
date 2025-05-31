#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_POVOS_DEFINIDOS 100

    typedef struct City{
        int peso_soldado;
        int habilidade;
    }City;
    
    typedef struct Cidade {
        int peso;
        int habilidade;
        int id;
        double razao;
    } Cidade;

    typedef struct {
        int **matAdj;
        int rows_columns;
    } MatAdj;

    typedef struct {
        int idCidade;
        int soldadosRecrutados;
    } infosRecrutamento;

    typedef struct {
        infosRecrutamento etapas[MAX_POVOS_DEFINIDOS]; 
        int numEtapas;
        int habilidadeTotal;
        int pesoTotalAtual;
        int distanciaTotalPercorrida;
    } Solucao;

    // Estrutura auxiliar para ordenar povos pela razão habilidade/peso
    typedef struct {
        int idOriginal; 
        double razaoCalculada;
    } Ordenacao;


#endif