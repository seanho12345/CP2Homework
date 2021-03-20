#include <stdio.h>
#include <stdlib.h>
typedef union{
    struct {
        unsigned char b1:1;
        unsigned char b2:1;
        unsigned char b3:1;
        unsigned char b4:1;
        unsigned char b5:1;
        unsigned char b6:1;
        unsigned char b7:1;
        unsigned char b8:1;
    } bits;
    unsigned char byte;
} uByte;

int main(){
    uByte data;
    printf("Please enter a byte (0~255): ");
    scanf("%d",&data.byte);
    printf("Data: %d %d%d%d%d%d%d%d%d\n",data.byte,data.bits.b8,data.bits.b7,data.bits.b6,data.bits.b5,data.bits.b4,data.bits.b3,data.bits.b2,data.bits.b1);
    while(1){
        int pos;
        printf("Flip bit (1-8, 0:exit): ");
        scanf("%d",&pos);
        if(pos == 0){
            printf("Bye\n");
            break;
        }else if(pos == 1){
            data.bits.b8 = !data.bits.b8;
        }else if(pos == 2){
            data.bits.b7 = !data.bits.b7;
        }else if(pos == 3){
            data.bits.b6 = !data.bits.b6;
        }else if(pos == 4){
            data.bits.b5 = !data.bits.b5;
        }else if(pos == 5){
            data.bits.b4 = !data.bits.b4;
        }else if(pos == 6){
            data.bits.b3 = !data.bits.b3;
        }else if(pos == 7){
            data.bits.b2 = !data.bits.b2;
        }else if(pos == 8){
            data.bits.b1 = !data.bits.b1;
        }
        
        printf("Data: %d %d%d%d%d%d%d%d%d\n",data.byte,data.bits.b8,data.bits.b7,data.bits.b6,data.bits.b5,data.bits.b4,data.bits.b3,data.bits.b2,data.bits.b1);
    }
}