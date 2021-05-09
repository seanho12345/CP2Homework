#include <stdio.h>
#include <stdlib.h>
#include "myprintf.h"

int main(){
    int a = 0,b = -10, c = 2;
    int hex = 10;
    char str[10] = "hello";
    myprintf("int test:%d %i %d\n",a,b,c);
    myprintf("hex test:%x %X\n",hex,hex);
    myprintf("str test:%s\n",str);
    return 0;
}