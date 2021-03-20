#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "mixed.h"
int main(){
    int a,b,c;
    sMixednumber num1,num2,added,sub,mul,div;
    printf("Enter a,b,c: ");
    scanf("%d %d %d",&a,&b,&c);
    mixed_set(&num1,a,b,c);
    printf("Enter a,b,c: ");
    scanf("%d %d %d",&a,&b,&c);
    mixed_set(&num2,a,b,c);
    mixed_print(num1);
    printf("\n");
    mixed_print(num2);
    printf("\n");
    mixed_add(&added,num1,num2);
    mixed_print(added);
    printf("\n");
    mixed_sub(&sub,num1,num2);
    mixed_print(sub);
    printf("\n");
    mixed_mul(&mul,num1,num2);
    mixed_print(mul);
    printf("\n");
    mixed_div(&div,num1,num2);
    mixed_print(div);
    printf("\n");
}