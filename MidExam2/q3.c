#include <stdio.h>
#include <stdlib.h>
#define MAX_N 20

#define MALLOC(p, s)\
    if(!((p) = malloc(s))){\
        printf("Fail\n");\
        exit(EXIT_FAILURE);\
    }
typedef struct edge_s *Edge;
typedef struct edge_s{
    int src;
    int dest;
}edge_t;
typedef struct graph_s *Graph;
typedef struct graph_s{
    int numVertices;
    int numEdges;
    Edge edge;
}graph_t;
// typedef struct subset_s *Subset;
// typedef struct subset_s{
//     int parent;
//     int rank;
// }subset_t;
Graph createGraph(int, int);
void addEdge(Graph, int, int);

//20/40
/*
4
0 1 1 1
1 0 1 1
1 1 0 0
1 1 0 0

3
0 1 1
1 0 0
1 0 0
*/

int main(void) {
    // Input
    int n;
    int cycle_x = -1, cycle_y = -1;     // The edge (x, y) used to determine whether there is a cycle, x < y
    int has_cycle = 0;      // Used to determine whether there is a cycle
    
    // Read the number of nodes
    scanf("%d", &n);

    int graph[n][n];
    
    // Read adjacency matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    int ways = 0;
    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++)
            if(graph[i][j] != 0)
                ways++;
    Graph G;
    G = createGraph(n, ways);
    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++)
            if(graph[i][j] != 0)
                addEdge(G, i, j);
    
    for(int i = 0; i < G->numEdges; i++){
        cycle_x = G->edge[i].src;
        cycle_y = G->edge[i].dest;
    }

    // Output
    if(has_cycle) {
        printf("True,(%d,%d)\n", cycle_x, cycle_y);
    } else {
        printf("False,(%d,%d)\n", cycle_x, cycle_y);
    }
    
    
    return 0;
}

Graph createGraph(int v, int e){
    Graph graph;
    MALLOC(graph, sizeof(*graph));
    graph->numVertices = v;
    graph->numEdges = e;
    MALLOC(graph->edge, e * sizeof(*graph->edge));
    return graph;
}

void addEdge(Graph graph, int s, int d){
    static int count = 0;
    graph->edge[count].src = s;
    graph->edge[count].dest = d;
    count++;
}