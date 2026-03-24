#include "threadpool.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print(bool* array,size_t len){
    for(size_t i=0;i<len;i++){
           switch(array[i]){
            case true :
                printf("| TRUE |");
                break;
            case false:
                printf("| FALSE |");
                break;
           }
    }
    putchar('\n');
}

bool IsPrime(size_t number){
    if(number==1) return false;
    size_t other=2;
    while(number>other){
        if(number%other==0) {
            return false;
        }
        other++;
    }
    return true;
}



bool* map(size_t* array,size_t len){
    bool* result=malloc(sizeof(bool)*len);
    for(size_t i=0;i<len;i++){
        result[i]=IsPrime(array[i]);
    }
    return result;
}

void* ParalleIsPrime(int id,void* arg){
    id=id;
    size_t number=*(size_t*)arg;
    if(number==1) return NULL;
    size_t other=2;
    while(number>other){
        if(number%other==0) {
            return NULL;
        }
        other++;
    }
   
    return (void*)1;
}


bool* parallelmap(size_t* array,size_t len){
    threadpool_t tp;
    futur_t* futurs[len];
    bool* result=malloc(sizeof(bool)*len);
    THREADPOOL_init(&tp,8);
    for(size_t i=0;i<len;i++){
       futurs[i]=THREADPOOL_sumbit(&tp,&ParalleIsPrime,array+i,true);
    }
    for(size_t i=0;i<len;i++){
        result[i]=(bool)FUTUR_get(futurs[i]);
        FUTUR_destroy(futurs[i]);
    }
    THREADPOOL_destroy(&tp);
    return result;
}
int main(){
    size_t array[]={2147483647,2147483647,2147483647,2147483647,2147483647,2147483647,2147483647,2147483647,2147483647,2147483647,2147483647};
    size_t len=sizeof(array)/sizeof(size_t);
    bool* result=parallelmap(array,len);
    print(result,len);
    
}