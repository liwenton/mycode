#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
  pid_t pid=fork();
  if(pid==0){
   printf("child begin sleep  pid=%d\n",getpid());
   sleep(15);
   printf("child stop sleep\n");
   exit(0);
  }
  else{
   printf("father bigin sleep  pid=%d\n",getpid());
   sleep(5);
   printf("father stop sleep\n");
  }
}
