#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void clear_child(int signal)
{
   pid_t pid;
   int state;
   while(pid=waitpid(-1, &state,WNOHANG)>0);  
}

int main()
{
   pid_t pid;
   pid=fork();
   if(pid==0)
   {
    
   }
   
}
