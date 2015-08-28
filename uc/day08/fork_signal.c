#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

//子进程继承了父进程对信号处理的方式
void fa(int signo){
  printf("捕获到信号%d\n",signo);
}

int main(){
  if(signal(SIGINT,SIG_IGN)==SIG_ERR)
   perror("signal"),exit(-1);
  if(signal(SIGQUIT,fa)==SIG_ERR)
   perror("signal"),exit(-1);

   pid_t pid=fork();
  if(pid==0){
   printf("子进程%d开始\n",getpid());
   while(1);
   printf("子进程结束\n");
  }

   printf("父进程结束\n");
}
