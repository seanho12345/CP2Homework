#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(){
    char *str = malloc(sizeof(char));
    printf("Please enter the hex string: ");
    char ch, *endptr;
    int len = 0;
    while(ch != '\n'){
        ch = getchar();
        str = realloc(str,sizeof(char) * len+1);
        str[len] = ch;
        len++;
    }
    str[len-1] = '\0';
    //printf("%d\n",len);
    char convert[(len-3)/2];
    int convertlen = 0,valid = 1;;
    for(int i=0;i<len-3;i+=2){
        char tmp[2];
        tmp[0] = str[i];
        tmp[1] = str[i+1];
        convert[convertlen] = strtol(tmp, &endptr, 16);
        if(*endptr == '\0' || (convert[convertlen]<0 || convert[convertlen]>127)){
            printf("ERROR\n");
            valid = 0;
            break;
        }
        convertlen++;
    }
    if(valid == 1){
        for(int i=0;i<convertlen;i++){
            printf("%c",convert[i]);
        }
        printf("\n");
    }
    
    free(str);
}