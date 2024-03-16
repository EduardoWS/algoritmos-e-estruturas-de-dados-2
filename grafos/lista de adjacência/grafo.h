#ifndef GRAFO_H
#define GRAFO_H

typedef struct grafo Grafo;

struct grafo {
    int eh_ponderado;
    int nro_vertices;
    int grau_max;
    int** arestas;
    float** pesos;
    int* grau;
};

Grafo* cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado);

void libera_Grafo(Grafo* gr);

int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso);

int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo);

void buscaProfundidade(Grafo* gr, int ini, int* visitado);

void buscaLargura(Grafo* gr, int ini, int* visitado);

void menorCaminho(Grafo* gr, int ini, int* ant, float* dist);

int procuraMenorDistancia(float* dist, int* visitado, int NV);

void imprime_Grafo(Grafo* gr);



#endif // GRAFO_H