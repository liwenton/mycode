#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define SIZE 4096
char buf[SIZE];
int main(int argc,char **argv){
 if(argc<3){
   printf("error format!\n");
   return -1;
  }
 int fdsrc=open(argv[1],O_RDONLY);
  if(fdsrc<0)
    perror("Open"),exit(-1);
 int fddst=open(argv[2],O_RDWR|O_CREAT|O_EXCL,0666);
  if(fddst<0)
    perror("Open"),exit(-1);
   int rd;
   int wr;
    while(1){
     rd=read(fdsrc,buf,SIZE);
     if(rd==0)break;
     if(rd==-1)perror("read"),exit(-1);
     wr=write(fddst,buf,rd);
     if(wr==-1)perror("write"),exit(-1);
     memset(buf,0,SIZE);
   }

  close(fdsrc);
  close(fddst);
}
