#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
  pid_t pid1,pid2;
  pid1=fork();
  if(pid1==0){//子进程1分支
    printf("子进程一%d开始运行\n",getpid());
    sleep(3);
    printf("子进程一结束\n");
    exit(100);
  }
  if(pid1>0){
    pid2=fork();
  }
  if(pid2==0){//子进程2分支
    printf("子进程二%d开始运行\n",getpid());
    sleep(1);
    printf("子进程二结束\n");
    exit(200);
  }
//  printf("WNOHANG=%d\n",WNOHANG);
  int status;
    waitpid(0,&status,0);   //阻塞等待
   if(WIFEXITED(status)){
     printf("EXIT=%d\n",WEXITSTATUS(status));
   }
   printf("父进程结束\n");
}

