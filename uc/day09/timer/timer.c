#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

void fa(int signo)
{
   printf("信号发送到了\n");
}

int main()
{
   signal(SIGALRM, fa);
   struct itimerval timer;
   //每隔1.1秒产生一个信号
   timer.it_interval.tv_sec = 60;
   timer.it_interval.tv_usec= 00;

   //3秒后开启定时器 
   timer.it_value.tv_sec= 3;       
   timer.it_value.tv_usec=0;   
   setitimer(ITIMER_REAL, &timer, NULL);

   while(1){
    sleep(30);
   }
}
