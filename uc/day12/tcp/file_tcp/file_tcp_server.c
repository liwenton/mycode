#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/stat.h>

#define FILE_NAME_LEN	40

typedef struct
{
	int size;
	char name[FILE_NAME_LEN];
}file_attr;


int send_file(int send_fd, char *pathname)
{
	int ret = -1;
	struct stat file_stat;
	file_attr file;

	memset((void *)file.name, 0, FILE_NAME_LEN);
	
	ret = access(pathname,R_OK);
	{
		printf("access\n");
		return -1;
	}
	
	stat(pathname,&file_stat);
	file.size = file_stat.st_size;
	strcpy((void *)file.name, pathname);
	write(send_fd, &file, sizeof(file));
	return 0;
}


void *client_thread(void *arg)
{
	struct sockaddr client_addr;
	int connfd = -1;
	int len = 0;
	int pthread_id;
	time_t ticks;
	char *time_str = NULL;

	pthread_id = pthread_self();
	pthread_detach(pthread_id);
	
	printf("成功启动线程: %d\n", pthread_id);	
	connfd = *((int *)arg);
	len = sizeof(client_addr);
	getpeername(connfd, &client_addr, &len);
  	printf("客户端%s成功连接\n",inet_ntoa(((struct sockaddr_in *)&client_addr)->sin_addr));

	send_file(connfd, "dp2pcs.pdf");

  	close(connfd);
	printf("退出线程 :%d\n", pthread_id);	
	pthread_exit((void*)NULL);
}

int main()
{
	int ret = -1;
  	int sockfd=socket(AF_INET,SOCK_STREAM,0);
  	struct sockaddr_in addr;
  	addr.sin_family=AF_INET;
  	addr.sin_port=htons(2222);
  	addr.sin_addr.s_addr=htonl(INADDR_ANY);

    ret = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
	if(ret == -1)
	{
		perror("bind");
		exit(-1);
	}
  	ret = listen(sockfd,100);
	if(ret == -1)
	{
    	perror("listen");
		exit(-1);
	}
  	while(1)
	{
  	 	printf("等待客户端的连接\n");
  		struct sockaddr_in client;
		memset((void *)&client, 0 ,sizeof(client));
  		socklen_t len=sizeof(client);
  		int newsock=accept(sockfd,(struct sockaddr*)&client, &len);
  		if(newsock == -1)
		{
			perror("accept");
			exit(-1);
		}
		
		pthread_t pthread_id;
		pthread_create(&pthread_id, NULL, client_thread, (void *)&newsock);
 	}

  	close(sockfd);
  	return 0;
} 

