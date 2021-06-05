#ifndef B64_H
#define B64_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define i32 int32_t
#define u32 int32_t
#define u8 uint8_t

#define b1 63 //00111111
#define b2 48 //00110000
#define b3 15 //00001111
#define b4 60 //00111100
#define b5 3  //00000011

#define o1 252 //11111100
#define o2 3   //00000011
#define o3 240 //11110000
#define o4 15  //00001111
#define o5 192 //11000000
#define o6 63  //00111111

#define B64_SYNTAX_ERROR        1
#define B64_FILE_ERROR          2
#define B64_FILE_IO_ERROR       3
#define B64_ERROR_OUT_CLOSE     4
#define B64_LINE_SIZE_TO_MIN    5
#define B64_SYNTAX_TOOMANYARGS  6

#define B64_MAX_MESSAGES 7
static char *b64_msgs[ B64_MAX_MESSAGES ] = {
            "b64:000:Invalid Message Code.",
            "b64:001:Syntax Error -- check help (-h) for usage.",
            "b64:002:File Error Opening/Creating Files.",
            "b64:003:File I/O Error -- Note: output file not removed.",
            "b64:004:Error on output file close.",
            "b64:005:linesize set to minimum.",
            "b64:006:Syntax: Too many arguments."
};

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/', '='};


