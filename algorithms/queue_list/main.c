#include "qulist.h"
#include <stdio.h>

int main(){
   Queue queue;
  QueueInit(&queue);
  int i;
  for(i=0;i<7;i++){
   QueuePush(i+1, &queue);
  }
  while(!QueueEmpty(&queue))
   printf("%d\n",QueuePop(&queue));
   QueueDel(&queue);
   printf("%s\n",!QueueEmpty(&queue)?"full":"empty");
}
