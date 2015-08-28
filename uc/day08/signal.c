#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void fun(int signo){//参数就是信号的数值
  printf("捕获了信号%d\n",signo);
}
int main(){
  if(signal(SIGINT,fun)==SIG_ERR){
    perror("signal"),exit(-1);//判断注册是否成功
  }
  while(1){
  }
}
