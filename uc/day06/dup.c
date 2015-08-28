#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){
  int fd=open("a.txt",O_RDWR|O_CREAT|O_TRUNC,0666);
  if(fd==-1)perror("open"),exit(-1);
  int fd2=dup(fd); //复制描述符，不复制文件表,只有一个偏移量
}
