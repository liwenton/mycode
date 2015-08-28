#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
int main(){
  int i;
  char buf[]="hello";
  //O_RDWR是fd的权限，0666是新文件的权限(会被屏蔽）
  int fd=open("./a.txt",O_RDWR|O_CREAT,0666);
  if(fd<0){
    perror("Open");
    return -1;
  }
   int num=write(fd,buf,sizeof(buf));
   if(num<=0)
    perror("Write"),exit(-1); //连接2个语句
    close(fd);//关闭文件描述符，从描述符从总表删除
}
