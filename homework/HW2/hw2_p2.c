#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 50

struct Node {
    int key;
    int degree;
    struct Node *prev;
    struct Node *next;
    struct Node *child;
    struct Node *parent;
};

typedef struct subset_s *Subset;
typedef struct subset_s{
    struct Node *node;
    int data;
    int grade;
    int root;
}subset_t;

struct Node *newNode(int);
struct Node *insert(struct Node *, struct Node *);
struct Node *swap(struct Node *, struct Node *);
struct Node *bubble_sort(struct Node *);
struct Node *find_min(struct Node *);
struct Node *delete_min(struct Node *, struct Node *);
int check_degree(struct Node *);
struct Node *merge(struct Node *, struct Node *);
struct Node *consolidation(struct Node *);
struct Node *search(struct Node *, int);
struct Node *decrease(struct Node *, int, int);
void traverse(struct Node *, Subset);
int cmp1(const void *, const void *);
int cmp2(const void *, const void *);
int cmp3(const void *, const void *);
void printList(struct Node *);
void printGraph(struct Node *, struct Node *, int);
void printSubset(Subset, int);

int main(void){
    int num1, num2;
    int node_count = 0, min = __INT32_MAX__;
    char step[20];
    struct Node *start = NULL;
    struct Node *minNode = NULL;
    while(1){
        scanf("%s", step);
        if(strcmp(step, "insert") == 0){
            scanf("%d", &num1);
            struct Node *temp = newNode(num1);
            if(temp->key < min){
                min = temp->key;
                minNode = temp;
            }
            start = insert(start, temp);
            node_count++;
            // printGraph(start, minNode, min);
        }else if(strcmp(step, "extract-min") == 0){
            start = bubble_sort(start);
            // printGraph(start, minNode, min);
            start = delete_min(start, minNode);
            // printGraph(start, minNode, min);
            start = bubble_sort(start);
            // printGraph(start, minNode, min);
            minNode = find_min(start);
            min = minNode->key;
            // printGraph(start, minNode, min);
            while(start->next != start && check_degree(start)){
                start = consolidation(start);
                // printGraph(start, minNode, min);
                start = bubble_sort(start);
                // printGraph(start, minNode, min);
            }
            node_count--;
        }else if(strcmp(step, "decrease") == 0){
            scanf("%d %d", &num1, &num2);
            start = decrease(start, num1, num2);
            minNode = find_min(start);
            min = minNode->key;
            // printGraph(start, minNode, min);
        }else if(strcmp(step, "delete") == 0){
            scanf("%d", &num1);
            start = decrease(start, num1, num1 + 1);
            minNode = find_min(start);
            min = minNode->key;
            start = delete_min(start, minNode);
            minNode = find_min(start);
            min = minNode->key;
            // printGraph(start, minNode, min);
            while(start->next != start && check_degree(start)){
                start = consolidation(start);
                // printGraph(start, minNode, min);
                start = bubble_sort(start);
                // printGraph(start, minNode, min);
            }
            node_count--;
        }else if(strcmp(step, "exit") == 0){
            // printGraph(start, minNode, min);
            // printRootLevelOrder(start);
            Subset subset = malloc(node_count * sizeof(*subset));
            for(int i = 0; i < node_count; i++){
                subset[i].node = NULL;
                subset[i].data = 0;
                subset[i].grade = 0;
                subset[i].root = 0;
            }
            // printSubset(subset, node_count);
            traverse(start, subset);
            int root = 0;
            for(int i = 0; i < node_count; i++){
                int count = 1;
                subset[i].data = subset[i].node->key;
                struct Node *temp = subset[i].node;
                while(temp->parent != NULL){
                    count++;
                    temp = temp->parent;
                }
                subset[i].grade = count;
                if(count == 1)
                    root++;
                subset[i].root = root;
            }
            // printSubset(subset, node_count);
            qsort(subset, node_count, sizeof(subset[0]), cmp1);
            // printSubset(subset, node_count);
            qsort(subset, node_count, sizeof(subset[0]), cmp2);
            // printSubset(subset, node_count);
            qsort(subset, node_count, sizeof(subset[0]), cmp3);
            // printSubset(subset, node_count);

            int nextLine = subset[0].root;
            for(int i = 0; i < node_count; i++){
                if(subset[i].root != nextLine){
                    printf("\n");
                    nextLine = subset[i].root;
                }
                printf("%d ", subset[i].data);
            }
            printf("\n");
            break;
        }
    }
    return 0;
}

struct Node *newNode(int num){
    struct Node *temp = malloc(sizeof(*temp));
    temp->degree = 0;
    temp->key = num;
    temp->prev = temp;
    temp->next = temp;
    temp->child = NULL;
    temp->parent = NULL;
    return temp;
}

struct Node *insert(struct Node *head, struct Node *temp){
    if(!head)
        return temp;
    temp->prev = head->prev;
    temp->next = head;
    head->prev->next = temp;
    head->prev = temp;
    return head;
}

struct Node *swap(struct Node *node1, struct Node *node2){
    struct Node *prev1 = node1->prev;
    struct Node *next2 = node2->next;
    prev1->next = node2;
    node2->prev = prev1;
    node2->next = node1;
    node1->prev = node2;
    node1->next = next2;
    next2->prev = node1;
    return node2;
}

