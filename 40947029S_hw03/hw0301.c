#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RED   "\033[31m"
#define GRN   "\033[32m"
#define YEL   "\033[33m"
#define BLU   "\033[34m"
#define MAG   "\033[35m"
#define CYN   "\033[36m"
#define WHT   "\033[37m"
#define RED_BACK   "\033[41m"
#define RESET "\033[0m"

int main(){
    int valid = 1;
    char filename[128]={0};
    FILE *fptr = NULL;
    printf("Open a LRC file: ");
    fgets(filename,128,stdin);
    filename[strlen(filename)-1] = 0;
    int i;
    for(i=strlen(filename)-1;i>=0;i--){
        if(filename[i] == '.'){
            break;
        }
    }
    if(i == -1){
        valid = 0;
    }else{
        i++;
        if(strlen(filename) - i != 3){
            valid = 0;
        }else{
            char type[3];
            int k=0;
            for(i; i<strlen(filename);i++){
                type[k] = filename[i];
                k++;
            }
            if(strncmp(type,"lrc",3) != 0){
                valid = 0;
            }
        }
    }
    if(valid == 1){
        if((fptr = fopen(filename,"r")) == NULL){
            printf("FILE COULD NOT BE OPENED!\n");
            return 0;
        }
        char character[10][20]={0};
        char tmpstr[1024]={0};
        int init = 1;
        int char_now = 0,char_num = -1;
        double prevsec=0.0,sec=0.0;
        while(!feof(fptr)){
            fgets(tmpstr,1024,fptr);
            if(init == 1){
                while(1){
                    if(tmpstr[0] == '['){
                        fgets(tmpstr,1024,fptr);
                    }else{
                        init = 0;
                        break;
                    }
                }
            }
            //printf("%s\n",tmpstr);
            int tmpnum=0;
            if(tmpstr[0] == '['){
                char sentence[512]={0};
                double tmpsec=0.0;
                int sentencelen = 0;
                prevsec = sec;
                sec = 0;
                for(i=1; tmpstr[i]!=':'; i++){
                    tmpnum *= 10;
                    tmpnum += tmpstr[i] - '0';
                }
                sec += tmpnum * 60;
                for(i++; tmpstr[i]!='.'; i++){
                    tmpnum *= 10;
                    tmpnum += tmpstr[i] - '0';
                }
                sec += tmpnum;
                for(i++; tmpstr[i]!=']'; i++){
                    tmpnum *= 10;
                    tmpnum += tmpstr[i] - '0';
                }
                sec += 0.01 * tmpnum;
                for(i++; tmpstr[i]!='\0'; i++){
                    sentence[sentencelen] = tmpstr[i];
                    sentencelen++;
                }
                sentence[sentencelen] = '\0';
                sleep(sec - prevsec);
                if(sec-prevsec != 0){
                    printf("%s",sentence);
                }
                prevsec = sec;
            }else{
                char tmpch[21]={0};
                for(i=0; tmpstr[i]!='\0' && i<=19;i++){
                    tmpch[i] = tmpstr[i];
                }
                i--;
                if(tmpch[i-2] == ':'){
                    int find = 0;
                    for(int j=0; j<char_num; j++){
                        if(strcmp(character[j],tmpch) == 0){
                            find = 1;
                            char_now = j;
                            break;
                        }
                    }
                    if(find == 0){
                        char_num++;
                        strcpy(character[char_num],tmpch);
                        char_now = char_num;
                    }
                    switch (char_now){
                        case 0:
                            printf("%s",RED);
                            break;
                        case 1:
                            printf("%s",GRN);
                            break;
                        case 2:
                            printf("%s",YEL);
                            break;
                        case 3:
                            printf("%s",BLU);
                            break;
                        case 4:
                            printf("%s",MAG);
                            break;
                        case 5:
                            printf("%s",CYN);
                            break;
                        case 6:
                            printf("%s",WHT);
                            break;
                        case 7:
                            printf("%s",RED_BACK);
                            break;
                    }
                }
            }
        }
        fclose(fptr);
    }else{
        printf("FILE TYPE NOT SUPPORTED!\n");
    }
    
    //printf("%s",RESET);
    return 0;
}