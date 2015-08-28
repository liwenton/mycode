#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//用程序执行ls -l ../day07
int main(){
  printf("begin\n");
  execl("/bin/ls","ls","-l","../day07",NULL);//不会新建进程，只是替换了原有进程的一切
  //参数1是可执行文件（带路径的）
  //参数2是命令，NULL结束
  printf("end\n");
}   
