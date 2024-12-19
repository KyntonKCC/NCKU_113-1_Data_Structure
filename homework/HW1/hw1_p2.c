#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
#define HEAP_FULL(n) (n == MAX - 1)
#define HEAP_EMPTY(n) (!n)
int min_heap[MAX];
void insert(int);
void delete(int);
int n = 0;

int main(){
    int num;
    char step[50];
    while (scanf("%s %d", step, &num) != EOF) {
        if(strcmp(step, "insert") == 0)
            insert(num);
        else if(strcmp(step, "delete") == 0)
            delete(num);
    }
    for(int i = 1; i <= n; i++)
        printf("%d ", min_heap[i]);
    printf("\n");
    return 0;
}

void insert(int item){
    if(HEAP_FULL(n)){
        fprintf(stderr, "The heap is full.\n");
        exit(EXIT_FAILURE);
    }
    int i = ++n;
    while((i != 1) && (item < min_heap[i/2])){
        min_heap[i] = min_heap[i/2];
        i /= 2;
    }
    min_heap[i] = item;
}

void delete(int num){
    if(HEAP_EMPTY(n)){
        fprintf(stderr, "The heap is empty.\n");
        exit(EXIT_FAILURE);
    }

    //1. 90/100
    // int parent, child, temp = min_heap[n--];
    // for(int i = 1; i <= n; i++){
    //     if(min_heap[i] == num){
    //         parent = i;
    //         break;
    //     }
    // }

    //2. 100/100
    int i, parent, child, temp = min_heap[n--];
    for(i = 1; i <= n; i++) 
        if(min_heap[i] == num) 
            break;
    parent = i;
    
    while(parent * 2 <= n){
        child = parent * 2;
        if((child < n) && (min_heap[child] > min_heap[child + 1]))
            child++;
        if(temp <= min_heap[child])
            break;
        min_heap[parent] = min_heap[child];
        parent = child;
    }
    min_heap[parent] = temp;
}