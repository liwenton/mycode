#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//父子进程不同时运行，子进程占用了父进程的内存空间，父进程要等待子进程结束
int main(){
  pid_t pid=vfork();
  if(pid==0){
    printf("子进程%d开始运行\n",getpid());
    sleep(3);
    printf("子进程结束\n");
    exit(0);
  }
   printf("父进程结束\n");
}
