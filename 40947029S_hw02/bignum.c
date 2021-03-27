#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "bignum.h"

const sBigNum num_default = {
    .digits = {0},
    .sign = 1,
    .len = 0
};
void print( const sBigNum num ){
    if(num.len == 0){
        printf("0");
    }else{
        if(num.sign == -1){
            printf("-");
        }
        for(int i=num.len-1; i>=0; i--){
            printf("%d",num.digits[i]);
        }
    }
}
int32_t set( sBigNum *pNum, char *str ){
    int valid = 1;
    int k=0;
    *pNum = num_default;
    for(int i=strlen(str)-1; str>=0; i--){
        if(str[i] == '-'){
            pNum->sign = -1;
        }else{
            if(str[i]>'9' || str[i]<'0'){
                valid = 0;
                break;
            }
            pNum->digits[k] = str[i] - '0';
            k++;
        }
    }
    pNum->len = strlen(str);
    return valid;
}
int32_t compare( const sBigNum num01 , const sBigNum num02 ){
    int cmp = 0;
    if(num01.sign != num02.sign){
        if(num01.sign == 1 && num02.sign == -1){
            cmp = 1;
        }else{
            cmp = -1;
        }
    }else{
        if(num01.len > num02.len){
            cmp = 1;
        }else if(num01.len < num02.len){
            cmp = -1;
        }else{
            for(int i=num01.len; i>=0; i++){
                if(num01.digits[i] != num02.digits[i]){
                    if(num01.digits[i] > num02.digits[i]){
                        cmp = 1;
                    }else{
                        cmp = -1;
                    }
                    break;
                }
            }
            if(num01.sign == -1){
                if(cmp == 1){
                    cmp = -1;
                }else if(cmp == -1){
                    cmp = 1;
                }
            }
        }
    }
    return cmp;
}
int32_t digits( const sBigNum num ){
    return num.len;
}
void add( sBigNum *pResult ,const sBigNum num01 , const sBigNum num02 ){
    *pResult = num_default;
    if(num01.sign == num02.sign){
        if(num01.len >= num02.len){
            pResult->len = num01.len;
        }else if(num02.len >= num01.len){
            pResult->len = num02.len;
        }
        for(int i=0; i < pResult->len; i++){
            int tmp = num01.digits[i] + num02.digits[i] + pResult->digits[i];
            pResult->digits[i] = tmp%10;
            pResult->digits[i+1] = tmp/10;
        }
        if(pResult->digits[pResult->len] != 0){
            pResult->len++;
        }
    }else{
        if(num01.sign == 1){
            sBigNum tmp = num02;
            tmp.sign = 1;
            subtract(pResult,num01,tmp);
        }else{
            sBigNum tmp = num01;
            tmp.sign = 1;
            subtract(pResult,num02,tmp);
        }
    }
}
void subtract( sBigNum *pResult , const sBigNum num01 , const sBigNum num02 ){
    *pResult = num_default;
    if(num01.sign == num02.sign){
        int cmp = compare(num01,num02);
        if(cmp == 1){
            sBigNum tmpnum = num01;
            for(int i=0; i<num01.len; i++){
                int tmp = tmpnum.digits[i] - num02.digits[i];
                if(tmp < 0){
                    tmpnum.digits[i+1]--;
                    tmp += 10;
                }
                pResult->digits[i] = tmp;
            }
            pResult->len = num01.len;
            int i = num01.len;
            while(pResult->digits[i-1] == 0){
                pResult->len--;
                i--;
            }
            //printf("Here\n");
        }else if(cmp == -1){
            sBigNum tmpnum = num02;
            for(int i=0; i<num02.len; i++){
                int tmp = tmpnum.digits[i] - num01.digits[i];
                if(tmp < 0){
                    tmpnum.digits[i+1]--;
                    tmp += 10;
                }
                pResult->digits[i] = tmp;
            }
            pResult->len = num02.len;
            int i = num02.len;
            while(pResult->digits[i-1] == 0){
                pResult->len--;
                i--;
            }
            pResult->sign = -1;
        }
        if(num01.sign == -1 && pResult->len != 0){
            if(pResult->sign == 1){
                pResult->sign = -1;
            }else{
                pResult->sign = 1;
            }
        }
    }else{
        if(num01.sign == 1){            
            sBigNum tmp = num02;
            tmp.sign = 1;
            add(pResult,num01,tmp);
        }else{
            sBigNum tmp = num02;
            tmp.sign = -1;
            add(pResult,num01,tmp);
        }
    }
}
void multiply( sBigNum *pResult , const sBigNum num01 , const sBigNum num02 ){
    *pResult = num_default;
    sBigNum tmpnum02 = num02;
    sBigNum one = num_default;
    one.digits[0] = 1;
    one.len = 1;
    while(tmpnum02.len != 0){
        sBigNum tmpnum = *pResult;
        add(pResult,tmpnum,num01);
        subtract(&tmpnum,tmpnum02,one);
        tmpnum02 = tmpnum;
    }
}
void divide( sBigNum *pQuotient , sBigNum *pRemainder , const sBigNum num01 , const sBigNum num02 ){
    *pQuotient = num_default;
    *pRemainder = num_default;
    sBigNum tmpnum = num_default;
    sBigNum N = num01;
    sBigNum one = num_default;
    one.digits[0] = 1;
    one.len = 1;
    while(compare(N,num02) == 1){
        subtract(&tmpnum,N,num02);
        N = tmpnum;
        add(&tmpnum,*pQuotient,one);
        *pQuotient = tmpnum;
    }
    *pRemainder = N;
}
void power( sBigNum *pResult , int32_t n, int32_t k ){
    *pResult = num_default;
    if(k == 0){
        pResult->len = 1;
        pResult->digits[0] = 1;
    }else{
        sBigNum n_big = num_default;
        int tmp = n;
        if(n<0){
            n_big.sign = -1;
        }
        while(tmp != 0){
            n_big.digits[n_big.len] = tmp % 10;
            tmp /= 10;
            n_big.len++;
        }
        sBigNum tmpnum;
        *pResult = n_big;
        k--;
        while(k--){
            multiply(&tmpnum,*pResult,n_big);
            *pResult = tmpnum;
        }
    }
}
int32_t c(int32_t n,int32_t k){
    if(k == 0 || n == k){
        return 1;
    }else{
        return c(n-1,k-1) + c(n-1,k);
    }
}

void combine( sBigNum *pResult , int32_t n, int32_t k ){
    *pResult = num_default;
    int64_t ans = c(n,k);
    while(ans != 0){
        pResult->digits[pResult->len] = ans % 10;
        ans /= 10;
        pResult->len++;
    }
}