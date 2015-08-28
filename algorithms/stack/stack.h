#ifndef STACK_H
#define STACK_H

struct Stack{
  int* arr; //数组首地址
  unsigned int  cap; //容量
  unsigned int  top; //栈顶指针
};

int stack_init(struct Stack* stack, unsigned int cap);
void stack_del(struct Stack* stack);

int stack_full(struct Stack* stack);
int stack_empty(struct Stack* stack);

void stack_push(struct Stack* stack, int data);
int stack_pop(struct Stack* stack);

int stack_top(struct Stack* stack);
int stack_size(struct Stack* stack);
#endif
