#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//无名管道，利用fork()复制代码原理，父子进程的文件描述符公用文件表，可以组合新的通道
int main()
{
  int fd[2]={};
  pipe(fd);  //读写描述符都可以了
  pid_t pid=fork();
  if(pid==0)
  {
     close(fd[1]); //关闭子进程的写端口 
     while(1)
     {
       int x;
       int res=read(fd[0], &x, 4);
       if(res<=0)
         break;
       printf("x=%d\n", x);                       
     }
     close(fd[0]);
     exit(0);
  }
  close(fd[0]);
  int i;
  for(i=0;i<100;i++)
  {
    write(fd[1], &i, 4);
    usleep(100000);
  }
  close(fd[1]);
}
