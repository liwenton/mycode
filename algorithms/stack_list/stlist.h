#ifndef STLIST_H
#define STLIST_H
#include <sys/types.h>

struct StackNode{
  int data;
  struct StackNode* next;  //指向下个节点
};

struct Stack{            //堆栈结构
  struct StackNode* top; //栈顶节点指针
};

void stack_init(struct Stack *stack); //初始化空堆栈
void stack_del(struct Stack *stack);  //删除所有的元素
int  stack_empty(struct Stack *stack); //判断是否空
void stack_push(struct Stack *stack ,int data);
int  stack_pop(struct Stack *stack);
int  stack_top(struct Stack *stack);
int  stack_size(struct Stack *stack);

#endif
