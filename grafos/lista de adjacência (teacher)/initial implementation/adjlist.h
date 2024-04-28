#include <stdio.h>
#include <stdlib.h>

#define Vertex int
typedef struct node *Link;
typedef struct graph *Digraph;
#define Graph Digraph

struct node {
  Vertex w;
  Link next;
  int weight;
};

struct graph {
  int V;
  int A;
  Link *adj;
};

Graph initGraph(int n) {
  Graph G = (Graph)malloc(sizeof(*G));
  G->V = n;
  G->A = 0;
  G->adj = (Link *)malloc(n * sizeof(Link));
  for (int i; i < n; i++) {
    G->adj[i] = NULL;
  }
  return G;
}

void destroyGraph(Graph G) {
  if (G != NULL) {
    for (int i; i < G->V; i++) {
      free(G->adj[i]);
    }
    free(G->adj);
    free(G);
  }
}

Link newArc(Vertex w, Link next) {
  Link anode = (Link)malloc(sizeof(*anode));
  anode->w = w;
  anode->next = next;
  return anode;
}

void insertArc(Graph G, Vertex v, Vertex w) {
  // verificar se o arco jah existe
  for (Link a = G->adj[v]; a != NULL; a = a->next) {
    if (a->w == w) {
      return;
    }
  }
  G->adj[v] = newArc(w, G->adj[v]);
  G->A++;
}

void insertEdge(Graph G, Vertex v, Vertex w) {
  insertArc(G, v, w);
  insertArc(G, w, v);
}

void removeArc(Graph G, Vertex v, Vertex w) {
  if (v > G->V) {
    return;
  }
  Link prev = G->adj[v];
  for (Link p = G->adj[v]; p != NULL; p = p->next) {
    if (p->w == w) {
      G->A--;
      if (G->adj[v] == p) {
        G->adj[v] = p->next;
      } else {
        prev->next = p->next;
      }
      free(p);
      return;
    } else {
      prev = p;
    }
  }
}

void removeEgde(Graph G, Vertex v, Vertex w) {
  removeArc(G, v, w);
  removeArc(G, w, v);
}

void printGraph(Graph G) {
  printf("Graph, %d vertex and %d arcs\n", G->V, G->A);
  for (int i = 0; i < G->V; i++) {
    printf("Vertex %d: ", i);
    for (Link p = G->adj[i]; p != NULL; p = p->next) {
      printf(" %d > %d / ", i, p->w);
    }
    printf("\n");
  }
}