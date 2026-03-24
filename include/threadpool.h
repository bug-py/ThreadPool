#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <pthread.h>
#include "queue.h"
typedef void* (*func_thread_t) (int id,void*);
typedef struct {
    func_thread_t func;
    void* arg;
}task_t;

typedef struct{
    size_t number_threads;
    pthread_t* threads;
    pthread_mutex_t lock;
    pthread_cond_t cond;
    queue_t queue;
    bool running;
}threadpool_t;

void THREADPOOL_init(threadpool_t* threadpool,size_t numbers_threads);
void THREADPOOL_sumbit(threadpool_t* threadpool,func_thread_t func,void* arg);
void THREADPOOL_destroy(threadpool_t* tp);
#endif