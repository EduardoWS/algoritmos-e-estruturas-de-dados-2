#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

typedef struct { 
    int v;
    int w; 
} Edge;

Edge EDGE(int, int);

typedef struct graph *Graph; 

Graph GRAPHinit (int);
void GRAPHinsertE (Graph, Edge);
void GRAPHremoveE (Graph, Edge); 
int GRAPHedges (Edge [], Graph G);
Graph GRAPHcopy (Graph);
void GRAPHdestroy (Graph);


#endif // GRAPH_H