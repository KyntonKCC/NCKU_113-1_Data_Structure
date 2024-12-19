#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
typedef enum{
    plus, minus, times, divide, eos, operand
}precedence;
char expression[MAX_STACK_SIZE];
char remember[MAX_STACK_SIZE];
int size[MAX_STACK_SIZE];
void Prefix_to_Infix();
precedence getToken(char *, int *);
void rememberToken(precedence);
void push(char);
char pop();
void stackFull();
char stackEmpty();
int remtop = -1, sizetop = -1, length = 0;

int main(void){
    scanf("%s", expression);
    for(int i = 0; expression[i] != '\0'; i++, length++);
    Prefix_to_Infix();
    for(int i = remtop; i >= 0; i--)
        printf("%c", pop());
    printf("\n");
    return 0;
}

void Prefix_to_Infix(){
    char symbol;
    int n = length - 1;
    precedence token = getToken(&symbol, &n);
    while(token != eos){
        if(token == operand){
            push(symbol);
            size[++sizetop] = 1;
        }else{
            char op1[size[sizetop - 1]], op2[size[sizetop]];
            for(int i = 0; i < size[sizetop]; i++)
                op2[i] = pop();
            for(int i = 0; i < size[sizetop - 1]; i++)
                op1[i] = pop();
            for(int i = size[sizetop - 1] - 1; i >= 0; i--)
                push(op1[i]);
            rememberToken(token);
            for(int i = size[sizetop] - 1; i >= 0; i--)
                push(op2[i]);
            size[sizetop - 1] = size[sizetop] + size[sizetop - 1] + 1;
            size[sizetop] = 0;
            sizetop--;
        }
        token = getToken(&symbol, &n);
    }
}

precedence getToken(char *symbol, int *n){
    *symbol = expression[(*n)--];
    switch(*symbol){
        case '+': return plus;
        case '-': return minus;
        case '/': return divide;
        case '*': return times;
        case '\0': return eos;
        default : return operand;
    }
}

void rememberToken(precedence item){
    switch(item){
        case plus: push('+'); break;
        case minus: push('-'); break;
        case divide: push('/'); break;
        case times: push('*'); break;
    }
}

void push(char item){
    if(remtop >= MAX_STACK_SIZE - 1)
        stackFull();
    else
        remember[++remtop] = item;
}

char pop(){
    if(remtop == -1)
        return stackEmpty();
    else
        return remember[remtop--];
}

void stackFull(){
    fprintf(stderr, "Stack is full, cannot add element\n");
    exit(EXIT_FAILURE);
}

char stackEmpty(){
    fprintf(stderr, "Stack is empty, cannot pop element\n");
    exit(EXIT_FAILURE);
}