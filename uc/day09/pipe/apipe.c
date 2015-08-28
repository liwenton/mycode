#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
  mkfifo("./a.pipe",0666);
  int pipefd=open("./a.pipe", O_WRONLY);
  printf("写入管道文件，等待接收\n");
  int cnt=write(pipefd, "hello", 5);
  printf("写入成功,长度=%d\n",cnt);
  return 0;
}
