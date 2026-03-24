#include "threadpool.h"
#include <stdio.h>
#include <unistd.h>
void* print(int id,void* arg){
    printf("i am Thread %i\n",id);
    return arg;
}
int main(){
    threadpool_t tp;
    THREADPOOL_init(&tp,5);
    THREADPOOL_sumbit(&tp,&print,NULL);
    THREADPOOL_sumbit(&tp,&print,NULL);
    THREADPOOL_sumbit(&tp,&print,NULL);
    THREADPOOL_sumbit(&tp,&print,NULL);
    THREADPOOL_sumbit(&tp,&print,NULL);
    THREADPOOL_sumbit(&tp,&print,NULL);
    THREADPOOL_sumbit(&tp,&print,NULL);
    THREADPOOL_sumbit(&tp,&print,NULL);
    THREADPOOL_sumbit(&tp,&print,NULL);
    THREADPOOL_sumbit(&tp,&print,NULL);
    THREADPOOL_sumbit(&tp,&print,NULL);
    THREADPOOL_sumbit(&tp,&print,NULL);
    sleep(2);
    THREADPOOL_destroy(&tp);
    return 0;
}