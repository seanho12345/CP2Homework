#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void output(char *o_ptr){
    int a=1,b=1;
    char *ptr;
    for(ptr = o_ptr; ptr<=&o_ptr[strlen(o_ptr)-1];ptr++){
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
        for(char *ch = ptr; *ch!=',' && *ch != ']' && *ch != '}';ch++){
            putchar(*ch);
        }
    }
    printf("\n");
}

int main(){
    int cmd = 1;
    char str[2049]={0},okey[2049]={0},key[2049]={0},subkey[2049]={0},c;
    char *find;
    
    printf("Please enter the JSON string:\n");
    fgets(str,2048,stdin);
    //printf("%s",str);
    while(1){
        char okey[2049]={0},key[2049]={0},subkey[2049]={0},c;
        int sub = 0,subkeylen=0,arr = 0,arrnum=0,len,valid;
        printf("Choice (0:Exit ,1:Get): ");
        valid = scanf("%d",&cmd);
        if(cmd == 0){
            break;
        }else if(!valid || cmd != 1){
            printf("ERROR!\n");
            while ( (c = getchar()) != '\n' && c != EOF ) ;
            continue;
        }
        printf("Key: ");
        while ( (c = getchar()) != '\n' && c != EOF ) ;
        fgets(okey,2048,stdin);   
        for(int i=0;i<strlen(okey);i++){
            if(okey[i] == '\n'){
                okey[i] = '\0';
            }else if(okey[i] == '.'){
                sub = 1;
                if(arr == 0){
                    strncpy(key,okey,i);
                }
            }else if(okey[i] == '['){
                strncpy(key,okey,i);
                arr = 1;
                for(int j=i+1; j<strlen(okey);j++){
                    if(okey[j] == ']'){
                        break;
                    }else{
                        arrnum*=10;
                        arrnum += okey[j]-'0';
                    }
                }
            }else if(sub == 1){
                subkey[subkeylen] = okey[i];
                subkeylen++;
            }
        }
        if(sub == 0 && arr == 0){
            strcpy(key,okey);
        }
        //printf("%s %s %d\n",key,subkey,arrnum);
        find = strstr(str,key);
        //printf("%s",find);
        if(find == NULL){
            printf("Not Found!\n");
        }else{
            if(arr == 1 && sub == 1){
                while(arrnum!=0){
                    find = strstr(find,subkey);
                    if(find == NULL){
                        printf("Not Found!\n");
                    }else{
                        arrnum--;
                        char *ptr;
                        for(ptr = find; ptr<=&find[strlen(find)-1] && *ptr!= ',';ptr++);
                        find = ptr;
                    }
                }
                find = strstr(find,subkey);
                output(find);
            }else if(sub == 1){
                find = strstr(find,subkey);
                output(find);
            }else if(arr == 1){
                for(find; find<=&find[strlen(find)-1] && *find != '[';find++);
                while(arrnum != 0){
                    char *ptr;
                    for(ptr = find; ptr<=&find[strlen(find)-1] && *ptr!= ',';ptr++);
                    find = ptr;
                    find++;
                    arrnum--;
                }
                printf("Value: ");
                if(*find == '\"'){
                    for(char *ch = find+1; *ch!='\"';ch++){
                        putchar(*ch);
                    }
                }else{
                    for(char *ch = find; *ch!=',' && *ch != '}' && *ch != ']';ch++){
                        putchar(*ch);
                    }
                }
                printf("\n");
            }else{
                output(find);
            }
        }
    }
    printf("Bye\n");
    return 0;
}