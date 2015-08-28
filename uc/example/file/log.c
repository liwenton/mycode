#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 4096

char buf[BUFSIZE]={0};

int main(int argc, char *argv[])
{
  int len;
  if(argc!=2)
  {
    printf("without pathname\n");
    return =1;
  }
  if(access(argv[1],F_OK)<0)
  {
    printf("without this file\n");
    return -1;
  }
  int fd=open(argv[1], R_ONLY);
  if(fd<0)
  {
    perror("open");
    return -1;
  }
  while(1)
  {
    len=read(fd, buf, BUFSIZE);  
    if(len==0)
     break;
  close(fd);
}
