#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>    
#include <sys/stat.h>    
#include <sys/mman.h>
#include <fcntl.h>
#include "b64.h"

struct option long_options[]= {
    {"enc", 1, NULL, 'e'},
    {"dec", 1, NULL, 'd'},
    {"output", 1, NULL, 'o'},
    {"help", 0, NULL, 'h'},
    {0,0,0,0},
};

void print_help(){ // print out help info
    printf("Usage: ./hw0501 [option] [filename]\n");
    printf("-e, --enc    Encode a file to a text file.\n");
    printf("-d, --dec    Decode a text file to a file.\n");
    printf("-o, --output Output file name.\n");
}

void checkfilevalid(FILE *fptr){
    if(fptr == NULL){
        printf("Unable to open file\n");
        exit(0);
    }
}

int main(int argc,char *argv[]){
    //check input is valid
    if(argc != 5){  
        print_help();
        return 0;
    }
    char opt;
    int enc = 0, dec = 0;
    int isbmp = 0;
    char infilename[100] = {0}, outfilename[100] = {0};
    //get argument
    while((opt = getopt_long(argc, argv, "e:d:o:h", long_options, NULL)) != -1){
        switch(opt){
            case 'e':
                enc = 1;
                strcpy(infilename, optarg);
                //check if it's bmp
                char type[4];
                type[3] = 0;
                int count = 2;
                for(int i=strlen(infilename)-1; i>=0 && count>=0 && i != '.'; i--){
                    type[count] = infilename[i];
                    count--; 
                }
                if(strcmp("bmp", type) == 0){
                    isbmp = 1;
                }
                break;
            case 'd':
                dec = 1;
                strcpy(infilename, optarg);
                break;
            case 'o':
                strcpy(outfilename, optarg);
                break;
            case '?':
                print_help();
                break;
        }
    }
    //setup file pointers
    FILE *inptr = fopen(infilename, "r");
    FILE *outptr = fopen(outfilename, "w");
    //check if there's error opening file
    checkfilevalid(inptr);
    checkfilevalid(outptr);
    //encoding file
    if(enc == 1){
        if(isbmp == 1){ //bmp encrypt
            bmpencrypt(inptr, outptr);
        }else{ //normal txt encrypt
            txtencode(inptr, outptr);
        }
        
    }
    //decoding file
    if(dec == 1){
        decode(inptr, outptr);
    }
    return 0;
}