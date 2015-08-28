#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

struct Emp{
  int id;
  char name[20];
  double sal;
};
int main(){
  int fd=open("emp.dat",O_RDWR|O_CREAT|O_TRUNC,0666);
   
  if(fd==-1)perror("open"),exit(-1);
  ftruncate(fd,sizeof(struct Emp)*3);
  //映射的时候，mmap的权限应该小于等于open的权限,结束了以后不会真正写入文件
  struct Emp* pe=mmap(NULL,sizeof(struct Emp)*3,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);
  if(pe==MAP_FAILED)perror("mmap"),exit(-1);
  pe[0].id=100;
  strcpy(pe[0].name,"zhangfei");
  pe[0].sal=12000.0;
  pe[1].id=100;
  strcpy(pe[1].name,"guangyu");
  pe[1].sal=12000.0;
  pe[2].id=100;
  strcpy(pe[2].name,"liubei");
  pe[2].sal=12000.0;
  munmap(pe,sizeof(struct Emp)*3);
  close(fd);
}