struct Node *bubble_sort(struct Node *head){
    if(!head || head->next == head) 
        return head;
    if(head->prev == head->next)
        if(head->degree <= head->next->degree)
            return head;
        else 
            return head->next;
    int swapped;
    struct Node *current;
    struct Node *lastSorted = NULL;
    do{
        swapped = 0;
        current = head;
        do{
            struct Node *nextNode = current->next;
            if((current->degree > nextNode->degree) ||
                (current->degree == nextNode->degree && current->key > nextNode->key)) {
                if(current == head)
                    head = nextNode;
                current = swap(current, nextNode);
                swapped = 1;
            }
            current = current->next;
        }while(current->next != head && current->next != lastSorted);
        lastSorted = current;
    }while(swapped);
    return head;
}

struct Node *find_min(struct Node *head){
    if(head->next == head)
        return head;
    int min = __INT32_MAX__;
    struct Node *current = head;
    struct Node *minimum = NULL;
    do{
        if(current->key < min){
            min = current->key;
            minimum = current;
        }
        current = current->next;
    }while(current != head);
    return minimum;
}

struct Node *delete_min(struct Node *head, struct Node *minNode){
    if(head == minNode){
        head = minNode->next;
        if(head->next == head){
            head = minNode->child;
            head->parent = NULL;
            return head;
        }
    }
    struct Node *minNodeChild = minNode->child;
    if(minNodeChild != NULL){
        struct Node *current = minNodeChild;
        do{
            current->parent = NULL;
            current = current->next;
        }while(current != minNodeChild);
        struct Node *temp = minNode->prev;
        temp->next = minNodeChild;
        minNodeChild->prev->next = minNode;
        minNode->prev = minNodeChild->prev;
        minNodeChild->prev = temp;
    }
    // struct Node *feedback = minNode->next;
    minNode->prev->next = minNode->next;
    minNode->next->prev = minNode->prev;
    free(minNode);
    return head;
}

int check_degree(struct Node *head){
    struct Node *current = head;
    int degreetable[10] = {0};
    do{
        if(degreetable[current->degree] > 0)
            return 1;
        degreetable[current->degree]++;
        current = current->next;
    }while(current != head);
    return 0;
}

struct Node *merge(struct Node *small, struct Node *large){
    // printf("merge :: %d %d\n", small->key, large->key);
    small->degree += 1;
    large->parent = small;
    if(small->child == NULL){
        small->child = large;
        large->prev = large;
        large->next = large;
    }else{
        struct Node *child = small->child;
        large->prev = child->prev;
        large->next = child;
        child->prev->next = large;
        child->prev = large;
        // small->child = large;
    }
    return small;
}

struct Node *consolidation(struct Node *head){
    if(!head || head->next == head) 
        return head;
    struct Node *temp = head;
    struct Node *curr = head->next;
    do{
        if(temp->degree == curr->degree) {
            temp->next = curr->next;
            curr->next->prev = temp;
            temp = merge(temp, curr);
            curr = temp->next;
        }
        temp = temp->next;
        curr = curr->next;
    }while(temp->next != head);
    return head;
}

struct Node *search(struct Node *head, int target){
    if(head == NULL) 
        return NULL;
    struct Node *current = head;
    do{
        if(current->key == target)
            return current;
        if(current->child != NULL) {
            struct Node *result = search(current->child, target);
            if (result != NULL)
                return result;
        }
        current = current->next;
    }while(current != head);
    return NULL;
}

struct Node *decrease(struct Node *head, int target, int subtrahend){
    struct Node *find = search(head, target);
    find->key -= subtrahend;
    if(find->parent != NULL && find->key < find->parent->key){
        struct Node *parent = find->parent;
        parent->degree -= 1;
        if(find->next == find){
            parent->child = NULL;
        }else{
            find->prev->next = find->next;
            find->next->prev = find->prev;
            if (parent->child == find) 
                parent->child = find->next;
        }
        find->parent = NULL;
        head = insert(head, find);
    }
    return head;
}

int cmp1(const void *a, const void *b){
    return ((Subset)a)->data - ((Subset)b)->data;
}

int cmp2(const void *a, const void *b){
    return ((Subset)a)->grade - ((Subset)b)->grade;
}

int cmp3(const void *a, const void *b){
    return ((Subset)a)->root - ((Subset)b)->root;
}

void traverse(struct Node *head, Subset subset){
    static int count = 0;
    struct Node *current = head;
    do{
        if(subset[count].node == NULL)
            subset[count].node = current;
        count++;
        if(current->degree != 0)
            traverse(current->child, subset);
        current = current->next;
    }while(current != head);
}

void printList(struct Node *head) {
    struct Node *current = head;
    do{
        printf("%2d(%d)-", current->key, current->degree);
        if(current->degree != 0){
            printf("{");
            printList(current->child);
            printf("}");
        }
        current = current->next;
    }while(current != head);
}

void printGraph(struct Node *head, struct Node *minNode, int min){
    printf("List :: ");
    printList(head);
    printf("\nMIN --> %d, %d\n", minNode->key, min);
}

void printSubset(Subset subset, int size){
    for(int i = 0; i < size; i++)
        printf("%4d ", subset[i].data);
    printf("\n");
    for(int i = 0; i < size; i++)
        printf("%4d ", subset[i].grade);
    printf("\n");
    for(int i = 0; i < size; i++)
        printf("%4d ", subset[i].root);
    printf("\n");
}
