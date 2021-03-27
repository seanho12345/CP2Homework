#ifndef BIGNUM_H
#define BIGNUM_H

#include <stdint.h>

typedef struct _sBigNum{
    int digits[100];
    int sign;
    int len;
}sBigNum;

void print( const sBigNum num );
int32_t set( sBigNum *pNum, char *str );
int32_t compare( const sBigNum num01 , const sBigNum num02 );
int32_t digits( const sBigNum num );
void add( sBigNum *pResult ,const sBigNum num01 , const sBigNum num02 );
void subtract( sBigNum *pResult , const sBigNum num01 , const sBigNum num02 );
void multiply( sBigNum *pResult , const sBigNum num01 , const sBigNum num02 );
void divide( sBigNum *pQuotient , sBigNum *pRemainder , const sBigNum num01 , const sBigNum num02 );
void power( sBigNum *pResult , int32_t n, int32_t k );
void combine( sBigNum *pResult , int32_t n, int32_t k );

#endif