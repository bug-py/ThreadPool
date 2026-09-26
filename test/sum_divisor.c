#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <threadpool.h>
#include <time.h>
#define NUMBER_CORE 8
#define SEC_TO_NSEC 10e9
size_t sum_divisor(size_t number){
    size_t sum =number;
    for(size_t divisor=1;divisor<number;divisor++){
        if(number%divisor==0) {
            sum+=divisor;
        }
    }
    return sum;
}

void* wrapper_sum_divisor(int id,void* arg){
    long long unsigned int number=*(size_t*)arg;
    long long unsigned int sum=sum_divisor(number);
    printf("THREAD : %i | NUMBER : %llu | SUM DIVISOR: %llu\n",id,number,sum);
    return NULL;
}
void single_thread(size_t* array,size_t len){
    for(size_t i=0;i<len;i++){
      long long unsigned int number=array[i];
      long long unsigned int sum=sum_divisor(number);
      printf("THREAD : 0 | NUMBER : %llu | SUM DIVISOR: %llu\n",number,sum);
    }
}
void multi_thread(size_t* array,size_t len){
    threadpool_t tp;
    THREADPOOL_init(&tp,NUMBER_CORE);
    for(size_t i=0;i<len;i++){
          THREADPOOL_submit(&tp,&wrapper_sum_divisor,&(array[i]),NULL);
    }
    THREADPOOL_wait(&tp);
    THREADPOOL_destroy(&tp);
}
double get_diff_sec(struct timespec* begin,struct timespec* end){
    double begin_sec=(double)begin->tv_sec+(double)begin->tv_nsec/SEC_TO_NSEC;
    double end_sec=(double)end->tv_sec+(double)end->tv_nsec/SEC_TO_NSEC;
    return end_sec-begin_sec;
}
int main(){
    size_t numbers[]={54555565,44555655,74959984,95621677,94959988,97678423,41279822,46786989,12345678,98765432};
    struct timespec begin;
    struct timespec end;
    printf("SINGLE THREAD :\n");
    clock_gettime(CLOCK_MONOTONIC,&begin);
    single_thread(numbers,sizeof(numbers)/sizeof(size_t));
    clock_gettime(CLOCK_MONOTONIC,&end);
    printf("execution time : %.9f\n",get_diff_sec(&begin,&end));

    printf("MULTI THREAD :\n");
    clock_gettime(CLOCK_MONOTONIC,&begin);
    multi_thread(numbers,sizeof(numbers)/sizeof(size_t));
    clock_gettime(CLOCK_MONOTONIC,&end);
    printf("execution time : %.9f\n",get_diff_sec(&begin,&end));
   
}