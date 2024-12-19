#include <stdio.h> 
#include <stdlib.h>
#define MAX_NODES 20

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define MALLOC(p, s)\
    if(!((p) = malloc(s))){\
        printf("Fail\n");\
        exit(EXIT_FAILURE);\
    }
typedef struct edge_s *Edge;
typedef struct edge_s{
    int src;
    int dest;
    int weight;
}edge_t;
typedef struct graph_s *Graph;
typedef struct graph_s{
    int numVertices;
    int numEdges;
    Edge edge;
}graph_t;
typedef struct subset_s *Subset;
typedef struct subset_s{
    int parent;
    int rank;
}subset_t;
Graph createGraph(int, int);
void addEdge(Graph, int, int, int);
int cmp(const void *, const void *);
int find(Subset, int);

//18/30
/*
4
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0

6
0 3 0 0 6 5
3 0 1 0 0 4
0 1 0 6 0 0
0 0 6 0 8 7
6 0 0 8 0 2
5 4 0 7 2 0
*/

int main(void) {
    // Input
    int n;
    scanf("%d", &n);  // Read the number of nodes
    
    // Read adjacency matrix
    int matrix[MAX_NODES][MAX_NODES];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }


    int totalCost = 0;      // Storing the total cost of the minimum spanning tree
    int mst[MAX_NODES][2];  // Store the edges of the minimum spanning tree. 
                            // If the i-th edge is (u, v), then mst[i-1][0] = u,mst[i-1][1] = v
    

    int ways = 0;
    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++)
            if(matrix[i][j] != 0)
                ways++;
    Graph graph;
    graph = createGraph(n, ways);
    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++)
            if(matrix[i][j] != 0)
                addEdge(graph, i, j, matrix[i][j]);

    int V = graph->numVertices;
    Edge results;
    MALLOC(results, (V - 1) * sizeof(*results));
    Subset subset;
    MALLOC(subset, V * sizeof(*subset));
    for(int i = 0; i < V; i++){
        subset[i].parent = -1;
        subset[i].rank = 0;
    }
    qsort(graph->edge, graph->numEdges, sizeof(graph->edge[0]), cmp);
    int j = 0, k = 0, t = 0;
    while(j < V - 1){
        int x = find(subset, graph->edge[k].src);
        int y = find(subset, graph->edge[k].dest);
        if(x != y){
            if(x > y)
                SWAP(x, y, t);
            if(subset[x].rank < subset[y].rank){
                subset[x].parent = y;
            }else if(subset[x].rank > subset[y].rank){
                subset[y].parent = x;
            }else{
                subset[x].parent = y;
                subset[y].rank += 1;
            }
            results[j].src = graph->edge[k].src;
            results[j].dest = graph->edge[k].dest;
            results[j].weight = graph->edge[k].weight;
            mst[j][0] = results[j].src;
            mst[j][1] = results[j].dest;
            totalCost += results[j].weight;
            j++;
        }
        k++;
    }


    // OutPut
    printf("%d", totalCost);
    for (int i = 0; i < n-1; i++) {
        printf(",(%d,%d)", mst[i][0], mst[i][1]);  
    }
    printf("\n");
    
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

void addEdge(Graph graph, int s, int d, int w){
    static int count = 0;
    graph->edge[count].src = s;
    graph->edge[count].dest = d;
    graph->edge[count].weight = w;
    count++;
}

int cmp(const void *a, const void *b){
    return ((Edge)a)->weight - ((Edge)b)->weight;
}

int find(Subset subset, int i){
    if((subset + i)->parent == -1){
        return i;
    }else{
        (subset + i)->parent = find(subset, (subset + i)->parent);
    }
}
