#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
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
    int angle;
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
        return 0;
    }
    printf("Angle (0-90): ");
    scanf("%d",&angle);
    if(angle < 0 || angle > 90){
        printf("ERROR! Aborting...\n");
        return 0;
    }else{
        if(angle == 90){
            sBmpHeader header;
            fread(&header, sizeof(header), 1, source);
            fwrite(&header, sizeof(header), 1, output);
            while(!feof(source)){
                uint8_t sourcebinary[999] = {0};
                int count = fread(sourcebinary, 1, 999, source);
                fwrite(sourcebinary, 1, count, output);
            }
        }else if(angle == 0){
            sBmpHeader header;
            fread(&header, sizeof(header), 1, source);
            header.width *= 2;
            header.height = 1;
            fwrite(&header, sizeof(header), 1, output);
            int pixel = header.width * 3 + header.width % 4;
            uint8_t* writepixel = calloc(pixel,sizeof(uint8_t));
            fwrite(writepixel,1,pixel,output);
            free(writepixel);
        }else{
            sBmpHeader header;
            double slope = tan(angle * M_PI / 180.0);
            fread(&header, sizeof(header), 1, source);
            int32_t origin_width = header.width;
            header.width += header.height * (1.0/slope);
            fwrite(&header, sizeof(header), 1, output);

            int32_t rpixel = origin_width * 3 + origin_width % 4;
            int32_t wpixel = header.width * 3 + header.width % 4;
            uint8_t *rpixelarr = malloc(sizeof(uint8_t) * rpixel);
            uint8_t *wpixelarr = malloc(sizeof(uint8_t) * wpixel);
            
            for(int i=0; i<header.height; i++){
                fread(rpixelarr, 1, rpixel, source);
                for(int j=0; j<wpixel; j++){
                    wpixelarr[j] = 255;
                }
                for(int j=0; j<wpixel; j+=3){
                    if(slope * j / 3 - i >= 0.0){
                        for(int k=0; k < rpixel; k++){
                            wpixelarr[j+k] = rpixelarr[k]; 
                        }
                        fwrite(wpixelarr, 1, wpixel, output);
                        break;
                    }
                }
            }
            free(rpixelarr);
            free(wpixelarr);
        }
    }
    fclose(source);
    fclose(output);
}
///home/vonernue/CP2Homework/40947029S_hw03/doraemon.bmp