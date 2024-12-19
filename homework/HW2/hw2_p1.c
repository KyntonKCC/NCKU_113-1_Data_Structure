#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    int bucket, slot, num;
    char step[20];
    scanf("%s %d", step, &bucket);
    scanf("%s %d", step, &slot);
    int table[bucket][slot];
    for(int i = 0; i < bucket; i++)
        for(int j = 0; j < slot; j++)
            table[i][j] = -1;
    
    while(1){
        scanf("%s", step);
        if(strcmp(step, "insert") == 0){
            scanf("%d", &num);
            int col = num % bucket;
            int i = col, j = 0;
            while(table[i][j] != -1){
                if(i == bucket - 1 && j == slot - 1){
                    i = 0;
                    j = 0;
                }else if(j == slot - 1){
                    i++;
                    j = 0;
                }else{
                    j++;
                }
            }
            table[i][j] = num;
        }else if(strcmp(step, "delete") == 0){
            scanf("%d", &num);
            int col = num % bucket;
            int i = col, j = 0;
            while(table[i][j] != num){
                if(i == bucket - 1 && j == slot - 1){
                    i = 0;
                    j = 0;
                }else if(j == slot - 1){
                    i++;
                    j = 0;
                }else{
                    j++;
                }
            }
            table[i][j] = -1;
        }else if(strcmp(step, "search") == 0){
            scanf("%d", &num);
            int col = num % bucket;
            int i = col, j = 0;
            while(table[i][j] != num){
                if(i == bucket - 1 && j == slot - 1){
                    i = 0;
                    j = 0;
                }else if(j == slot - 1){
                    i++;
                    j = 0;
                }else{
                    j++;
                }
            }
            printf("%d %d\n", i, j);
        }else if(strcmp(step, "exit") == 0){
            break;
        }
    }
    return 0;
}
