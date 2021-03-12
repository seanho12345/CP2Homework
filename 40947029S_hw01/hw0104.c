#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    int cmd = 1;
    char str[2049]={0},key[2049]={0},c;
    char *find;
    int keylen,len;
    printf("Please enter the JSON string:\n");
    fgets(str,2048,stdin);
    //printf("%s",str);
    while(1){
        printf("Choice (0:Exit ,1:Get): ");
        scanf("%d",&cmd);
        if(cmd == 0){
            break;
        }
        printf("Key: ");
        while ( (c = getchar()) != '\n' && c != EOF ) ;
        fgets(key,2048,stdin);   
        for(int i=0;i<strlen(key);i++){
            if(key[i] == '\n'){
                key[i] = '\0';
            }
        }
        find = strchr(key,'.');
        if(find != NULL){
            printf("Not yet supported!\n");
            continue;
        }
        find = strstr(str,key);
        //printf("%s",find);
        if(find == NULL){
            printf("Not Found!\n");
        }else{
            int a=1,b=1;
            char *ptr;
            for(ptr = find; ptr<=&find[strlen(find)-1];ptr++){
                if(a==0 && b==0){
                    ptr+=1;
                    break;
                }else if(*ptr == '\"'){
                    a--;
                }else if(*ptr == ':'){
                    b--;
                }
            }
            printf("Value: ");

            if(*ptr == '\"'){
                for(char *ch = ptr+1; *ch!='\"';ch++){
                    putchar(*ch);
                }
            }else{
                for(char *ch = ptr; *ch!=',' && *ch != '}';ch++){
                    putchar(*ch);
                }
            }
            printf("\n");
        }
    }
    printf("Bye\n");
    return 0;
}