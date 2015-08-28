#include <stdio.h>
#include <unistd.h>

int main(){
   void *p=sbrk(0);
   brk(p+4);//分配了4个字节
   brk(p+8);//分配了4个字节
   brk(p+4);//回收了4个字节
   int *pi=p;
   *pi=100;
   
}
