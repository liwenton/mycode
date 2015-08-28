#include <stdio.h>
#include <stdlib.h>
#include "qulist.h"

static QueueNode *creat_node(int data)
{
   QueueNode *node=malloc(sizeof(QueueNode));
   node->data=data;
   node->next=NULL;
  
   return node;
}

static QueueNode *destroy_node(QueueNode *node)
{
   QueueNode *next=node->next;
   free(node);

   return next;
}

void queue_init(Queue *queue)
{
   queue->front=NULL;
   queue->rear=NULL;
}

void queue_del (Queue *queue)
{
   while(queue->front)
    queue->front=destory_node(queue->front);
  
    queue->rear=NULL;
}
int  queue_empty(Queue *queue)
{
}
void queue_push(Queue *queue)
{
    
}
void queue_pop (Queue *queue)
int  queue_top (Queue *queue)
int  queue_size(Queue *queue)

