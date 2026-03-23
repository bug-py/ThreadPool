#include "threadpool.h"
#include "alloc.h"
#include <stdlib.h>
typedef struct{
    size_t id;
    bool* running;
    pthread_mutex_t* lock;
    pthread_cond_t* cond;
    queue_t* queue;
}arg_thread_t;

void* worker(void* thread_arg){
    arg_thread_t* arg=thread_arg;
    while(true){
        task_t current;
        pthread_mutex_lock(arg->lock);
        while(*(arg->running) && QUEUE_empty(arg->queue)){
            pthread_cond_wait(arg->cond,arg->lock);
        }
        
        if(!*(arg->running)){
            pthread_mutex_unlock(arg->lock);
            free(arg);
            return NULL;
        }
        QUEUE_pop(arg->queue,&current);
        pthread_mutex_unlock(arg->lock);
        current.func(arg->id,current.arg);
    }
    

}

void THREADPOOL_init(threadpool_t* threadpool,size_t number_threads){
    if(!number_threads) number_threads=1;
    threadpool->number_threads=number_threads;
    threadpool->running=true;
    pthread_mutex_init(&(threadpool->lock),NULL);
    pthread_cond_init(&(threadpool->cond),NULL);
    QUEUE_init(&(threadpool->queue),sizeof(task_t));
    threadpool->threads=safe_alloc(sizeof(pthread_t),number_threads,NULL);
    for(size_t i=0;i<number_threads;i++){
        arg_thread_t* arg=safe_alloc(sizeof(arg_thread_t),1,NULL);
        arg->id=i;
        arg->running=(&(threadpool->running));
        arg->lock=(&(threadpool->lock));
        arg->cond=(&(threadpool->cond));
        arg->queue=(&(threadpool->queue));
        pthread_create(threadpool->threads+i,NULL,&worker,arg);
    }
}
void THREADPOOL_sumbit(threadpool_t* threadpool,func_thread_t func,void* arg){
    task_t task;
    task.func=func;
    task.arg=arg;
    pthread_mutex_lock(&(threadpool->lock));
    QUEUE_push(&(threadpool->queue),&task);
    pthread_cond_signal(&(threadpool->cond));
    pthread_mutex_unlock(&(threadpool->lock));
}