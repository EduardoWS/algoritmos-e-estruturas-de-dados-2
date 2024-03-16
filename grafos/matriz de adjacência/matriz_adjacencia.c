#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct {
    int numVertices;
    int matrizAdj[MAX_VERTICES][MAX_VERTICES];
} Graph;

// Inicializa o grafo com o número de vértices e zera a matriz de adjacência
Graph initGraph(int numVertices) {
    Graph g;
    g.numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            g.matrizAdj[i][j] = 0;
        }
    }
    return g;
}

// Insere um arco no grafo
void insertArc(Graph *g, int origem, int destino) {
    if (origem >= 0 && origem < g->numVertices && destino >= 0 && destino < g->numVertices) {
        g->matrizAdj[origem][destino] = 1;
    }
}

// Remove um arco do grafo
void removeArc(Graph *g, int origem, int destino) {
    if (origem >= 0 && origem < g->numVertices && destino >= 0 && destino < g->numVertices) {
        g->matrizAdj[origem][destino] = 0;
    }
}

// Imprime o grafo
void printGraph(Graph g) {
    for (int i = 0; i < g.numVertices; i++) {
        for (int j = 0; j < g.numVertices; j++) {
            printf("%d ", g.matrizAdj[i][j]);
        }
        printf("\n");
    }
}

// Liberar recursos do grafo (neste caso, não é estritamente necessário pois estamos usando alocação estática)
void destroyGraph(Graph *g) {
    // Como estamos usando uma matriz estática, não há alocação dinâmica a ser liberada.
    // Esta função está aqui para fins de completude e futura expansão.
}

int main() {
    int numVertices;
    FILE *file = fopen("grafo.txt", "r");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fscanf(file, "%d", &numVertices);
    Graph g = initGraph(numVertices);

    int origem, destino;
    while (fscanf(file, "%d %d", &origem, &destino) != EOF) {
        insertArc(&g, origem, destino);
    }

    printGraph(g);
    fclose(file);
    return 0;
}