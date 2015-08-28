#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<string.h>

int main(){
  int sockfd=socket(AF_FILE,SOCK_DGRAM,0);
  //PF_UNIX PF_LOCAL PF_FILE   本地通信
  //PF_INET  网络通信
  //PF_INET6 网络通信IPV6
  if(sockfd==-1)perror("socket"),exit(-1);
  struct sockaddr_un addr; //本地通信地址
  //struct sockaddr_in addr; 网络通信地址
  addr.sun_family=AF_FILE;
  strcpy(addr.sun_path,"a.sock");
  int res=bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
  if(res==-1)perror("bind"),exit(-1);
  printf("绑定成功\n");
  char buf[100]={};
  int len=read(sockfd,buf,sizeof(buf));
  printf("读到了%d字节，内容：%s\n",len,buf);
  return 0;
}
  
   

