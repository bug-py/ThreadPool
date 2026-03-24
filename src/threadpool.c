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

void THREADPOOL_init(threadpool_t* tp,size_t number_threads){
    if(!number_threads) number_threads=1;
    tp->number_threads=number_threads;
    tp->running=true;
    pthread_mutex_init(&(tp->lock),NULL);
    pthread_cond_init(&(tp->cond),NULL);
    QUEUE_init(&(tp->queue),sizeof(task_t));
    tp->threads=safe_alloc(sizeof(pthread_t),number_threads,NULL);
    for(size_t i=0;i<number_threads;i++){
        arg_thread_t* arg=safe_alloc(sizeof(arg_thread_t),1,NULL);
        arg->id=i;
        arg->running=(&(tp->running));
        arg->lock=(&(tp->lock));
        arg->cond=(&(tp->cond));
        arg->queue=(&(tp->queue));
        pthread_create(tp->threads+i,NULL,&worker,arg);
    }
}
void THREADPOOL_sumbit(threadpool_t* tp,func_thread_t func,void* arg){
    task_t task;
    task.func=func;
    task.arg=arg;
    pthread_mutex_lock(&(tp->lock));
    QUEUE_push(&(tp->queue),&task);
    pthread_cond_signal(&(tp->cond));
    pthread_mutex_unlock(&(tp->lock));
}

void THREADPOOL_destroy(threadpool_t* tp){
    pthread_mutex_lock(&(tp->lock));
    tp->running=false;
    pthread_cond_broadcast(&(tp->cond));
    pthread_mutex_unlock(&(tp->lock));
    for(size_t i=0;i<tp->number_threads;i++){
        pthread_join(tp->threads[i],NULL);
    }
    free(tp->threads);
    pthread_mutex_destroy(&(tp->lock));
    pthread_cond_destroy(&(tp->cond));
    QUEUE_destroy(&(tp->queue));
}