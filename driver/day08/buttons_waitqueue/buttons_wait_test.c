#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int key_val;
int main(void){
  int fd=open("/dev/BUTTON_IRQ",O_RDWR);
  if(fd<0){
   printf("open button device failed!\n");
   return -1;
  }
  while(1){
     read(fd,&key_val,1);
     printf("key_val=%#x\n",key_val);
  }
  close(fd);
  return 0;
}
