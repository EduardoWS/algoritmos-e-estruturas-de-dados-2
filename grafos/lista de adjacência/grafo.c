#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

Grafo* cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado) {
    Grafo *gr = (Grafo*)malloc(sizeof(Grafo));
    if (gr != NULL) {
        int i;
        gr->nro_vertices = nro_vertices;
        gr->grau_max = grau_max;
        gr->eh_ponderado = (eh_ponderado != 0) ? 1 : 0;
        gr->grau = (int*)calloc(nro_vertices, sizeof(int));
        gr->arestas = (int**)malloc(nro_vertices * sizeof(int*));
        for (i = 0; i < nro_vertices; i++)
            gr->arestas[i] = (int*)malloc(grau_max * sizeof(int));
        if (gr->eh_ponderado) {
            gr->pesos = (float**)malloc(nro_vertices * sizeof(float*));
            for (i = 0; i < nro_vertices; i++)
                gr->pesos[i] = (float*)malloc(grau_max * sizeof(float));
        }
    }
    return gr;
}

void libera_Grafo(Grafo* gr) {
    if (gr != NULL) {
        int i;
        for (i = 0; i < gr->nro_vertices; i++)
            free(gr->arestas[i]);
        free(gr->arestas);
        if (gr->eh_ponderado) {
            for (i = 0; i < gr->nro_vertices; i++)
                free(gr->pesos[i]);
            free(gr->pesos);
        }
        free(gr->grau);
        free(gr);
    }
}

int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso) {
    if (gr == NULL)
        return 0;
    if (orig < 0 || orig >= gr->nro_vertices)
        return 0;
    if (dest < 0 || dest >= gr->nro_vertices)
        return 0;
    gr->arestas[orig][gr->grau[orig]] = dest;
    if (gr->eh_ponderado)
        gr->pesos[orig][gr->grau[orig]] = peso;
    gr->grau[orig]++;
    if (eh_digrafo == 0)
        insereAresta(gr, dest, orig, 1, peso);
    return 1;
}

int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo) {
    if (gr == NULL)
        return 0;
    if (orig < 0 || orig >= gr->nro_vertices)
        return 0;
    if (dest < 0 || dest >= gr->nro_vertices)
        return 0;
    int i = 0;
    while (i < gr->grau[orig] && gr->arestas[orig][i] != dest)
        i++;
    if (i == gr->grau[orig])
        return 0;
    gr->grau[orig]--;
    gr->arestas[orig][i] = gr->arestas[orig][gr->grau[orig]];
    if (gr->eh_ponderado)
        gr->pesos[orig][i] = gr->pesos[orig][gr->grau[orig]];
    if (eh_digrafo == 0)
        removeAresta(gr, dest, orig, 1);
    return 1;
}

void buscaProfundidade(Grafo* gr, int ini, int* visitado){
    int i;
    visitado[ini] = 1;
    printf("%d ", ini);
    for (i = 0; i < gr->grau[ini]; i++)
        if (!visitado[gr->arestas[ini][i]])
            buscaProfundidade(gr, gr->arestas[ini][i], visitado);
}

void buscaLargura(Grafo* gr, int ini, int* visitado){
    int i, vert, NV, *fila, IF = 0, FF = 0;
    for (i = 0; i < gr->nro_vertices; i++)
        visitado[i] = 0;
    NV = gr->nro_vertices;
    fila = (int*)malloc(NV * sizeof(int));
    FF++;
    fila[FF] = ini;
    visitado[ini] = 1;
    while (IF != FF) {
        IF = (IF + 1) % NV;
        vert = fila[IF];
        printf("%d ", vert);
        for (i = 0; i < gr->grau[vert]; i++) {
            if (!visitado[gr->arestas[vert][i]]) {
                FF = (FF + 1) % NV;
                fila[FF] = gr->arestas[vert][i];
                visitado[gr->arestas[vert][i]] = 1;
            }
        }
    }
    free(fila);
}

void menorCaminho(Grafo* gr, int ini, int* ant, float* dist){
    int i, cont, NV, ind, *visitado, u;
    cont = NV = gr->nro_vertices;
    visitado = (int*)malloc(NV * sizeof(int));
    for (i = 0; i < NV; i++) {
        ant[i] = -1;
        dist[i] = -1;
        visitado[i] = 0;
    }
    dist[ini] = 0;
    while (cont > 0) {
        u = procuraMenorDistancia(dist, visitado, NV);
        if (u == -1)
            break;
        visitado[u] = 1;
        cont--;
        for (i = 0; i < gr->grau[u]; i++) {
            ind = gr->arestas[u][i];
            if (dist[ind] < 0) {
                dist[ind] = dist[u] + 1;
                ant[ind] = u;
            } else {
                if (dist[ind] > dist[u] + 1) {
                    dist[ind] = dist[u] + 1;
                    ant[ind] = u;
                }
            }
        }
    }
    free(visitado);
}

int procuraMenorDistancia(float* dist, int* visitado, int NV){
    int i, menor = -1, primeiro = 1;
    for (i = 0; i < NV; i++)
        if (dist[i] >= 0 && visitado[i] == 0) {
            if (primeiro) {
                menor = i;
                primeiro = 0;
            } else {
                if (dist[menor] > dist[i])
                    menor = i;
            }
        }
    return menor;

}

void imprime_Grafo(Grafo* gr){
    int i, j;
    for (i = 0; i < gr->nro_vertices; i++) {
        printf("%d: ", i);
        for (j = 0; j < gr->grau[i]; j++) {
            if (gr->eh_ponderado)
                printf("%d(%.2f), ", gr->arestas[i][j], gr->pesos[i][j]);
            else
                printf("%d, ", gr->arestas[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Grafo *gr;
    gr = cria_Grafo(5, 5, 0);
    insereAresta(gr, 0, 1, 0, 0);
    insereAresta(gr, 1, 3, 0, 0);
    insereAresta(gr, 1, 2, 0, 0);
    insereAresta(gr, 2, 4, 0, 0);
    insereAresta(gr, 3, 4, 0, 0);
    insereAresta(gr, 3, 0, 0, 0);
    insereAresta(gr, 4, 1, 0, 0);
    int ant[5];
    float dist[5];
    menorCaminho(gr, 0, ant, dist);
    for (int i = 0; i < 5; i++)
        printf("%d: %d, %.2f\n", i, ant[i], dist[i]);
    libera_Grafo(gr);
    return 0;
}