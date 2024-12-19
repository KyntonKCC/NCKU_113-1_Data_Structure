#include <stdio.h> 
#include <stdlib.h>
#define MAX_NODES 20



int main() {
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



    // OutPut
    printf("%d", totalCost);
    for (int i = 0; i < n-1; i++) {
        printf(",(%d,%d)", mst[i][0], mst[i][1]);  
    }
    printf("\n");
    
    return 0;
}