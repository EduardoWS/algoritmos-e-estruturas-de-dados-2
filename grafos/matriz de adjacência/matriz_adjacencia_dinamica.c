#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int numVertices;
    int **matrizAdj; // Matriz de adjacência como um ponteiro para ponteiro
} Graph;

// Função para alocar a matriz de adjacência dinamicamente
int **alocaMatrizAdj(int numVertices) {
    int **matriz = (int **)malloc(numVertices * sizeof(int *));
    for (int i = 0; i < numVertices; i++) {
        matriz[i] = (int *)malloc(numVertices * sizeof(int));
        for (int j = 0; j < numVertices; j++) {
            matriz[i][j] = 0; // Inicializa a matriz com 0
        }
    }
    return matriz;
}

// Inicializa o grafo com o número de vértices e aloca a matriz de adjacência dinamicamente
Graph initGraph(int numVertices) {
    Graph g;
    g.numVertices = numVertices;
    g.matrizAdj = alocaMatrizAdj(numVertices);
    return g;
}

// Insere um arco no grafo
void insertArc(Graph *g, int origem, int destino) {
    if (origem >= 0 && origem < g->numVertices && destino >= 0 && destino < g->numVertices) {
        g->matrizAdj[origem][destino] = 1;
        g->matrizAdj[destino][origem] = 1; // Grafo não direcionado
    }
}

// Remove um arco do grafo
void removeArc(Graph *g, int origem, int destino) {
    if (origem >= 0 && origem < g->numVertices && destino >= 0 && destino < g->numVertices) {
        g->matrizAdj[origem][destino] = 0;
        g->matrizAdj[destino][origem] = 0; // Grafo não direcionado
    }
}


void printGraph(Graph g) {
    int totalArcs = 0;
    for (int i = 0; i < g.numVertices; i++) {
        for (int j = 0; j < g.numVertices; j++) {
            totalArcs += g.matrizAdj[i][j];
        }
    }
    printf("Total of vertices: %d, total of arcs: %d\n", g.numVertices, totalArcs/2);

    for (int i = 0; i < g.numVertices; i++) {
        printf("Vertex %d, arcs: ", i);
        int first = 1;
        // Imprime arcos de entrada
        for (int j = 0; j < g.numVertices; j++) {
            if (g.matrizAdj[j][i] && !g.matrizAdj[i][j]) { // Evita duplicatas
                if (!first) printf(", ");
                printf("%d", j);
                first = 0;
            }
        }
        // Imprime arcos de saída
        for (int j = 0; j < g.numVertices; j++) {
            if (g.matrizAdj[i][j]) {
                if (!first) printf(", ");
                printf("%d", j);
                first = 0;
            }
        }
        printf("\n");
    }
}

// Libera a matriz de adjacência e o grafo
void destroyGraph(Graph *g) {
    for (int i = 0; i < g->numVertices; i++) {
        free(g->matrizAdj[i]); // Libera cada linha da matriz
    }
    free(g->matrizAdj); // Libera o vetor de ponteiros
    g->matrizAdj = NULL; // Evita dangling pointers
}

int main() {
    int n, x, y;
    Graph G;
    if (scanf("%d\n", &n) == 1) {
        G = initGraph(n);
        while (scanf("%d %d\n", &x, &y) != EOF) {
            // printf("Inserindo arco: %d -> %d\n", x, y);
            insertArc(&G, x, y);
        }
    }

    printGraph(G);
    destroyGraph(&G);
    return 0;
}

// int main() {
//     int numVertices;
//     FILE *file = fopen("./grafo.txt", "r");
//     if (!file) {
//         printf("Erro ao abrir o arquivo.\n");
//         return 1;
//     }

//     fscanf(file, "%d", &numVertices);
//     Graph g = initGraph(numVertices);

//     int origem, destino;
//     while (fscanf(file, "%d %d", &origem, &destino) != EOF) {
//         printf("Inserindo arco: %d -> %d\n", origem, destino);
//         insertArc(&g, origem, destino);
//     }

//     printGraph(g);
//     destroyGraph(&g);
//     fclose(file);
//     return 0;
// }