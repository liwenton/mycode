#include "queue.h"
#include <stdio.h>

int main(){
  Queue queue;
  queue_init(&queue, 5);
  int i;
  for(i=0;!queue_full(&queue);i++){
   queue_push(i+1, &queue);
  }
  while(!queue_empty(&queue))
   printf("%d\n",queue_pop(&queue));
   queue_del(&queue);
}
