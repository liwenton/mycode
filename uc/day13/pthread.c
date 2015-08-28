#include <stdio.h>
#include <pthread.h>
#include <string.h>

void *task(void* p)
{
  int i;
  for(i=0;i<100;i++)
   {
     printf("task:%d\n",i);
   }
}

int main()
{
   pthread_t id;
   printf("size=%d\n",sizeof(id));
   int res =  pthread_create(&id, 0, task, 0);
   if(res)
   {
     printf("error:%s\n", strerror(res));  
   }
  int i;
  for(i=0;i<100;i++)
   {
     printf("main:%d\n",i);
   }
   sleep(5);
}
