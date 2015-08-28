#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
int main(){
  void *p=mmap(NULL,4,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,0,0);
  //               大小      权限            映射物理内存
  if(p==MAP_FAILED){
     perror("mmap");
     return -1;
  }
  int *pi=p;
  *pi=100;
  int *s=malloc(4);
//  printf("%d,%s\n",*pi,str);
  printf("%p,%p\n",pi,s);
  printf("pid=%d\n",getpid());
  sleep(15);
  printf("munmap()\n");
  munmap(p,4);
  sleep(15);
  return 0;
}
