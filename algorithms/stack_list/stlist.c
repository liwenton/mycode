#include <stdio.h>
#include <stdlib.h>
#include "stlist.h"
/*额外提供创建节点和销毁节点的函数(自用)*/

/*传入久节点，和数据，返回新节点*/
static struct StackNode *creat_node(int data, struct StackNode *next)
{
   struct StackNode *node=malloc(sizeof(struct StackNode));
   node->data=data;
   node->next=next;
   return node;
}

static struct StackNode *destroy_node(struct StackNode *node)
{
   struct StackNode *next=node->next;
   free(node);
   return next;
}

void stack_init(struct Stack *stack)
{
   stack->top=NULL;    
}

void stack_del(struct Stack *stack)  //删除所有的元素
{
/*
   struct StackNode *node=stack->top;
   stack->top=destroy_node(node);
   if(stack->top==NULL)
      return ; 
   else
     stack_del(stack->top);
*/
   while(stack->top)
     stack->top=destroy_node(stack->top);
}

int  stack_empty(struct Stack *stack) //判断是否空
{
   return !stack->top;
}

void stack_push(struct Stack *stack ,int data)
{
   stack->top=creat_node(data ,stack->top);
}

int  stack_pop(struct Stack *stack)
{
   int data=stack->top->data;
   stack->top=destroy_node(stack->top);
   return data;
}

int  stack_top(struct Stack *stack)
{
   return stack->top->data;
}

int  stack_size(struct Stack *stack)
{
   int size=0;
   struct StackNode *node=stack->top;
   while(node)
   {
    size++;
    node=node->next;
   }
   return size;
}
