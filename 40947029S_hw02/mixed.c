#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "mixed.h"

int gcd(int m, int n) {
    while(n != 0) { 
        int r = m % n; 
        m = n; 
        n = r; 
    } 
    return m;
}

int lcm(int m, int n) {
    return m * n / gcd(m, n);
}

int convert(const sMixednumber mn){
    int32_t num;
    if(mn.wholenum < 0){
        num = mn.wholenum*mn.denom - mn.numer;
    }else{
        num = mn.wholenum*mn.denom + mn.numer;
    }
    return num;
}

int mixed_set( sMixednumber *num, int32_t a, int32_t b,int32_t c){
    int valid = 0;
    if(b>c || (a==0 && b<0) || c == 0){
        valid = -1;
    }else{
        num->wholenum = a;
        num->numer = b;
        num->denom = c;
    }
    return valid;
}
// return -1 if invalid; otherwise , return 0.
void mixed_print( const sMixednumber num){
    printf("(%d,%d,%d)",num.wholenum,num.numer,num.denom);
}
// in the form of (a,b,c)
void mixed_add( sMixednumber *num, const sMixednumber mn1,const sMixednumber mn2){
    int32_t wnum1 = convert(mn1),wnum2 = convert(mn2);
    if(mn1.denom == mn2.denom){
        num->denom = mn1.denom;
    }else{
        num->denom = lcm(mn1.denom,mn2.denom);
        wnum1 *= num->denom / mn1.denom;
        wnum2 *= num->denom / mn2.denom;
    }
    num->wholenum = (wnum1+wnum2) / num->denom;
    num->numer = (wnum1+wnum2) % num->denom;
    if(num->wholenum == 0 && (wnum1-wnum2<0)){
        num->numer *= -1;
    }
    if(num->numer == 0){
        num->denom  = 0;
    }
}
// pNumber = r1 + r2
void mixed_sub( sMixednumber *num, const sMixednumber mn1,const sMixednumber mn2){
    int32_t wnum1 = convert(mn1),wnum2 = convert(mn2);
    if(mn1.denom == mn2.denom){
        num->denom = mn1.denom;
    }else{
        num->denom = lcm(mn1.denom,mn2.denom);
        wnum1 *= num->denom / mn1.denom;
        wnum2 *= num->denom / mn2.denom;
    }
    num->numer = abs(wnum1-wnum2) % num->denom;
    num->wholenum = (wnum1-wnum2) / num->denom;
    if(num->wholenum == 0 && (wnum1-wnum2<0)){
        num->numer *= -1;
    }
    if(num->numer == 0){
        num->denom  = 0;
    }
}
// pNumber = r1 - r2
void mixed_mul( sMixednumber *num, const sMixednumber mn1,const sMixednumber mn2){
    int32_t wnum1 = convert(mn1),wnum2 = convert(mn2);
    int32_t mygcd;
    num->numer = wnum1 * wnum2;
    num->denom = mn1.denom * mn2.denom;
    mygcd = gcd(num->numer,num->denom);
    num->numer /= mygcd;
    num->denom /= mygcd;
    num->wholenum = num->numer / num->denom;
    num->numer = abs(num->numer) % num->denom;
    if(num->wholenum == 0 && (wnum1-wnum2<0)){
        num->numer *= -1;
    }
    if(num->numer == 0){
        num->denom  = 0;
    }
}
// pNumber = r1 * r2
void mixed_div( sMixednumber *num, const sMixednumber mn1,const sMixednumber mn2){
    int32_t wnum2 = convert(mn2);
    sMixednumber swaped = {
        .numer = mn2.denom,
        .denom = wnum2,
        .wholenum = 0
    };
    mixed_mul(num,mn1,swaped);
}
// pNumber = r1 / r2
