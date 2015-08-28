#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main(){
   pid_t pid=fork(); //先fork()，后open，两张文件表
   int fd=open("a.txt",O_RDWR|O_CREAT,0666);
   if(fd==-1)perror("open"),exit(-1);
   if(pid==0){
     write(fd,"abc",3);
     close(fd);
     exit(0);
   }
   else{
     sleep(1);
     write(fd,"123",3);//相互覆盖
     close(fd);
   }
}
