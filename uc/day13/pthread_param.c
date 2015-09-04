#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

void *task(void* p)
{
  	int *x =(int *)p;	//穿地址的时候，一定要保证地址的有效性
	printf("task:%d\n", *x);
}

int main()
{
   	pthread_t id;
   	int *pi = malloc(4);
	*pi = 100;
   	int res =  pthread_create(&id, 0, task, pi);
   	if(res)
   	{
     	printf("error:%s\n", strerror(res));  
   	}
	free(pi);	//当free了以后，并没有解除内存映射，不会发生段错误。
}
