#include "queue.h"
#include "alloc.h"

#include <stdlib.h>

void QUEUE_init(queue_t* queue,size_t element_size,size_t init_capacity){
        if(!init_size) init_size=1;
        if(!element_size) element_size=1;
        queue->array=safe_alloc(element_size,init_size,NULL);
        queue->capacity=init_size;
        queue->length=0;
        queue->element_size=element_size;
}



void QUEUE_destroy(queue_t* queue){
    if(queue->array!=NULL){
        free(queue->array);
    }
}