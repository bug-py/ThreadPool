#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <pthread.h>
#include "queue.h"
typedef void* (*func_thread_t) (int id,void*);
typedef enum{
    FUNC_FINISH=0,
    FUNC_RUN,
    FUNC_WAIT
}state_func_t;
typedef struct{
    pthread_cond_t cond;
    pthread_mutex_t lock;
    state_func_t state;
    void* result;
}futur_t;

typedef struct{
    size_t number_threads;
    size_t worker;
    pthread_t* threads;
    pthread_mutex_t lock;
    pthread_cond_t cond;
    pthread_cond_t empty;
    queue_t queue;
    bool running;
}threadpool_t;

void THREADPOOL_init(threadpool_t* tp,size_t numbers_threads);
futur_t* THREADPOOL_submit(threadpool_t* tp,func_thread_t func,void* arg,bool get_futur);
void THREADPOOL_wait(threadpool_t* tp);
void THREADPOOL_destroy(threadpool_t* tp);

state_func_t FUTUR_state(futur_t* futur);
void* FUTUR_get(futur_t* futur);
void FUTUR_destroy(futur_t* futur);
#endif