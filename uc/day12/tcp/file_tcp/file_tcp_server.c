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
#include<fcntl.h>

#define FILE_NAME_LEN	40
#define FILE_BUFF_LEN	1400


typedef struct
{
	int size;
	char name[FILE_NAME_LEN];
}file_attr;

typedef struct
{
	file_attr attr;
	char *content;
}file_send;

//
int send_file(int send_fd, char *pathname)
{
	int index = 0;
	int ret = -1;
	int file_fd;
	int save_fd;
	int file_len = 0;
	int file_size = 0;
	char file_buffer[FILE_BUFF_LEN] = {0};
	char save_path[FILE_NAME_LEN] = {0};
	struct stat file_stat;
	file_send file;

	memset((void *)file.attr.name, 0, FILE_NAME_LEN);
	
	ret = access(pathname,R_OK);
	if(ret == -1)
	{
		printf("access\n");
		return -1;
	}
	
	file_fd = open(pathname, O_RDONLY);
	if(file_fd == -1)
	{
		printf("open\n");
		return -1;
	}
	
	stat(pathname,&file_stat);
	file.attr.size = file_stat.st_size;
	strcpy((void *)file.attr.name, pathname);

	file.content = malloc(file_stat.st_size);
	memset(file.content, 0, file_stat.st_size);

	write(send_fd, &file.attr, sizeof(file.attr));

	while(1)
	{
		file_len = read(file_fd, file.content + file_size, FILE_BUFF_LEN);
		if(file_len == 0)
		{
			break;
		}
		write(send_fd, file.content + file_size, FILE_BUFF_LEN);
		file_size += file_len;
	}

	/*
	snprintf(save_path, FILE_NAME_LEN, "../%s", file.attr.name);
	save_fd = open(save_path, O_RDWR|O_CREAT);
	write(save_fd, file.content, file.attr.size);	
	close(save_fd);
	*/

	//write(send_fd, file.content, file.attr.size);
	close(file_fd);
	free(file.content);
	return 0;
}


void *client_thread(void *arg)
{
	struct sockaddr client_addr;
	int connfd = -1;
	int len = 0;
	int pthread_id;
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

