#ifndef MIXED_H
#define MIXED_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct _sMixednumber{
    int32_t wholenum;
    int32_t numer;
    int32_t denom;
}sMixednumber;

int mixed_set( sMixednumber *, int32_t , int32_t ,int32_t );
// return -1 if invalid; otherwise , return 0.
void mixed_print( const sMixednumber);
// in the form of (a,b,c)
void mixed_add( sMixednumber *, const sMixednumber ,const sMixednumber );
// pNumber = r1 + r2
void mixed_sub( sMixednumber *, const sMixednumber ,const sMixednumber );
// pNumber = r1 - r2
void mixed_mul( sMixednumber *, const sMixednumber ,const sMixednumber );
// pNumber = r1 * r2
void mixed_div( sMixednumber *, const sMixednumber ,const sMixednumber );
// pNumber = r1 / r2

#endif