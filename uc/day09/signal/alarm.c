#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
void fa(int signo)
{
  printf("捕获了信号%d\n",signo);   
}

int main()
{
   pid_t pid=fork();
   if(pid==0)
   {
    signal(SIGALRM, fa);
    alarm(1);  //1秒以后产生闹钟信号
    while(1);
    exit(0);
   } 
   return 0;
}
