#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>

struct option long_options[]= {
    {"help", 0, NULL, 'h'},
    {0,0,0,0,},
};

void print_help(){ // print out help info
    printf("./hw0402 -l [options] -i [input file] -o [output file]\n");
    printf("./hw0402 -h\n");
    printf("./hw0402 --help\n");
    printf("    Display this help manual.\n");
}

int main(int argc, char* argv[]){
    char infilename[30]={0}, outfilename[30] = {0};
    int invalid = 0;
    int c,index;
    int instr = 0;
    int level = 0;
    srand(time(NULL));
    while((c = getopt_long(argc,argv,"l:i:o:h",long_options,&index)) != -1){
        switch(c){
            case 'h':
                print_help();
                break;
            case 'i':
                if(strlen(optarg) == 0){
                    invalid = 1;
                }
                strcpy(infilename,optarg);
                break;
            case 'o':
                if(strlen(optarg) == 0){
                    invalid = 1;
                }
                strcpy(outfilename,optarg);
                break;
            case 'l':
                level = atoi(optarg);
                if(level < 1 || level > 4){
                    invalid = 1;
                }
                
        }
        if(invalid == 1){
            break;
        }
    }
    if(invalid == 1){
        return 0;
    }
    FILE *inptr, *outptr;
    inptr = fopen(infilename,"r");
    if(inptr == NULL){
        printf("Unable to open file\n");
        return 0;
    }
    outptr = fopen(outfilename,"w");
    if(level == 1){
        while(!feof(inptr)){
            char line[200]={0};              
            fgets(line,200,inptr);
            for(int i=0; i<strlen(line); i++){
                if(instr == 0){
                    if(line[i] == ',' || line[i] == ';' || line[i] == '[' || line[i] == '('){
                        int randnum = rand()%4;
                        if(randnum == 0 || randnum == 1){
                            int randspace = rand()%100;
                            for(int k=0; k<randspace; k++){
                                fputc(' ',outptr);
                            }
                        }
                    }
                }
                if(line[i] == '"'){
                    if(instr){
                        instr = 0;
                    }else{
                        instr = 1;
                    }
                }else if(line[i] == '\\'){
                    fputc(line[i],outptr);
                    i++;
                }
                fputc(line[i],outptr);
            }
        }
    }else if(level == 2){
        printf("not yet implemented :)\n");
    }else if(level == 3){
        printf("not yet implemented :)\n");
    }else if(level == 4){
        printf("not yet implemented :)\n");
    }
            
    
    return 0;
}