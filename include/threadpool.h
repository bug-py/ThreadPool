#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include "queue.h"
#include "alloc.h"
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
    bool stop;
}threadpool_t;
void THREADPOOL_init(threadpool_t* threadpool,size_t numbers_threads);
#endif