#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
  int fd=open("a.txt",O_RDWR|O_CREAT,0666);
  if(fd==-1)perror("open"),exit(-1);
  struct flock lock;
  lock.l_type=F_WRLCK; //写锁是一种独占锁（互斥锁），不允许其他进程进行读写操作
  lock.l_whence=SEEK_SET;
  lock.l_start=10;
  lock.l_len=20;
  lock.l_pid=-1;//-1代表参数的
  int res=fcntl(fd,F_SETLKW,&lock);//加文件锁，以阻塞的方式进行加锁，如果加不上锁，会等待锁开了以后
  if(res==-1)printf("加锁失败\n");
  else printf("加锁成功\n");
//  sleep(10);
  close(fd);
  return 0;
}
  
