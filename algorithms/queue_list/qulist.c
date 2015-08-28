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

static QueueList *destroy_node(QueueList *node)
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
   {
     queue->front=destroy_node(queue->front);
     queue->rear=NULL;
   }
}

int  queue_empty(Queue *queue)
{
   return (!queue->front) && (!queue->rear);
}
void queue_push(int data, Queue *queue)
{
   QueueNode *node=create_node(data);
   if(queue->rear)
     queue->rear->next=node; //改原来队尾的next

   else
     queue->front=node;
     queue->rear=node;
   
}

int queue_pop (Queue *queue);
{  
     int data= queue->front->data;
    // QueueNode *node=queue->front;
     queue->front=destroy_node(queue->front);
     if(!queue->front)
       queue->rear=NULL;
     return data;     
}
int  queue_top (Queue *queue)
{
    return queue->front->data;
}

int  queue_size(List *list)
{
    int size=0;
    QueueNode *node;
    for(node=queue->front;node;node=node->next)
    {
      size++;
    }
}
}
 
