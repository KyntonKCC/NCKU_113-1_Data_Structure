#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 100
#define MALLOC(p, s)\
    if(!((p) = malloc(s))){\
        printf("FAIL\n");\
        exit(EXIT_FAILURE);\
    }
int max_heap[MAX_SIZE];
void insert(int);
void delete();
void update(int, int);
int n = 0;

int main(void){
    int num1, num2;
    char step[20];
    while(1){
        scanf("%s", step);
        if(strcmp(step, "insert") == 0){
            scanf("%d", &num1);
            insert(num1);
        }else if(strcmp(step, "delete") == 0){
            delete();
        }else if(strcmp(step, "update") == 0){
            scanf("%d %d", &num1, &num2);
            update(num1, num2);
        }else{
            break;
        }
    }
    for(int i = 1; i <= n; i++)
        printf("%d ", max_heap[i]);
    printf("\n");
    return 0;
}

void insert(int num){
    int i = ++n;
    while((i != 1) && num > max_heap[i/2]){
        max_heap[i] = max_heap[i/2];
        i /= 2;
    }
    max_heap[i] = num;
}

void delete(){
    int parent = 1, child, temp = max_heap[n--];
    while(parent * 2 <= n){
        child = parent * 2;
        if(child < n && max_heap[child] < max_heap[child + 1])
            child++;
        if(temp >= max_heap[child])
            break;
        max_heap[parent] = max_heap[child];
        parent = child;
    }
    max_heap[parent] = temp;
}

void update(int num1, int num2){
    int i, parent, child;
    for(i = 1; i <= n; i++)
        if(max_heap[i] == num1){
            max_heap[i] = num2;
            break;
        }
    parent = i;

    while(parent > 1 && max_heap[parent] > max_heap[parent / 2]) {
        int temp = max_heap[parent];
        max_heap[parent] = max_heap[parent / 2];
        max_heap[parent / 2] = temp;
        parent /= 2;
    }

    while(parent * 2 <= n){
        child = parent * 2;
        if(child < n && max_heap[child] < max_heap[child + 1])
            child++;
        if(max_heap[parent] >= max_heap[child])
            break;
        int temp = max_heap[parent];
        max_heap[parent] = max_heap[child];
        max_heap[child] = temp;
        parent = child;
    }
}