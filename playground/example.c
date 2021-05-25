#include <stdio.h>
#define concat(a, b) a##b
int main(void){
    int xy = 30;
    printf("%d", concat(x, y));
    return 0;
}