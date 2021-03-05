#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define ANSI_RED "\033[1;31m"
#define ANSI_BLUE "\033[1;34m"
#define ANSI_RESET "\033[1;0m"

char* readstring(int *len_ptr){
    char *str = malloc(sizeof(char));
    char ch = 1;
    int len = 0;
    while(ch != '\0'){
        ch = getchar();
        if(ch == '\n'){
            ch = '\0';
        }
        str = realloc(str,sizeof(char) * len+1);
        str[len] = ch;
        len++;
    }
    *len_ptr = len;
    return str;
}
int main(){
    char *ostr,*key,*replace;
    int ostrlen=0,keylen=0,replacelen=0;
    printf("Please enter the orginal text:\n");
    ostr = readstring(&ostrlen);
    char str[ostrlen];
    for(int i=0;i<ostrlen;i++){
        str[i] = ostr[i];
    }
    printf("Keyword:\n");
    key = readstring(&keylen);
    printf("New word:\n");
    replace = readstring(&replacelen);
    char *substr = NULL, *prevfind = ostr, *split = " ";
    //printf("%d %s\n%d %s\n%d %s\n",strlen,str,keylen,key,replacelen,replace);
    printf("Before:\n");
    substr = strtok(ostr,split);
    while(substr != NULL){
        //printf("%d\n",strncmp(substr,key,keylen));
        if(strncmp(substr,key,keylen-1)==0){
            printf(ANSI_BLUE "%s" ANSI_RESET,key);
            for(int i=keylen-1; i<strlen(substr) && substr[i] != '\0'; i++){
                putchar(substr[i]);
            }
            printf(" ");
        }else{
            printf("%s ",substr);
        }
        substr = strtok(NULL,split);
    }
    printf("\n");
    printf("After:\n");
    substr = strtok(str,split);
    while(substr != NULL){
        //printf("%d",strncmp(substr,key,keylen));
        if(strncmp(substr,key,keylen-1)==0){
            printf(ANSI_RED "%s" ANSI_RESET,replace);
            for(int i=keylen-1; i<strlen(substr) && substr[i] != '\0'; i++){
                putchar(substr[i]);
            }
            printf(" ");
        }else{
            printf("%s ",substr);
        }
        substr = strtok(NULL,split);
    }
    printf("\n");
    
    
}