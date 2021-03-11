#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "mystring.h"

int main()
{
    const char  *str = "I have an apple.";

    int c = 'a';

    printf( "str: \"%s\"\n", str );
    printf( "strchr( str, c ) = %s\n", mystrchr( str, c ) );
    printf( "strchr( str, c ) = %s\n", strchr( str, c ) );
    printf( "location is %d\n", mystrchr( str, c ) - str );
    printf( "location is %d\n", strchr( str, c ) - str );
    printf( "strrchr( str, c ) = %s\n", mystrrchr( str, c ) );
    printf( "strrchr( str, c ) = %s\n", strrchr( str, c ) );
    printf( "location is %d\n", mystrrchr( str, c ) - str );
    printf( "location is %d\n", strrchr( str, c ) - str );

    printf( "\n" );

    const char  *str2 = "the value of pi is 3.14";
    const char  *accept = "abcdefghijklmnopqrstuvwxyz";
    const char  *reject = "0123456789";
    const char  *accept2 = "abc";

    printf( "str2: \"%s\"\n", str2 );
    printf( "accept: \"%s\"\n", accept );
    printf( "reject: \"%s\"\n", reject );
    printf( "accept2: \"%s\"\n", accept2 );

    printf( "strspn( str2, accept ) = %d\n", mystrspn( str2, accept ) );
    printf( "strspn( str2, accept ) = %d\n", strspn( str2, accept ) );
    printf( "strcspn( str2, reject ) = %d\n", mystrcspn( str2, reject ) );
    printf( "strcspn( str2, reject ) = %d\n", strcspn( str2, reject ) );
    printf( "strpbrk( str2, accept2 ) = %c, which is in %d\n", *( mystrpbrk( str2, accept2 ) ), mystrpbrk( str2, accept2 ) - str2 );
    printf( "strpbrk( str2, accept2 ) = %c, which is in %d\n", *( strpbrk( str2, accept2 ) ), strpbrk( str2, accept2 ) - str2 );

    printf( "\n" );

    const char  *needle = "pi";

    printf( "needle: \"%s\"\n", needle );
    printf( "strstr( str2, needle ): %s\n", mystrstr( str2, needle ) );
    printf( "strstr( str2, needle ): %s\n", strstr( str2, needle ) );
    printf( "\n" );

    char    str3[] = "the value of pi is 3.14";
    char    *token = mystrtok( str3, " " );
    int32_t i = 0;

    while( token != NULL )
    {
        printf( "%d: %s\n", i, token );
        token = mystrtok( NULL, " " );
        i++;
    }
    char    str4[] = "the value of pi is 3.14";
    char    *token2 = strtok( str4, " " );
    i = 0;
    while( token2 != NULL )
    {
        printf( "%d: %s\n", i, token2 );
        token2 = strtok( NULL, " " );
        i++;
    }

    return 0;
}