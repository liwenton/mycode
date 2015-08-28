#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<string.h>

int main(){
  int sockfd=socket(AF_FILE,SOCK_DGRAM,0);
  if(sockfd==-1)perror("socket"),exit(-1);
  struct sockaddr_un addr;
  addr.sun_family=AF_FILE;
  strcpy(addr.sun_path,"a.sock");
  int res=connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
  if(res==-1)perror("bind"),exit(-1);
  printf("connect成功\n");
  write(sockfd,"hello",5);
  return 0;
}
  
   

