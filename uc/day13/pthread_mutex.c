#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>

pthread_t thread[2];
pthread_mutex_t mut;
#define INDEX 	10 

int number = 0;

void *thread1()
{

	int i;
	printf("create thread1\n");
	for(i=0; i< 3; i++)
	{
		pthread_mutex_lock(&mut);
//			number++;
		printf("tread1 : number = %d\n", number);
		pthread_mutex_unlock(&mut);
		sleep(2);
	}
	pthread_exit(NULL);
}

void *thread2()
{
	int i;
	printf("create thread2\n");
	pthread_mutex_lock(&mut);
	for(i=0; i<INDEX; i++)
	{
		number++;
		sleep(1);
	}
	pthread_mutex_unlock(&mut);
	printf("tread2 : number = %d\n", number);
	pthread_exit(NULL);

}

int main()
{
	int ret;
	ret = pthread_create(&thread[0], NULL, thread1, NULL);
	if(ret != 0)
	{
		printf("create thread 1 faild\n");
		return -1;
	}

	ret = pthread_create(&thread[1], NULL, thread2, NULL);
	if(ret != 0)
	{
		printf("create thread 2 faild\n");
		return -1;
	}

	pthread_join(thread[0],NULL);
	printf("thread1 exit\n");

	pthread_join(thread[1],NULL);
	printf("thread2 exit\n");
}

