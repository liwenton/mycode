#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
int main()
{
//	本地通信 
  	int sockfd=socket(AF_INET,SOCK_DGRAM,0);

  	struct sockaddr_in addr;
  	addr.sin_family=AF_INET;
  	addr.sin_port=htons(2222);//端口需要处理
  	addr.sin_addr.s_addr=inet_addr("192.168.1.8");

  	int res=bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
  	if(res==-1)perror("bind"),exit(-1);
  	printf("bind ok\n");
  	char buf[100];
  	int len=read(sockfd,buf,sizeof(buf));
  	buf[len]='\0';
  	printf("%s\n",buf);
  	close(sockfd);
  	return 0;
}
