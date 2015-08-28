#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void fa(int signo){
   printf("捕获了信号%d\n",signo);
}

int main(){
  signal(SIGINT,fa);
  raise(SIGINT);
  int res=10;
  while(res)
  { 
    res=sleep(res);
  }
  printf("res=%d\n",res);
  raise(SIGQUIT);
  while(1);
  
}
