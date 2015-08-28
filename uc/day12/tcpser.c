#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(){
  int sockfd=socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in addr;
  addr.sin_family=AF_INET;
  addr.sin_port=htons(2222);
  addr.sin_addr.s_addr=inet_addr("192.168.1.8");
  int res=bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
  if(res==-1)perror("bind"),exit(-1);
  if(listen(sockfd,100)==-1)
    perror("listen"),exit(-1);
  while(1){
   printf("等待客户端的连接\n");
  struct sockaddr_in client;
  socklen_t len=sizeof(client);
  int newsock=accept(sockfd,(struct sockaddr*)&client, &len);
  if(newsock==-1)perror("accept"),exit(-1);
  printf("客户端%s成功连接\n",inet_ntoa(client.sin_addr));
  char buf[100];
  read(newsock,buf,sizeof(buf));
  printf("buf=%s\n",buf);
  write(newsock,"welcome",8);
  close(newsock);
 }
  close(sockfd);
  return 0;
} 

