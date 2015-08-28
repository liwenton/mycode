#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]){
  struct stat s={};
  chmod("a.txt",0740);
  int res=stat("a.txt",&s);
  printf("权限=%o\n",s.st_mode & 0777);
  printf("size=%d\n",s.st_size);
  truncate("a.txt",100);
  printf("size=%d\n",s.st_size);
  //系统初始的权限屏蔽字为0002,
  mode_t old=umask(0666);
  int fd=open("b.txt",O_RDWR|O_CREAT,0666);
  umaks(old);//恢复系统默认屏蔽
  
}
