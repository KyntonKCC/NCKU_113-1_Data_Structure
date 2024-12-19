#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#define MAX_N 20

//27/30
/*
2
50 30 40 10 20

4
90 70 80 50 60 40 30 10 20
*/

int main(void) {
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

    int length = size, temp, index;
    for(int T = 0; T < n; T++){
        temp = heap[0];
        heap[0] = heap[size - 1];
        heap[size - 1] = temp;
        size--;

        int parent = 0;
        if((heap[parent] < heap[parent + 1] && (parent + 1) <= size - 1) 
            || (heap[parent] < heap[parent + 2] && (parent + 2) <= size - 1)){
            index = heap[parent + 1] > heap[parent + 2] ? (parent + 1) : (parent + 2);
            temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;
            parent = index;
        }
        
        while((heap[parent] < heap[2 * parent + 1] && (2 * parent + 1) <= size - 1) 
            || (heap[parent] < heap[2 * parent + 2] && (2 * parent + 2) <= size - 1)){
            index = heap[2 * parent + 1] > heap[2 * parent + 2] ? (2 * parent + 1) : (2 * parent + 2);
            temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;
            parent = index;
        }
    }

    // Output
    for (int i = 0; i < length; i++) {
        printf("%d", heap[i]);
        if (i < length-1) printf(" ");
    }
    printf("\n");

    return 0;
}