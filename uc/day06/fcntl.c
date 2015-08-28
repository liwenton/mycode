#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
  int fd=open("a.txt",O_RDWR|O_CREAT,0666);
  if(fd==-1)perror("open"),exit(-1);
  int fd2=fcntl(fd,F_DUPFD,5);
  int fd3=fcntl(fd,F_DUPFD,5);
  printf("fd=%d,fd2=%d,fd2=%d\n",fd,fd2,fd3);
  close(fd);
  close(fd2);
  close(fd3);
}
