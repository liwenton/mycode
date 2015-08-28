#ifndef QULIST_H
#define QULIST_H

struct QUEUENODE{
   int data;
   struct QUEUENODE *next;
}QueueNode;

struct QUEUE{
   QueueNode *front;
   QueueNode *rear;
}Queue;


void queue_init(List *list);
void queue_del (List *list);
int  queue_empty(List *list);
void queue_push(List *list);
void queue_pop (List *list);
int  queue_top (List *list);
int  queue_size(List *list);

#endif
