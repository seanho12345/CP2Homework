#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
char *prev = NULL;
char *mystrchr(const char *s, int c){
    int i;
    for(i=0;s[i] != '\0';i++){
        if(s[i] == c){
            break;
        }
    }
    return (char *)&s[i];
}
char *mystrrchr(const char *s, int c){
    int i;
    for(i = strlen(s);i>=0;i--){
        if(s[i] == c){
            break;
        }
    }
    return (char *)&s[i];
}
size_t mystrspn(const char *s, const char *accept){
    uint re=0;
    int flag = 0;
    for(int i=0;i<strlen(accept);i++){
        for(int j=0;j<strlen(s);j++){
            if(accept[i] == s[j]){
                re++;
            }else{
                flag = 1;
                break;
            }
        }
        if(flag == 1){
            break;
        }
    }
    return re;
}
size_t mystrcspn(const char *s, const char *reject){
    uint min=strlen(s)+1;
    int find=1;
    for(int i=0;i<strlen(reject);i++){
        for(int j=0;j<strlen(s);j++){
            if(reject[i] == s[j] && j<min){
                min = j;
            }
        }
    }
    return min;
}
char *mystrpbrk(const char *s, const char *accept){
    char *ptr = (char *)&s[strlen(s)-1];
    int find = 0;
    for(int i=0;i<strlen(accept);i++){
        for(int j=0;j<strlen(s);j++){
            if(accept[i] == s[j]){
                if(&s[j]<ptr){
                    ptr = (char *)&s[j];
                    find = 1;
                }
            }
        }
    }
    if(find == 0){
        ptr = NULL;
    }
    return ptr;
}
char *mystrstr(const char *haystack , const char *needle){
    char *ptr = NULL;
    int count = 0;
    for(int i=0;i<strlen(haystack);i++){
        if(haystack[i] == needle[count]){
            count++;
            if(count = strlen(needle)){
                ptr = (char *)&haystack[i-strlen(needle)+2];
            }
        }
    }
    return ptr;
}
char *mystrtok(char *str, const char *delim){
    int find = 0;
    char *ptr;
    if(str == NULL){
        ptr = prev;
    }else{
        ptr = str;
    }
    //printf("%p\n",ptr);
    for(char *i=ptr; ptr != NULL && i<&ptr[strlen(ptr)];i++){
        for(int j=0;delim[j]!='\0';j++){
            if(*i == delim[j]){
                *i = '\0';
                prev = i+1;
                find = 1;
                //printf("FIND ");
                break;
            }
        }
        if(find == 1){
            break;
        }
    }
    if(find == 0){
        if(prev == NULL){
            ptr = NULL;
        }else{
            prev = NULL;
        }
    }
    return ptr;
}