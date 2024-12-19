#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
typedef enum{
    lparen, rparen, plus, minus, times, divide, eos, operand
}precedence;
char expression[MAX_STACK_SIZE];
char input[MAX_STACK_SIZE];
int stack[MAX_STACK_SIZE];
int eval();
precedence getToken(char *, int *);
void push(int);
int pop();
void stackFull();
int stackEmpty();
int top = -1;

int main(void){

    //1.
    scanf("%s", input);

    //2.
    // char *token;
    // int count = -1;
    // fgets(expression, sizeof(expression), stdin);
    // token = strtok(expression, " \n");
    // while(token != NULL){
    //     input[++count] = *token;
    //     token = strtok(NULL, " \n");
    // }

    int ans = eval();
    if(top == -1){
        printf("%d\n", ans);
    }else{
        printf("Invalid\n");
    }
    return 0;
}

int eval(){
    char symbol;
    int op1, op2;
    int n = 0;
    precedence token = getToken(&symbol, &n);
    while(token != eos){
        if(token == operand){
            push(symbol - '0');
        }else{
            op2 = pop();
            op1 = pop();
            switch(token){
                case plus : push(op1 + op2); break;
                case minus : push(op1 - op2); break;
                case times : push(op1 * op2); break;
                case divide : push(op1 / op2); break;
            }
        }
        token = getToken(&symbol, &n);
    }
    return pop();
}

precedence getToken(char *symbol, int *n){
    *symbol = input[(*n)++];
    switch(*symbol){
        case '(': return lparen;
        case ')': return rparen;
        case '+': return plus;
        case '-': return minus;
        case '/': return divide;
        case '*': return times;
        case '\0': return eos;
        default : return operand;
    }
}

void push(int item){
    if(top >= MAX_STACK_SIZE - 1){
        stackFull();
    }else{
        stack[++top] = item;
    }
}

int pop(){
    if(top == -1){
        return stackEmpty();
    }else{
        return stack[top--];
    }
}

void stackFull(){
    printf("Full\n");
    exit(EXIT_SUCCESS);
}

int stackEmpty(){
    printf("Empty\n");
    exit(EXIT_SUCCESS);
}
