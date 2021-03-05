#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw0103.h"

int main(){
    char *tmpch_ptr = pStr01;
    pStr01 = pStr02;
    pStr02 = tmpch_ptr;
    print_answers();
    return 0;
}