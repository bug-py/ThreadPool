#include "queue.h"
#include "alloc.h"
#include <stdio.h>

int main(){
    queue_t queue;
    QUEUE_init(&queue,sizeof(int));
    int number=-45454;
    QUEUE_push(&queue,&number);
    number=9;
    QUEUE_push(&queue,&number);
    number=-1825;
    QUEUE_push(&queue,&number);
    number=67;
    QUEUE_push(&queue,&number);
    int result;
    QUEUE_pop(&queue,&result);
    printf("%i ",result);
    QUEUE_pop(&queue,&result);
    printf("%i ",result);
    QUEUE_pop(&queue,&result);
    printf("%i ",result);
    QUEUE_pop(&queue,&result);
    printf("%i ",result);
    return 0;
}