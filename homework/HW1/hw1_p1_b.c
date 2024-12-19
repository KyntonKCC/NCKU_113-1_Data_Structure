#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
typedef enum{
    plus, minus, times, divide, eos, operand
}precedence;
char expression[MAX_STACK_SIZE];
precedence stack[MAX_STACK_SIZE];
char remember[MAX_STACK_SIZE];
int isp[] = {12, 12, 13, 13, 0};
int icp[] = {12, 12, 13, 13, 0};
void Infix_to_Postfix();
precedence getToken(char *, int *);
void rememberToken(precedence);
void push(precedence);
precedence pop();
void stackFull();
precedence stackEmpty();
int top = -1, count = 0;

int main(void){
    scanf("%s", expression);
    Infix_to_Postfix();
    while(top != -1)
        rememberToken(pop());
    for(int i = 0; i < count; i++)
        printf("%c", remember[i]);
    printf("\n");
    count = 0;
    return 0;
}

void Infix_to_Postfix(){
    char symbol;
    int n = 0;
    precedence token = getToken(&symbol, &n);
    while(token != eos){
        if(token == operand){
            remember[count++] = symbol;
        }else{
            while(top != -1 && isp[stack[top]] >= icp[token])
                rememberToken(pop());
            push(token);
        }
        token = getToken(&symbol, &n);
    }
}

precedence getToken(char *symbol, int *n){
    *symbol = expression[(*n)++];
    switch(*symbol){
        case '+': return plus;
        case '-': return minus;
        case '/': return divide;
        case '*': return times;
        case '\0':
        case '\n':return eos;
        default : return operand;
    }
}

void rememberToken(precedence item){
    switch(item){
        case plus: remember[count++] = '+'; break;
        case minus: remember[count++] = '-'; break;
        case divide: remember[count++] = '/'; break;
        case times: remember[count++] = '*'; break;
    }
}

void push(precedence item){
    if(top >= MAX_STACK_SIZE - 1)
        stackFull();
    else
        stack[++top] = item;
}

precedence pop(){
    if(top == -1)
        return stackEmpty();
    else
        return stack[top--];
}

void stackFull(){
    fprintf(stderr, "Stack is full, cannot add element\n");
    exit(EXIT_FAILURE);
}

precedence stackEmpty(){
    fprintf(stderr, "Stack is empty, cannot pop element\n");
    exit(EXIT_FAILURE);
}