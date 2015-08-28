#include <stdio.h>
#include <unistd.h>

int main(){
  int *p1=sbrk(4);//虚拟内存地址映射
  int *p2=sbrk(4);//不映射
  *p1=100;
  *p2=200;
  printf("%p,%d\n",p1,*p1);
  printf("%p,%d\n",p2,*p2);
  printf("%d\n",getpid()); 
  int *p3=sbrk(4090);
  sleep(10);
  sbrk(-4090);
  printf("relese 4090\n");
  sleep(10);
  sbrk(-8);
  printf("relese 8\n");
  sleep(10);
  
  return 0;
}
