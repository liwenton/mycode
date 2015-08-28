#include <stdio.h>
#include <stdlib.h>

void at(){
  printf("atexit is called\n");
}

int main(){
  atexit(at);//注册了推出前调用的函数
  printf("bigin\n");
//  exit(0);
  _Exit(0);//立即退出，不调用at()
  printf("end\n");
  return 0; //return返回的效果跟exit是一样的
}
