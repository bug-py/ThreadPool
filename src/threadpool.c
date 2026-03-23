#include "threadpool.h"
void* worker(void* arg){
    return NULL;
}

void THREADPOOL_init(threadpool_t* threadpool,size_t number_threads){
    if(!number_threads) number_threads=1;
    threadpool->number_threads=number_threads;
    threadpool->stop=false;
    threadpool->threads=safe_alloc(sizeof(pthread_t),number_threads,NULL);
    for(size_t i=0;i<number_threads;i++){
        pthread_create(threadpool->threads+i,NULL,&worker,NULL);
    }
    pthread_mutex_init(&(threadpool->lock),NULL);
    pthread_cond_init(&(threadpool->cond),NULL);
    QUEUE_init(&(threadpool->queue),sizeof(task_t));
}
