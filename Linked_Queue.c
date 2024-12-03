#include "stdlib.h"
#include "stdio.h"


typedef struct LINKED_QUEUE_NODE_s *LINKED_QUEUE_NODE;
typedef struct LINKED_QUEUE_NODE_s{
    LINKED_QUEUE_NODE next;
    int data;
} LINKED_QUEUE_NODE_t[1];

typedef struct LINKED_QUEUE_s *LINKED_QUEUE;
typedef struct LINKED_QUEUE_s{
    LINKED_QUEUE_NODE head;
    LINKED_QUEUE_NODE tail;
} LINKED_QUEUE_t[1];


LINKED_QUEUE linked_queue_init(){
    LINKED_QUEUE queue = malloc(sizeof(LINKED_QUEUE_t));
    queue->tail = NULL;
    queue->head = NULL;
    return queue;
}

void linked_queue_free(LINKED_QUEUE queue){
    free(queue);
}

int linked_queue_is_empty(LINKED_QUEUE queue){
    if(queue->head == NULL || queue->tail == NULL) {
        return 1;
    }else
        return 0;
}

void linked_queue_enqueue(LINKED_QUEUE queue, int data){
    LINKED_QUEUE_NODE temp = malloc(sizeof(LINKED_QUEUE_NODE_t));
    if(temp != NULL){
        temp->data = data;
        temp->next = NULL;
        if(queue->head == NULL){
            queue->head = temp;
        }else{
            queue->tail->next = temp;
        }
        queue->tail = temp;
    }
    else{
        printf("Cannot allocate...");
    }
}

int linked_queue_dequeue(LINKED_QUEUE queue){
    LINKED_QUEUE_NODE top;
    int res = 0;
    top = queue-> head;
    if(top !=NULL){
        if(top == queue ->tail) {
            queue->head = queue->tail = NULL;
        }
        else{
            queue->head = top-> next;
        }
        res = top->data;
        free (top);
    }
    else{
        printf("Error @ linked_queue_dequeue: Queue empty. \n");
    }
    return res;
}
