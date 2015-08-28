#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int i=10;
int main(){
  int i2=10;
  int *pi=malloc(4); 
  *pi=10;
  pid_t pid=fork();
  int i4=10;//这个内存地址可能会不一样，不是复制而来,父子进程各自创建
  if(pid==0){
    i=20;i2=20;*pi=20;i4=20;   
    printf("child:i=%d,i2=%d,*pi=%d,i4=%d\n",i,i2,*pi,i4);
    printf("child:&i=%p,&i2=%p,*pi=%p,i4=%p\n",&i,&i2,pi,&i4);
    exit(0);
  }
  else{
   sleep(2);
    printf("father:i=%d,i2=%d,*pi=%d,i4=%d\n",i,i2,*pi,i4);
    printf("father:&i=%p,&i2=%p,*pi=%p,i4=%p\n",&i,&i2,pi,&i4);
  }
}
