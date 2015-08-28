#include <stdio.h>
#include <errno.h>
//#include <string.h>

int main(){
  FILE* file=fopen("/etc/passwd","w");
  if(file==NULL){
//    char *errstr=strerror(errno);
//    printf("%d,%s\n",errno,errstr);
//    printf("error:%m\n");//%m不用配变量
    perror("Open");
    return -1;
  }
  fclose(file);
}
