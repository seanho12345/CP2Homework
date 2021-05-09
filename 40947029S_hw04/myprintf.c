#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

int myprintf(const char *format, ...){
    va_list valist;
    int len = strlen(format);
    int printcount = 0;
    va_start(valist, format);
    for(int i=0; i<len; i++){
        if(format[i] == '%'){
            i++;
            if(format[i] == 'd' || format[i] == 'i'){
                int argint = va_arg(valist, int);
                char strarr[10] = {0};
                int numlen = 0;
                int neg = 0;
                if(argint < 0){
                    neg = 1;
                }
                argint = abs(argint);
                while(argint != 0){
                    strarr[numlen] = '0' + argint % 10;
                    argint /= 10;
                    numlen++;
                }
                if(numlen == 0){
                    fputc('0', stdout);
                    printcount++;
                }
                if(neg){
                    fputc('-', stdout);
                    printcount++;
                }
                numlen--;
                for(int k=numlen; k>=0; k--){
                    fputc(strarr[k], stdout);
                    printcount++;
                }
            }else if(format[i] == 'x' || format[i] == 'X'){
                int argint = va_arg(valist, int);
                int quotient = argint;
                int remainder;
                char strarr[10] = {0};
                int numlen = 0;
                while(quotient != 0){
                    remainder = quotient % 16;
                    if(quotient < 10){
                        strarr[numlen] = 48 + remainder;
                    }else{
                        strarr[numlen] = 55 + remainder;
                    }
                    quotient /= 16;
                    numlen++;
                }
                for(int k=numlen; k>=0; k--){
                    fputc(strarr[k], stdout);
                    printcount++;
                }
            }else if(format[i] == 's'){
                char *strarr = va_arg(valist, char*);
                for(int k=0; strarr[k] != '\0'; k++){
                    fputc(strarr[k], stdout);
                    printcount++;
                }
            }
        }else{
            fputc(format[i], stdout);
            printcount++;
        }
    }
    va_end(valist);
    return printcount;
}