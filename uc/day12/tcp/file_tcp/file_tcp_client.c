#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<stdlib.h>


#define FILE_NAME_LEN	40

typedef struct
{
	int size;
	char name[FILE_NAME_LEN];
}file_attr;


void show_file_size(int file_size)
{
	int count = 0;
	int show_size = file_size;
	while(show_size / 1024)
	{
		count++;
		show_size /= 1024;
	}
	switch(count)
	{
		case 0:	
	  		printf("file size : %d\n" ,show_size);
	  		break;
		case 1:
	  		printf("file size : %dK\n" ,show_size);
	  		break;
		case 2:
	  		printf("file size : %dM\n" ,show_size);
	  		break;
		case 3:
	  		printf("file size : %dG\n" ,show_size);
	  		break;
	}
}

int main(){
  int sockfd;
  file_attr file;
  memset((void *)file.name, 0, FILE_NAME_LEN);

  sockfd=socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in addr;
  addr.sin_family=AF_INET;
  addr.sin_port=htons(2222);//端口需要处理
  addr.sin_addr.s_addr=inet_addr("192.168.5.101");
  int res=connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
  if(res==-1)perror("connect"),exit(-1);
  printf("connect ok\n");
  read(sockfd, &file, sizeof(file));
  printf("file name : %s\n", file.name);
  show_file_size(file.size);
  close(sockfd);
  return 0;
}
