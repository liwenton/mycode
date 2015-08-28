#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
void func(int signo)
{
   printf("进程%d捕获了信号%d\n" ,getpid(), signo);
}

int main()
{
   pid_t pid=fork();
   if(pid == 0)
   {
     signal(SIGINT , func);      //父进程发信号的时候，子进程还没有调用signal
     printf("child pid=%d\n" , getpid());
     sleep(10); 
     printf("child end pid=%d\n" , getpid()); 
     exit(-1);  
   }
   sleep(5);
   kill(pid , SIGINT); //如果子进程没有exit,会发送两次
   sleep(10);
}