static const char cb64[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char cd64[]="|$$$}rstuvwxyz{$$$$$$$>?@ABCDEFGHIJKLMNOPQRSTUVW$$$$$$XYZ[\\]^_`abcdefghijklmnopq";
#define b64_message( ec ) ((ec > 0 && ec < B64_MAX_MESSAGES ) ? b64_msgs[ ec ] : b64_msgs[ 0 ])

static void encodeblock( unsigned char *in, unsigned char *out, int len )
{
    out[0] = (unsigned char) cb64[ (int)(in[0] >> 2) ];
    out[1] = (unsigned char) cb64[ (int)(((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4)) ];
    out[2] = (unsigned char) (len > 1 ? cb64[ (int)(((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6)) ] : '=');
    out[3] = (unsigned char) (len > 2 ? cb64[ (int)(in[2] & 0x3f) ] : '=');
}
static int txtencode( FILE *infile, FILE *outfile)
{
    int linesize = 72;
    unsigned char in[3];
    unsigned char out[4];
    int i, len, blocksout = 0;
    int retcode = 0;

    *in = (unsigned char) 0;
    *out = (unsigned char) 0;
    while( feof( infile ) == 0 ) {
        len = 0;
        for( i = 0; i < 3; i++ ) {
            in[i] = (unsigned char) getc( infile );

            if( feof( infile ) == 0 ) {
                len++;
            }
            else {
                in[i] = (unsigned char) 0;
            }
        }
        if( len > 0 ) {
            encodeblock( in, out, len );
            for( i = 0; i < 4; i++ ) {
                if( putc( (int)(out[i]), outfile ) == 0 ){
                    if( ferror( outfile ) != 0 )      {
                        perror( b64_message( B64_FILE_IO_ERROR ) );
                        retcode = B64_FILE_IO_ERROR;
                    }
                    break;
                }
            }
            blocksout++;
        }
        if( blocksout >= (linesize/4) || feof( infile ) != 0 ) {
            if( blocksout > 0 ) {
                fprintf( outfile, "\r\n" );
            }
            blocksout = 0;
        }
    }
    return( retcode );
}

static void decodeblock( unsigned char *in, unsigned char *out )
{   
    out[ 0 ] = (unsigned char ) (in[0] << 2 | in[1] >> 4);
    out[ 1 ] = (unsigned char ) (in[1] << 4 | in[2] >> 2);
    out[ 2 ] = (unsigned char ) (((in[2] << 6) & 0xc0) | in[3]);
}

static int decode( FILE *infile, FILE *outfile )
{
    int retcode = 0;
    unsigned char in[4];
    unsigned char out[3];
    int v;
    int i, len;

    *in = (unsigned char) 0;
    *out = (unsigned char) 0;
    while( feof( infile ) == 0 ) {
        for( len = 0, i = 0; i < 4 && feof( infile ) == 0; i++ ) {
            v = 0;
            while( feof( infile ) == 0 && v == 0 ) {
                v = getc( infile );
                if( v != EOF ) {
                    v = ((v < 43 || v > 122) ? 0 : (int) cd64[ v - 43 ]);
                    if( v != 0 ) {
                        v = ((v == (int)'$') ? 0 : v - 61);
                    }
                }
            }
            if( feof( infile ) == 0 ) {
                len++;
                if( v != 0 ) {
                    in[ i ] = (unsigned char) (v - 1);
                }
            }
            else {
                in[i] = (unsigned char) 0;
            }
        }
        if( len > 0 ) {
            decodeblock( in, out );
            for( i = 0; i < len - 1; i++ ) {
                if( putc( (int) out[i], outfile ) == 0 ){
                    if( ferror( outfile ) != 0 )      {
                        perror( b64_message( B64_FILE_IO_ERROR ) );
                        retcode = B64_FILE_IO_ERROR;
                    }
                    break;
                }
            }
        }
    }
    return( retcode );
}

void bmpencrypt(FILE *input, FILE *output)
{
    while (1)
    {
        uint8_t read[3] = {0};
        u8 cnt = fread(read, sizeof(u8), 3, input);
        if (feof(input))
            break;
        uint8_t bit[4] = {0};
        if (cnt == 3)
        {
            bit[0] = (read[0] >> 2) & b1;
            bit[1] = (((read[0] << 4) & b2) | ((read[1] >> 4) & b3));
            bit[2] = (((read[1] << 2) & b4) | ((read[2] >> 6) & b5));
            bit[3] = ((read[2]) & b1); //00010110 22
        }
        else if (cnt == 2)
        {
            bit[0] = (read[0] >> 2) & b1;
            bit[1] = (((read[0] << 4) & b2) | ((read[1] >> 4) & b3));
            bit[2] = (((read[1] << 2) & b4) | ((read[2] >> 6) & b5));
            bit[3] = 64;
        }
        else if (cnt == 1)
        {
            bit[0] = (read[0] >> 2) & b1;
            bit[1] = (((read[0] << 4) & b2) | ((read[1] >> 4) & b3));
            bit[2] = 64;
            bit[3] = 64;
        }
        char a[5] = {encoding_table[bit[0]], encoding_table[bit[1]], encoding_table[bit[2]], encoding_table[bit[3]]};
        fwrite(a, sizeof(u8), strlen(a), output);
    }
    fclose(input);
    fclose(output);
    return;
}
void decrypt(FILE *input, FILE *output)
{
    while (1)
    {
        uint8_t read[4] = {0};

        u8 cnt = fread(read, sizeof(u8), 4, input);
        if (feof(input))
            break;
        uint8_t outs[4] = {0};
        char result[3] = {0};
        i32 index = 0;
        for (i32 i = 0; i < cnt; i++)
        {
            for (i32 j = 0; j < 65; j++)
            {
                if (read[i] == encoding_table[j])
                {
                    outs[index] = j;
                    if(outs[index] == 64)
                        outs[index] = 0;
                    index++;
                    break;
                }
            }
        }
        result[0] = ((outs[0] << 2) & o1) | ((outs[1] >> 4) & o2);
        result[1] = ((outs[1] << 4) & o3) | ((outs[2] >> 2) & o4);
        result[2] = ((outs[2] << 6) & o5) | ((outs[3]) & o6);
        //printf("%d %d %d\n", result[0], result[1], result[2]);
        fwrite(result, 1,sizeof(result), output);
    }
    fclose(output);
    fclose(input);
    return;
}

#endif