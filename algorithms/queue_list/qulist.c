#include <stdio.h>
#include <stdlib.h>
#include "qulist.h"

QueueNode *CreatNode(int data)
{
   QueueNode *node=malloc(sizeof(QueueNode));
   node->data=data;
   node->next=NULL;

   return node;
}

QueueNode *DestroyNode(QueueNode *node)
{
   QueueNode *next=node->next;
   free(node);

   return next;  
}

void QueueInit(Queue *queue)
{
   queue->front=NULL;
   queue->rear=NULL;
}

void QueueDel(Queue *queue)
{
   while(queue->front)
   {
     queue->front=DestroyNode(queue->front);
     queue->rear=NULL;
   }
}

int QueueEmpty(Queue *queue)
{
   return (!queue->front) && (!queue->rear);
}


void QueuePush(int data, Queue *queue)
{
   QueueNode *node= CreatNode(data);

   	if(queue->rear)
	{
     	queue->rear->next=node; //改原来队尾的next
		queue->rear=node;
	}
   	else
   	{
     queue->front=node;
     queue->rear=node;
	}
   
}

int QueuePop (Queue *queue)
{  
	int data= queue->front->data;
//	QueueNode *node=queue->front;
	queue->front=DestroyNode(queue->front);

    if(!queue->front)
	{
		queue->rear=NULL;
	}

	return data;     
}

int QueueTop(Queue *queue)
{
    return queue->front->data;
}

int	QueueSize(Queue *queue)
{
    int size=0;
    QueueNode *node;
    for(node=queue->front;node;node=node->next)
    {
      	size++;
    }
}
 
