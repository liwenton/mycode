#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
  pid_t pid=vfork();
  if(pid==0){
    printf("子进程%d开始运行\n",getpid());
    execl("./proc","proc",NULL);
    printf("子进程结束\n");
    exit(0);
  }
   printf("父进程结束\n");
}
