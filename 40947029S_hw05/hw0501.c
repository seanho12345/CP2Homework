//base64 library: https://gist.github.com/caseyscarborough/8467877
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
#include "fileb64.h"

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
    char infilename[100] = {0}, outfilename[100] = {0};
    //get argument
    while((opt = getopt_long(argc, argv, "e:d:o:h", long_options, NULL)) != -1){
        switch(opt){
            case 'e':
                enc = 1;
                strcpy(infilename, optarg);
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
    int inptr = open(infilename, O_RDONLY);
    FILE *outptr = fopen(outfilename, "w");
    //check if there's error opening file
    if(inptr == -1){
        printf("Unable to read file\n");
        return 0;
    }
    checkfilevalid(outptr);
    //get input file size
    struct stat st;
    fstat(inptr, &st);
    size_t size = st.st_size;
    //encoding file
    if(enc == 1){
        b64('e', infilename, outfilename, 72);
        /*
        int count;
        unsigned char *data = mmap(0, size, PROT_READ, MAP_PRIVATE, inptr, 0);
        char *encdata = NULL;
        encdata = b64_encode(data, size);
        fwrite(encdata, sizeof(char), strlen(encdata), outptr);
        munmap(data,size);
        */
    }
    //decoding file
    if(dec == 1){
        b64('d', infilename, outfilename, 72);
        /*
        int count;
        char *data = (char *)mmap(0, size, PROT_READ, MAP_PRIVATE, inptr, 0);
        unsigned char *decdata = NULL;
        decdata = b64_decode(data, size);
        fwrite(decdata, sizeof(unsigned char), strlen(decdata), outptr);
        munmap(data,size);
        */
    }
    return 0;
}