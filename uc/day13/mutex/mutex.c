#include <stdio.h>
#include <pthread.h>

char *data[5];
int size = 0; //元素数量
pthread_mutex_t mutex;

void *task(void* p)
{
	char *name =(char *)p;

	pthread_mutex_lock(&mutex);
	data[size] = name;
	usleep(100000);
	size++;
	pthread_mutex_unlock(&mutex);
}

int main()
{
	pthread_t id1, id2;
	int i;
	data[size] = "liubei";
	size++;

	pthread_mutex_init(&mutex, 0);
	pthread_create(&id1, 0, task, "guanyu");
	usleep(10);
	pthread_create(&id2, 0, task, "zhangfei");

	pthread_join(id1, NULL);
	pthread_join(id2, NULL);

	pthread_mutex_destroy(&mutex);

	for(i=0; i<size; i++)
	{
		printf("%s\n", data[i]);
	}

	return 0;
}

