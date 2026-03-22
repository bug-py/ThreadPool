#ifndef QUEUE_H
#define QUEUE_H
#include <stddef.h>
#include <stdbool.h>
typedef struct node node_t;
typedef struct{
    char* array;
    size_t length;
    size_t element_size;
    node_t* begin;
    node_t* end;
}queue_t;

struct node{
    node_t*  next;
    char element[];
};

void QUEUE_init(queue_t* queue,size_t element_size);
void QUEUE_push(queue_t* queue,void* element);
void QUEUE_pop(queue_t* queue,void* element);
void QUEUE_destroy(queue_t* queue);
size_t QUEUE_length(queue_t* queue);
bool QUEUE_empty(queue_t* queue);
#endif