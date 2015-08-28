#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main(void){
  int fd=open("/dev/BUTTON_IRQ",O_RDWR);
  if(fd<0){
   printf("open button device failed!\n");
   return -1;
  }
  sleep(100);
  close(fd);
  return 0;
}
