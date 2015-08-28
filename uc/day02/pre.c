#include<stdio.h>
//预处理指令
#define VERSION 2
#if (VERSION<3)
  #error "版本过高"
#elif (VERSION>3)
  #warning "版本过低"
#endif

int main(){
  printf("hello c\n");
  return 0;
}
