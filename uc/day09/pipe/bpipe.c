#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
  char buf[100]={};
  int pipefd=open("./a.pipe", O_RDONLY);
  printf("等待接收\n");
  int cnt=read(pipefd, buf, sizeof(buf));
  printf("接受成功:%s\n", buf);
  return 0;
}
