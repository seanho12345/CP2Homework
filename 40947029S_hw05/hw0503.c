#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>
#include <getopt.h>

void print_help(){ // print out help info
    printf("Usage: ./hw0503 -q [keyword]\n");
}

int main(int argc,char *argv[]){
    char option;
    char query[100+1] = {0};
    char link[200] = "https://api.birkhoff.me/v1/dblp/";
    if(argc != 3){
        print_help();
        return 0;
    }
    while((option = getopt(argc,argv,"q:")) != -1){
        switch(option){
            case 'q':
                strncpy(query, optarg, 100);
                strncat(link, query, 100);
                break;
            case '?':
                print_help();
                return 0;
                break;
        }
    }
    CURL *curl = curl_easy_init();
    CURLcode res;
    if(curl){
        curl_easy_setopt(curl, CURLOPT_USERAGENT, NULL);
        curl_easy_setopt(curl, CURLOPT_URL, link);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, stdout);
        curl_easy_perform(curl);
        
    }
    curl_easy_cleanup(curl);
}