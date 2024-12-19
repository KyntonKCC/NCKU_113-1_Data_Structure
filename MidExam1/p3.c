#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

#define TRUE 1
#define FALSE 0
#define MALLOC(p, s) \
    if (!((p) = malloc(s))) { \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }
typedef struct edge_s *Edge;
typedef struct edge_s {
    int src;
    int dest;
    int weight;
} edge_t;
typedef struct graph_s *Graph;
typedef struct graph_s {
    int numVertices;
    int numEdges;
    Edge edge;
} graph_t;
typedef struct subset_s *Subset;
typedef struct subset_s {
    int parent;
    int key;
    int visited;
} subset_t;
Graph createAGraph(int, int);
void addEdge(Graph, int, int, int);
int cmp(const void *, const void *);
void printGraph(Graph);
void printSubset(Subset, int);

// Input
void readInput(int *n, int adjacencyMatrix[MAX_N][MAX_N]) {
    int i, j;
    // Read the number of nodes
    scanf("%d", n);
    // Read the adjacency matrix
    for (i = 0; i < *n; i++) {
        for (j = 0; j < *n; j++) {
            scanf("%d", &adjacencyMatrix[i][j]);
        }
    }
}

//  Output
void outputResult(int cost, int edgeCount, int edges[MAX_N][2]) {
    int i;
    // Output total weight
    printf("%d ", cost);

    // Output edges
    for (i = 0; i < edgeCount; i++) {
        printf("(%d,%d) ", edges[i][0], edges[i][1]);
    }
    printf("\n");
}

/*
4
0 5 0 10
5 0 15 20
0 15 0 25
10 20 25 0

7
0 28 0 0 0 10 0
28 0 16 0 0 0 14
0 16 0 12 0 0 0
0 0 12 0 22 0 18
0 0 0 22 0 25 24
10 0 0 0 25 0 0
0 14 0 18 24 0 0
*/

int main() {
    int n;
    int adjacencyMatrix[MAX_N][MAX_N];
    int edges[MAX_N][2];     // Stores the selected edges
    int edgeCount = 0;
    int cost = 0;

    readInput(&n, adjacencyMatrix);

    //Here is your code
    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++)
            if(adjacencyMatrix[i][j] != 0)
                edgeCount++;
    Graph graph = createAGraph(n, edgeCount);
    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++)
            if(adjacencyMatrix[i][j] != 0)
                addEdge(graph, i, j, adjacencyMatrix[i][j]);
    int start = 0;
    int V = graph->numVertices;
    int E = graph->numEdges;
    Edge result;
    MALLOC(result, (V - 1) * sizeof(*result));
    Subset subset;
    MALLOC(subset, V * sizeof(*subset));
    for(int i = 0; i < V; i++){
        subset[i].parent = -1;
        subset[i].key = 0;
        subset[i].visited = FALSE;
    }
    subset[start].key = __INT32_MAX__;
    subset[start].visited = TRUE;
    // printGraph(graph);
    // printSubset(subset, V);
    int check = 0;
    while(check < V - 1){
        // printf("--> (%d %d)\n", check, start);
        for(int i = 0 ; i < E; i++)
            if(graph->edge[i].src == start && graph->edge[i].weight > subset[graph->edge[i].dest].key && subset[graph->edge[i].dest].visited == FALSE){
                subset[graph->edge[i].dest].parent = graph->edge[i].src;
                subset[graph->edge[i].dest].key = graph->edge[i].weight;
            }else if(graph->edge[i].dest == start && graph->edge[i].weight > subset[graph->edge[i].src].key && subset[graph->edge[i].src].visited == FALSE){
                subset[graph->edge[i].src].parent = graph->edge[i].dest;
                subset[graph->edge[i].src].key = graph->edge[i].weight;
            }
        // printSubset(subset, V);
        int max = 0;
        for(int i = 0; i < V; i++)
            if(subset[i].visited == FALSE && subset[i].key > max){
                max = subset[i].key;
                start = i;
            }
        if(start < subset[start].parent){
            result[check].src = start;
            result[check].dest = subset[start].parent;
        }else if(start > subset[start].parent){
            result[check].src = subset[start].parent;
            result[check].dest = start;
        }
        subset[start].visited = TRUE;
        result[check].weight = subset[start].key;
        cost += result[check].weight;
        check++;
        // printSubset(subset, V);
    }
    // for(int i = 0; i < V - 1; i++)
    //     printf("%d %d -> %d\n", result[i].src, result[i].dest, result[i].weight);
    qsort(result, V - 1, sizeof(*result), cmp);
    // for(int i = 0; i < V - 1; i++)
    //     printf("%d %d -> %d\n", result[i].src, result[i].dest, result[i].weight);
    edgeCount = n - 1;
    for(int i = 0; i < edgeCount; i++){
        edges[i][0] = result[i].src;
        edges[i][1] = result[i].dest;
    }
    //Here is your code

    outputResult(cost, edgeCount, edges);

    return 0;
}

Graph createAGraph(int v, int e) {
    Graph graph;
    MALLOC(graph, sizeof(*graph));
    graph->numVertices = v;
    graph->numEdges = e;
    MALLOC(graph->edge, e * sizeof(*graph->edge));
    return graph;
}

void addEdge(Graph graph, int s, int d, int w) {
    static int count = 0;
    graph->edge[count].src = s;
    graph->edge[count].dest = d;
    graph->edge[count].weight = w;
    count++;
}

int cmp(const void *a, const void *b){
    return ((Edge)b)->weight - ((Edge)a)->weight;
}

void printGraph(Graph graph) {
    for (int i = 0; i < graph->numEdges; i++) 
        printf("%d %d %d\n", graph->edge[i].src, graph->edge[i].dest, graph->edge[i].weight);
    printf("--------------------\n");
}

void printSubset(Subset s, int v){
    for(int i = 0; i < v; i++)
        printf("%2d ", i);
    printf("\n");
    for(int i = 0; i < v; i++)
        printf("%2d ", (s+i)->parent);
    printf("\n");
    for(int i = 0; i < v; i++)
        if(i == 0)
            printf(" X ");
        else
            printf("%2d ", (s+i)->key);
    printf("\n");
    for(int i = 0; i < v; i++)
        printf("%2d ", (s+i)->visited);
    printf("\n");
    printf("--------------------\n");
}