#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    printf("begin\n");
    pid_t pid=fork();
   if(pid==0){
   // printf("子进程:%d\n",getpid());
    printf("父进程:%d\n",getppid());
    exit(-1);
   }
   else{ 
   // printf("父进程:%d\n",getpid());
    printf("子进程:%d\n",pid);
   }
}
