#ifndef QUEUE_H
#define QUEUE_H

typedef struct QUEUE{
  int *arr;   //数组首地址
  int cap;    //长度 
  int front;  //队首（弹出元素)
  int rear;   //队尾（放入元素)
  int size;   //数量
}Queue;

void queue_init(Queue *queue, int cap);
void queue_del(Queue *queue);
int  queue_full(Queue *queue);
int  queue_empty(Queue *queue);
void queue_push(int data, Queue *queue);
int  queue_pop(Queue *queue);
int  queue_front(Queue *queue);
int  queue_size(Queue *queue);

#endif
