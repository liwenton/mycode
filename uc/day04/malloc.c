#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
  int a,b,c,d;
  printf("%p,%p,%p,%p\n",&a,&b,&c,&d);
  int* p1=malloc(12);//映射了33个内存页
  *(p1+4)=100;//在33个内存哟之内不会有段错误
  int* p2=malloc(12);//不需要内存映射
  *p2=100;//对比第八行，便于管理和操作
  int* p3=malloc(12);//
  int* p4=malloc(12);//
  //malloc(4096*30);//
  *(p1+4096*33)=100;
  printf("%p,%p,%p,%p\n",p1,p2,p3,p4);
  printf("%d\n",getpid());
  while(1);
  free(p1);
}
