#include "matriz_adj.hpp"
#include "fila.hpp"

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
    // Alocação de memória para o vetor visited
    g.visited = (int *)malloc(numVertices * sizeof(int));
    
    return g;
}

// Insere um arco no grafo
void insertArc(Graph *g, int origem, int destino, int peso) {
    if (origem >= 0 && origem < g->numVertices && destino >= 0 && destino < g->numVertices) {
        g->matrizAdj[origem][destino] = peso;
        // g->matrizAdj[destino][origem] = 1; // Grafo não direcionado
    }
}

// Remove um arco do grafo
void removeArc(Graph *g, int origem, int destino) {
    if (origem >= 0 && origem < g->numVertices && destino >= 0 && destino < g->numVertices) {
        g->matrizAdj[origem][destino] = 0;
        // g->matrizAdj[destino][origem] = 0; // Grafo não direcionado
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
    free(g->visited); // Libera o vetor visited
    g->matrizAdj = NULL; 
    g->visited = NULL; // Boa prática para evitar dangling pointers
}



void BFS(Graph *g, int v){
    t_fila f;
    inicializar(&f);
    g->visited[v] = 1; // Marque como visitado ao enfileirar
    enfileirar(v, &f);

    while (!vazia(&f)){
        int atual = desenfileirar(&f);
        printf("visited %d\n", atual);

        for (int i = 0; i < g->numVertices; i++) {
            if (g->matrizAdj[atual][i] && !g->visited[i]) {
                g->visited[i] = 1; // Marque como visitado ao enfileirar
                enfileirar(i, &f);
            }
        }
    }
}

void DFS(Graph *g, int v){
    g->visited[v] = 1;
    printf("visited %d\n", v);

    // Recursão para todos os vértices adjacentes não visitados
    for (int i = 0; i < g->numVertices; i++) {
        if (g->matrizAdj[v][i] && !g->visited[i]) {
            DFS(g, i);
        }
    }
}

void clearVisited(Graph *g){
    // Inicialização do vetor visited com 0
    for (int i = 0; i < g->numVertices; i++) {
        g->visited[i] = 0;
    }
}

void startDFS(Graph *G, int v) {
    clearVisited(G);
    printf("DFS\n");
    DFS(G, v);
}

void startBFS(Graph *G, int v) {
    clearVisited(G);
    printf("BFS\n");
    BFS(G, v);
}

void dijkstra(Graph *g, int src, int *dist, int *prev) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int i = 0; i < g->numVertices; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }

    dist[src] = 0;
    pq.push(make_pair(0, src));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int v = 0; v < g->numVertices; v++) {
            if (g->matrizAdj[u][v] != 0) {  // Aresta existe
                int weight = g->matrizAdj[u][v];
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
    }
}


void allPairsShortestPath(Graph *g) {
    int v = g->numVertices;
    int *dist = (int *)malloc(v * sizeof(int));
    int *prev = (int *)malloc(v * sizeof(int));

    for (int i = 0; i < v; i++) {
        dijkstra(g, i, dist, prev);
        printf("Node %d:\n", i);
        for (int j = 0; j < v; j++) {
            if (dist[j] == INT_MAX) {
                printf("Distance from %d to %d = infinity\n", i, j);
            } else {
                printf("Distance from %d to %d = %d\n", i, j, dist[j]);
                if (dist[j] != 0) {
                    printf("Path: ");
                    vector<int> path;
                    for (int at = j; at != -1; at = prev[at]) {
                        path.push_back(at);
                    }
                    for (int k = path.size() - 1; k >= 0; k--) {
                        printf("%d", path[k]);
                        if (k > 0) printf(" -> ");
                    }
                    printf("\n");
                }
            }
        }
        if (i < v - 1) printf("\n"); // Adiciona uma linha em branco entre as saídas de cada nó
    }

    free(dist);
    free(prev);
}

int main() {
    int n, x, y, peso;
    Graph G;
    if (scanf("%d\n", &n) == 1) {
        G = initGraph(n);
        while (scanf("%d %d %d\n", &x, &y, &peso) != EOF) {
            // printf("Inserindo arco: %d -> %d\n", x, y);
            insertArc(&G, x, y, peso);
        }
    }

    // printGraph(G);
    // startDFS(&G, 0);
    // startBFS(&G, 0);

    allPairsShortestPath(&G);

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
//     int peso;
//     while (fscanf(file, "%d %d %d", &origem, &destino, &peso) != EOF) {
//         insertArc(&g, origem, destino, peso);
//     }

//     allPairsShortestPath(&g);

//     // printGraph(g);
//     // startDFS(&g, 0);
//     // startBFS(&g, 0);


//     destroyGraph(&g);
//     fclose(file);
//     return 0;
// }

