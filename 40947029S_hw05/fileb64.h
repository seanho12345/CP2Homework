#ifndef FILEB64_H
#define FILEB64_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/', '='};

void encrypt(FILE *input, FILE *output)
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