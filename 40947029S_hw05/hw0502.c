#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

typedef struct _cpustat{
    uint64_t user,nice,system,idle,iowait,irq,softirq,stead,guest;
}cpustat;

void readstat(uint64_t *total,uint64_t *idle){
    FILE *fptr = fopen("/proc/stat","r");
    cpustat stat;
    if(fptr == NULL){
        printf("Failed to read stat");
        exit(0);
    }
    char buff[200]={0};
    while(fgets(buff, 200, fptr)){
        if(strstr(buff,"cpu")){
            sscanf(buff,"cpu %Lu %Lu %Lu %Lu %Lu %Lu %Lu %Lu", 
            &stat.user, &stat.nice, &stat.system, &stat.idle, &stat.iowait, &stat.irq, &stat.softirq, &stat.stead, &stat.guest);
            break;
        }
    }
    *total = stat.user + stat.nice + stat.system + stat.idle + stat.iowait + stat.irq + stat.softirq + stat.stead + stat.guest;
    *idle = stat.idle;
}

int main(){
    while(1){
        uint64_t lasttotal = 0, lastidle = 0;
        uint64_t total,idle;
        readstat(&total, &idle);
        double usage;
        usage = 100 - (idle - lastidle) * 100.0 / (total - lasttotal);
        //printf("total:%Lu, idle:%Lu\n",total,idle);
        printf("CPU usage: %lf%\n",usage);
        lasttotal = total;
        lastidle = idle;
        sleep(1);
    }
    
    
}