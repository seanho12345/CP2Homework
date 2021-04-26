#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
FILE *readFile(char mode){
    int valid=1,i;
    char filename[128]={0};
    FILE *ptr = NULL;
    fgets(filename,128,stdin);
    filename[strlen(filename)-1] = 0;
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
            if(strncmp(type,"bmp",3) != 0){
                valid = 0;
            }
        }
    }
    if(valid == 1){
        return fopen(filename,&mode);
    }else{
        return NULL;
    }
}

struct _sBmpHeader
{
    char		bm[2];
    uint32_t	size;
    uint32_t	reserve;
    uint32_t	offset;
    uint32_t	header_size;
    uint32_t	width;
    uint32_t	height;
    uint16_t	planes;
    uint16_t	bpp;
    uint32_t	compression;
    uint32_t	bitmap_size;
    uint32_t	hres;
    uint32_t	vres;
    uint32_t	used;
    uint32_t	important;
}__attribute__ ((__packed__));

typedef struct _sBmpHeader sBmpHeader;

int main(){
    FILE *source = NULL;
    FILE *output = NULL;
    uint8_t alpha;
    printf("Please input a BMP file: ");
    source = readFile('r');
    if(source == NULL){
        printf("ERROR! Aborting...\n");
        return 0;
    }
    printf("Please input the output BMP file name: ");
    output = readFile('w');
    if(output == NULL){
        printf("ERROR! Aborting...\n");
        fclose(source);
        return 0;
    }
    printf("Alpha (0-31): ");
    scanf("%hhd",&alpha);
    if(alpha < 0 || alpha > 31){
        printf("ERROR! Aborting...\n");
        return 0;
    }else{
        sBmpHeader header;
        fread(&header, sizeof(header), 1, source);
        if(header.bpp != 24){
            printf("ERROR! Aborting...\n");
            return 0;
        }
        header.size = 70 + header.width * header.height * 4;
        header.offset = 70;
        header.header_size = 56;
        header.bpp = 32;
        header.compression = 3;
        header.bitmap_size = header.width * header.height * 4;
        uint32_t mask[4] = {0x00FF0000,0x0000FF00,0x000000FF,0xFF000000};
        fwrite(&header, sizeof(header), 1, output);
        fwrite(&mask,sizeof(uint32_t),4,output);
        int32_t rpixel = header.width * 3 + header.width % 4;
        int32_t wpixel = header.width * 4;
        uint8_t *rpixelarr = malloc(sizeof(uint8_t) * rpixel);
        uint8_t *wpixelarr = malloc(sizeof(uint8_t) * wpixel);
        while(!feof(source)){
            fread(rpixelarr, 1, rpixel, source);
            int writepos = 0;
            for(int i=0; i<header.width * 3; i++){
                if(writepos % 4 == 3){
                    wpixelarr[writepos] = alpha;
                    writepos++;
                }
                wpixelarr[writepos] = rpixelarr[i];
                writepos++;
            }
            fwrite(wpixelarr, 1, wpixel, output);
        }
    }
    fclose(source);
    fclose(output);
    return 0;
}