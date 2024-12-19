#include <stdio.h>
#define MAX_N 20



int main() {
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

    // Output
    if(has_cycle) {
        printf("True,(%d,%d)\n", cycle_x, cycle_y);
    } else {
        printf("False,(%d,%d)\n", cycle_x, cycle_y);
    }
    
    
    return 0;
}