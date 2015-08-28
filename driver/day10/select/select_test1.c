#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

int main(){
   fd_set rfds;
   struct timeval tv;
   int retval;
   char buf[200];
   memset(buf,0,200);

  while(1){
   FD_ZERO(&rfds);
   FD_SET(0,&rfds);
   tv.tv_sec=3;
   tv.tv_usec=0;
   retval=select(1,&rfds,NULL,NULL,&tv);
   
   if(retval==-1)
    perror("select()");
   else if(retval){
    printf("Data is available now.\n");
     if(FD_ISSET(0,&rfds)){
        read(0,buf,200);
       printf("mes:%s\n",buf);
     }
   }
   else
   printf("No data within five seconds.\n");
  }   
   return 0;
}
