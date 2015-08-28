#include <stdio.h>
#include "stack.h"
int stack_init(struct Stack* stack, unsigned int cap)
{
  if(cap<=0)
   return -1;
  stack->arr = (int *)malloc(cap*4);
  stack->cap = cap;
  stack->top = 0;
  if(stack->arr==NULL)
   return -1;
  else
   return  0;
}

void stack_del(struct Stack* stack)
{
  free(stack->arr);
  stack->arr = NULL;
  stack->cap = 0;
  stack->top = 0;
}

int stack_full(struct Stack* stack)
{
  if((stack->top) >= (stack->cap))
     return -1;
  else
     return  0;
}

int stack_empty(struct Stack* stack)
{
  if((stack->top))
     return 0;
  else
     return -1;
}  


void stack_push(struct Stack* stack, int data)
{
  unsigned int pos=stack->top;
  stack->arr[pos]=data;
  pos++;
  stack->top=pos;
}

int stack_pop(struct Stack* stack)
{
  unsigned int pos=stack->top;
  pos--;
  stack->top=pos;
  return stack->arr[pos];
}

int stack_top(struct Stack* stack)
{
  unsigned int pos=stack->top;
  pos--;
  //stack->top=pos;
  return stack->arr[pos];
}

int stack_size(struct Stack* stack)
{
  return stack->top;
}
