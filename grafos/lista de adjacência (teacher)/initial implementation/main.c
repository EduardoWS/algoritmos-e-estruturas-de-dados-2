#include "adjlist.h"
#include <stdio.h>

int main(void) {
  int n, i, x, y;
  Graph G;
  if (scanf("%d\n", &n) == 1) {
    G = initGraph(n);
    while (scanf("%d %d\n", &x, &y) != EOF) {
      insertEdge(G, x, y);
    }
  }
  printf("printGraph\n");
  printGraph(G);
  printf("printGraph after remove\n");
  removeEgde(G, 5, 2);
  printGraph(G);
  return 0;
}