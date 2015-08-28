#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
//通过fork创建子进程，父进程有文件描述符，但复制文件表，数据不会覆盖
int main(){
   int fd=open("a.txt",O_RDWR|O_CREAT,0666);
   if(fd==-1)perror("open"),exit(-1);
   pid_t pid=fork();
   if(pid==0){
     write(fd,"abc",3);
     close(fd);
     exit(0);
   }
   else{
     sleep(1);
     write(fd,"123",3);
     close(fd);
   }
}
