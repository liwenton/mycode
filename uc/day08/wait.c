#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
  pid_t pid=fork();
  if(pid==0){
    printf("子进程%d开始运行\n",getpid());
    sleep(5);
    printf("子进程%d结束运行\n",getpid());
    exit(50);
  }
    pid_t cpid=fork();
   if(cpid==0){
    printf("子进程%d开始运行\n",getpid());
    sleep(3);
    printf("子进程%d结束运行\n",getpid());
    exit(100);
  }
  printf("父进程等待子进程的结束 \n");
  int status;
  pid_t wpid=wait(&status);
  printf("等待结束\n");
  printf("子进程%d\n",wpid);
  if(WIFEXITED(status)){
   printf("子进程正常结束，退出码%d\n",WEXITSTATUS(status));
  }
} 
