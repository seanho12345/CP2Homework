#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

struct option long_options[]= {
    {"size", 1, NULL, 'z'},
    {"help", 0, NULL, 'h'},
    {0,0,0,0,},
};
void print_help(){ // print out help info
    printf("Split:\n");
    printf("./hw0401 -s [file] --size [Small File Size]\n");
    printf("The default small file size is 1000 bytes.\n");
    printf("Recover:\n");
    printf("./hw0401 -r [output file] [small files]\n");
    printf("The input small files may not be in order.\n");
}

int main(int argc, char *argv[]){
    char filename[20]={0};
    int mode = 0;
    int c = 0;
    int invalid = 0;
    int splitsize = 1000;
    int index;
    while((c = getopt_long(argc,argv,"s:r:",long_options,&index)) != -1){
        switch(c){
            case 's':
                mode = 1;
                if(strlen(optarg) == 0){
                    invalid = 1;
                }
                strcpy(filename,optarg);
                break;
            case 'z':
                splitsize = 0;
                for(int i=0; i<strlen(optarg);i++){
                    splitsize *= 10;
                    splitsize += optarg[i] - '0';
                }
                printf("%d\n",splitsize);
                break;
            case 'r':
                mode = 2;
                if(strlen(optarg) == 0){
                    invalid = 1;
                }
                strcpy(filename,optarg);
                break;
            case 'h':
                print_help();
                break;
            case '?':
                invalid = 1;
                break;
        }
        if(invalid == 1){
            break;
        }
    }
    if(mode == 1){ //split mode
        uint8_t filecount = 1;
        FILE *source;
        source = fopen(filename,"r");   //open source file
        if(source == NULL){
            printf("Unable to read file\n");
            return 0;
        }
        while(!feof(source)){
            char wfilename[25] = {0};   //make output filename
            strncpy(wfilename,filename,20);
            int len = strlen(wfilename);
            wfilename[len] = '.';
            wfilename[len+1] = 48 + filecount;
            wfilename[len+2] = 0;
            uint8_t header = filecount; //write header for recover usage
            FILE *output = fopen(wfilename,"w");
            fwrite(&header,sizeof(uint8_t),1,output);
            int count;
            uint8_t *dataarr = calloc(splitsize,sizeof(uint8_t));
            count = fread(dataarr,sizeof(uint8_t),splitsize,source);
            fwrite(dataarr,1,count,output);
            filecount++;
            fclose(output);
        }
        fclose(source);
    }else if(mode == 2){ // recovery mode
        if(argc - 3 == 0){
            printf("Split files not given\n");
            return 0;
        }
        FILE *splitfiles[argc - 3];
        for(int i=3; i<argc; i++){
            char *rfilename = argv[i];
            FILE *tmp = fopen(rfilename, "r");
            if(tmp == NULL){
                printf("Unable to read file\n");
                return 0;
            }
            uint8_t header = 0;
            fread(&header,sizeof(uint8_t),1,tmp);
            splitfiles[header-1] = tmp;
        }
        FILE *output = fopen(filename,"w");
        for(int i=0; i<argc - 3; i++){
            FILE *tmp = splitfiles[i];
            while(!feof(tmp)){
                uint8_t *dataarr = calloc(1000,sizeof(uint8_t));
                int count;
                count = fread(dataarr,sizeof(uint8_t),1000,tmp);
                fwrite(dataarr,1,count,output);
            }
            fclose(tmp);
        }
        fclose(output);
    }

    return 0;

}

