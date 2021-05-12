//Reference: https://users.cs.jmu.edu/buchhofp/forensics/formats/pkzip.html
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint8_t signature[4] = {'P','K',3,4};
void print_help(){ // print out help info
    printf("Usage: ./hw0404 [Zip File]\n");
}

struct _zipheader{
    uint16_t version;
    uint16_t flags;
    uint16_t compression;
    uint16_t modtime;
    uint16_t moddate;
    uint32_t checksum;
    uint32_t compresssize;
    uint32_t uncompresssize;
    uint16_t filenamelen;
    uint16_t extralen;
}__attribute__ ((__packed__));
typedef struct _zipheader zipheader;

void printindent(int num){
    for(int i=0;i<num;i++){
        printf("    ");
    }
    printf("+-- ");
}
int main(int argc, char *argv[]){
    FILE *fptr;
    char filename[30];
    if(argc != 2){
        print_help();
        return 0;
    }else{
        strcpy(filename,argv[1]);
    }
    fptr = fopen(filename,"r");
    if(fptr == NULL){
        printf("Unable to read file");
        return 0;
    }
    int compcount = 0;
    int indent = 0;
    char dirstack[100][100]={0};
    while(!feof(fptr)){
        if(compcount == 4){
            zipheader *header = malloc(sizeof(zipheader));
            fread(header,sizeof(zipheader),1,fptr);
            char filenamestr[header->filenamelen+1];
            fread(filenamestr,sizeof(uint8_t),header->filenamelen,fptr);
            filenamestr[header->filenamelen] = '\0';
            if(filenamestr[header->filenamelen-1] == '/'){
                strcpy(dirstack[indent],filenamestr);
                while(strncmp(dirstack[indent-1],filenamestr,strlen(dirstack[indent-1])) != 0 && indent != 0){
                    indent--;
                }
                filenamestr[header->filenamelen-1] = '\0';
                printindent(indent);
                if(indent == 0){
                    printf("%s",filenamestr);
                }else{
                    for(int i=strlen(dirstack[indent-1]); filenamestr[i] != '\0'; i++){
                        fputc(filenamestr[i],stdout);
                    }
                }
                indent++;
            }else{
                while(strncmp(dirstack[indent-1],filenamestr,strlen(dirstack[indent-1])) != 0 && indent != 0){
                    indent--;
                }
                printindent(indent);
                if(indent == 0){
                    printf("%s",filenamestr);
                }else{
                    for(int i=strlen(dirstack[indent-1]); filenamestr[i] != '\0'; i++){
                        fputc(filenamestr[i],stdout);
                    }
                }
            }
            printf("\n");
            //printf("%s\n",filenamestr);
            compcount = 0;
        }
        //printf("compcount: %d",compcount);
        uint8_t *tmpdata = malloc(sizeof(uint8_t));
        fread(tmpdata,sizeof(uint8_t),1,fptr);
        if(*tmpdata == signature[compcount]){
            compcount++;
        }else{
            compcount = 0;
        }
    }
    fclose(fptr);
    return 0;
}