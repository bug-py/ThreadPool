#include "queue.h"
#include "alloc.h"

#include <stdlib.h>
#include <string.h>

void QUEUE_init(queue_t* queue,size_t element_size){
        if(!element_size) element_size=1;
        queue->begin=NULL;
        queue->end=NULL;
        queue->length=0;
        queue->element_size=element_size;
}
void QUEUE_push(queue_t* queue,void* element){
    node_t* node=safe_alloc(sizeof(node_t)+queue->element_size,1,NULL);
    node->next=NULL;
    memcpy(node->element,element,queue->element_size);
    if(!queue->length){
        queue->begin=node;
        queue->end=node;
    }else{
        queue->end->next=node;
        queue->end=node;
    }
    queue->length+=1;
}
void QUEUE_pop(queue_t* queue,void* element){
    if(!queue->length) return;
    memcpy(element,queue->begin->element,queue->element_size);
    if(queue->length==1){
        free(queue->begin);
        queue->begin=NULL;
        queue->end=NULL;
    }else{
        node_t* tmp=queue->begin;
        queue->begin=queue->begin->next;
        free(tmp);
    }
    queue->length-=1;
}
void QUEUE_destroy(queue_t* queue){
    node_t* tmp;
    node_t* current=queue->begin;
    while(current!=NULL){
        tmp=current->next;
        free(current);
        current=tmp;
    }
    queue->begin=NULL;
}

size_t QUEUE_length(queue_t* queue){
    return queue->length;
}

 bool QUEUE_empty(queue_t* queue){
    return queue->length==0;
}