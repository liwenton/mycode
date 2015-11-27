#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<stdlib.h>
int main(int argc, char *argv[]){
  int sockfd;
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in addr;
  addr.sin_family=AF_INET;
  addr.sin_port=htons(2222);//端口需要处理
  addr.sin_addr.s_addr=inet_addr(argv[1]);
  int res=connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
  if(res==-1)perror("connect"),exit(-1);
  printf("connect ok\n");
  char buf[100] = {0};
  read(sockfd,buf,sizeof(buf));

  printf("%s\n",buf);
  close(sockfd);
  return 0;
}
