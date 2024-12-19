#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#define MAX_N 20


int main() {
    // Input
    int n;  // The first line input
    int heap[MAX_N];  // operations should be performed on this array
    int size = 0;

    if (scanf("%d", &n) != 1) {
        return 1; 
    }

    while (scanf("%d", &heap[size]) == 1) {
        size++;
        if (size >= MAX_N) break; 
    }


    // Output
    for (int i = 0; i < size; i++) {
        printf("%d", heap[i]);
        if (i < size-1) printf(" ");
    }
    printf("\n");

    return 0;
}