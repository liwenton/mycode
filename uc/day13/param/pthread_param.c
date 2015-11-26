#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

/*该例程演示了当向子线程传递参数时，释放了参数内存，会导致传入参数值无法
预料*/

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
	/*当在先程结束前free了，并没有解除内存映射，所以不会发生段错误*/
	// free(pi);
	pthread_join(id, NULL);
}
