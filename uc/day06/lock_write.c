#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
  int fd=open("a.txt",O_RDWR);
  if(fd==-1)perror("open"),exit(-1);
  struct  flock lock;
//  struct  flock lock;
  lock.l_type=F_WRLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start=0;
  lock.l_len=14;
  lock.l_pid=-1;

  int res=fcntl(fd,F_SETLK,&lock);
  if(res==-1)printf("其他进程正在使用\n");

  else
  write(fd,"abcd1234567890",14);
  close(fd);
}
