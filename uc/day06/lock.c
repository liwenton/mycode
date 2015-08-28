#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
  int fd=open("a.txt",O_RDWR|O_CREAT,0666);
  if(fd==-1)perror("open"),exit(-1);
  struct flock lock;
  lock.l_type=F_RDLCK;//锁是一种共享锁，允许读进程访问，锁定其他进程的写进行
  lock.l_whence=SEEK_SET;
  lock.l_start=10;
  lock.l_len=20;
  lock.l_pid=-1;//-1代表参数的
  int res=fcntl(fd,F_SETLK,&lock);
  if(res==-1)printf("加锁失败\n");
  else printf("加锁成功\n");
  sleep(10);
  close(fd);
  return 0;
}
  
