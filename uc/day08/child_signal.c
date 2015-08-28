#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void fa(int signo){
  printf("接受到子进程的结束信号%d\n",signo);
}
int main(){
  pid_t pid=fork();
  if(pid==0){
  printf("子进程开始\n");
  sleep(3);
  printf("子进程结束\n");
  exit(10);
  }
  signal(SIGCHLD,fa);
  printf("父进程开始\n");
  sleep(8);
  printf("父进程结束\n");
}
 
