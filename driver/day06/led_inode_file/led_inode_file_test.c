#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

int main(int argc,char *argv [] ){
      int fd;
      int state;
      char in[20];
      fd=open("/dev/led_inode",O_RDWR);
      if(fd<0){
	  printf("open led file error\n");
	  return -1;
      }
      while(1){
      printf("please input led state!\n");
      scanf("%s",in);
      if(strcmp(in,"on")==0){
         state=0;
        ioctl(fd,state);	
       }
      else if(strcmp(in,"off")==0){
         state=1;
        ioctl(fd,state);	
       }
      else if(in[0]=='q')
        break; 
     }
      close(fd);
      return 0;
}

