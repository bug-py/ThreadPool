#ifndef QUEUE_H
#define QUEUE_H
#include <stddef.h>
typedef struct{
    char* array;
    size_t length;
    size_t capacity;
    size_t element_size;
}queue_t;

void QUEUE_init(queue_t* queue,size_t element_size,size_t init_capacity);
void QUEUE_destroy(queue_t* queue);
#endif