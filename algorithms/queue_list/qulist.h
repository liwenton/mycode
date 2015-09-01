#ifndef __QULIST_H__
#define __QULIST_H__

typedef struct QUEUENODE{
   int data;
   struct QUEUENODE *next;
}QueueNode;

typedef struct QUEUE{
   QueueNode *front;
   QueueNode *rear;
}Queue;

QueueNode *CreatNode(int data);
QueueNode *DestroyNode(QueueNode *node);
void QueueInit(Queue *queue);
void QueueDel(Queue *queue);
int  QueueEmpty(Queue *queue);
void QueuePush(int data, Queue *queue);
int QueuePop (Queue *queue);
int QueueTop(Queue *queue);
int QueueSize(Queue *queue);


#endif
