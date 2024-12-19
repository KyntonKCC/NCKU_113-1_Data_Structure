#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

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

int main() {
    int n;
    int adjacencyMatrix[MAX_N][MAX_N];
    int edges[MAX_N][2];     // Stores the selected edges
    int edgeCount = 0;
    int cost = 0;

    readInput(&n, adjacencyMatrix);

    //Here is your code

    outputResult(cost, edgeCount, edges);

    return 0;
}