#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(){
    char *str = malloc(sizeof(char));
    printf("Please enter the hex string: ");
    char ch, *endptr;
    int len = 0,valid = 1;
    char tmp[3]={0},count=0;
    while(ch != '\n'){
        ch = getchar();
        tmp[count] = ch;
        count++;
        if(count == 2){
            count = 0;
            str[len] = strtol(tmp, &endptr, 16);
            str = realloc(str,sizeof(char)*(len+1));
            len++;
        }
        if(*endptr != '\0'){
            printf("Error\n");
            valid = 0;
            break;
        }
    }
    if(str[len-1] != '\0'){
        valid = 0;
        printf("Error\n");
    }
    if(valid == 1){
        printf("%s\n",str);
    }
    free(str);
}