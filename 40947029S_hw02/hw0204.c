#include <stdio.h>
#include <stdint.h>
#include "bignum.h"

int main(){
    sBigNum a, b;

    set( &a, "1" );
    set( &b, "99" );

    print( a );
    printf("\n");
    print( b );
    printf("\n");

    if( compare( a, b ) == 1 ){
        printf( "Comparison Pass.\n" );
    }
    else{
        printf( "Comparison Fail.\n" );
    }

    if( digits( a ) == 3 ){
        printf( "Digits Pass.\n" );
    }else{
        printf( "Digits Fail.\n" );
    }

    sBigNum ans, q, r;
    printf("ADD: ");
    add( &ans, a, b );
    print( ans );
    printf("\n");

    printf("SUB: ");
    subtract( &ans, a, b );
    print( ans );
    printf("\n");

    printf("MUL: ");
    multiply( &ans, a, b );
    print( ans );
    printf("\n");

    printf("DIV: ");
    divide( &q, &r, a, b );
    print( q );
    printf("...");
    print( r );
    printf("\n");

    printf("POW: ");
    power( &ans, 2, 0 );
    print( ans );
    printf("\n");

    printf("COMBINE: ");
    combine( &ans, 20, 10 );
    print( ans );
    printf("\n");

    return 0;
}