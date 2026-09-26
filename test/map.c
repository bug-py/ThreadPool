#include "threadpool.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
bool IsPrime(size_t number){
    if(number==1 || !number) return false;
    for(size_t divisor=2;divisor<number;divisor++){
        if(number%divisor==0) return false;
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

void* wrapper(int id,void* arg){
    return (void*)IsPrime(*(size_t*)arg);
}

bool* parallel_map(size_t* array,size_t len){
    threadpool_t tp;
    futur_t** futurs=malloc(sizeof(futur_t*)*len);
    bool* result=malloc(sizeof(bool)*len);
    THREADPOOL_init(&tp,8);
    for(size_t i=0;i<len;i++){
        futurs[i]=THREADPOOL_submit(&tp,&wrapper,array+i,true);
    }
    THREADPOOL_wait(&tp);
    for(size_t i=0;i<len;i++){
        result[i]=(bool)FUTUR_get(futurs[i]);
        FUTUR_destroy(futurs[i]);
    }
    free(futurs);
    THREADPOOL_destroy(&tp);
    return result;
}

void show(bool* array,size_t len){
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





int main(){
    size_t array[]={2147483648,2147483579,47554554,245745,455545887};
    size_t len=sizeof(array)/sizeof(size_t);
    printf("%lu\n",sizeof(threadpool_t));
    time_t begin;
    bool* result;
    begin=time(NULL);
    result=map(array,len);
    printf("Map mono-thread executed in %lu s \n",(unsigned long)difftime(time(NULL),begin));
    show(result,len);
    free(result);
    begin=time(NULL);
    result=parallel_map(array,len);
    printf("Map multi-thread executed in %lu s \n",(unsigned long)difftime(time(NULL),begin));
    show(result,len);
    free(result);

    
    
}

