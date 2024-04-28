#ifndef MATRIZ_ADJ_HPP
#define MATRIZ_ADJ_HPP

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <vector>
#include "fila.hpp"

using namespace std;

typedef struct {
    int numVertices;
    int *visited; // Vetor para marcar vértices visitados
    int **matrizAdj; // Matriz de adjacência como um ponteiro para ponteiro
} Graph;


int **alocaMatrizAdj(int numVertices);

Graph initGraph(int numVertices);

void insertArc(Graph *g, int origem, int destino);

void removeArc(Graph *g, int origem, int destino);

void printGraph(Graph g);

void destroyGraph(Graph *g);

void BFS(Graph *g, int origem);

void clearVisited(Graph *g);

void DFS(Graph *g, int origem);

void startDFS(Graph *g, int v);




#endif