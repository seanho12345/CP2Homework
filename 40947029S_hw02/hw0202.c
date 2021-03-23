#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef union{
    struct{
        uint64_t frac:52;
        uint16_t expo:11;
        uint8_t sign:1;
    }bit;
    double num;
}_mydouble;

int main(){
    _mydouble mydouble;
    printf("Please enter a floating-point number (double precision): ");
    scanf("%lf", &mydouble.num); 
    printf("Sign: ");
    printf("%d\n",mydouble.bit.sign);
    printf("Exponent: ");
    int expobit[11]={0},fracbit[52]={0};
    uint16_t tmp1 = mydouble.bit.expo;
    int i = 0;
    while(tmp1 >= 1){
        expobit[i] = tmp1%2;
        tmp1/=2;
        i++;
    }
    for(i=10; i>=0; i--){
        printf("%d",expobit[i]);
    }
    i=0;
    printf("\nFraction: ");
    uint64_t tmp2 = mydouble.bit.frac;
    while(tmp2 >= 1){
        fracbit[i] = tmp2%2;
        tmp2/=2;
        i++;
    }
    for(i=51; i>=0; i--){
        printf("%d",fracbit[i]);
    }
    printf("\n");
    printf("%lf = (-1)^%d * (1",mydouble.num,mydouble.bit.sign);
    for(int i=51; i>=0 ;i--){
        if(fracbit[i] == 1){
            printf(" + 2^%d",(51-i+1)*-1);
        }
    }
    printf(") * 2^(%d-1023)\n",mydouble.bit.expo);
}