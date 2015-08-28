#include "stlist.h"
#include <stdio.h>

int main(){
  struct Stack stack;
  stack_init(&stack);
  int i;
  for(i=0;i<7;i++){
   stack_push(&stack, i+1);
  }
  while(!stack_empty(&stack))
   printf("%d\n",stack_pop(&stack));
   stack_del(&stack);
   printf("%s\n",!stack_empty(&stack)?"full":"empty");
}
