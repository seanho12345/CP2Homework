#include <stdio.h>
#include <string.h>
#include <errno.h>
int main ()
{
    FILE * pFile;
    pFile=fopen ("unexist.ent","rb");
    if (pFile==NULL){
        perror("ERROR(perror)");
    }
    else{
        fclose (pFile);
    }
    pFile=fopen ("unexist.ent","rb");
    if (pFile==NULL){
        printf("ERROR(strerror): %s\n",strerror(errno));
    }
    else{
        fclose (pFile);
    }
    return 0;
}