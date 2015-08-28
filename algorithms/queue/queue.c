#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void queue_init(Queue *queue, int cap)
{
   queue->arr = (int *)malloc((sizeof(int)*cap));
   queue->cap = cap;
   queue->front = 0;
   queue->rear = 0;
   queue->size = 0;
}

void queue_del(Queue *queue)
{
   free(queue->arr);
   queue->arr  = NULL;
   queue->cap  = 0;
   queue->front = 0;
   queue->rear = 0;
   queue->size = 0;
}

int  queue_full(Queue *queue)
{
   return queue->size >= queue->cap;
}

int  queue_empty(Queue *queue)
{
   return !queue->size;
}

void queue_push(int data, Queue *queue)
{
    if(queue->rear >= queue->cap)
      queue->rear = 0;
    queue->size++;
    queue->arr[queue->rear++]=data;
}

int  queue_pop(Queue *queue)
{
    if(queue->front >= queue->cap)
       queue->front = 0;
    queue->size--;
    return queue->arr[queue->front++];
}

int  queue_front(Queue *queue)
{
    if(queue->front >= queue->cap)
       queue->front = 0;
    return queue->arr[queue->front];
}
int  queue_size(Queue *queue)
{
   return queue->size;
}
