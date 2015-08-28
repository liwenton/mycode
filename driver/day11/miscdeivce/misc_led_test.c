#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc,char* argv[]){
     int fd;
     int state;
      fd=open("/dev/led",O_RDWR);
    if(fd<0){
      printf("open file failed!\n");
      return -1;
     }

     if(strcmp(argv[1],"on")==0)
        state=0;
     else if(strcmp(argv[1],"off")==0)
        state=1;
     else {
      printf("input error!\n");
      return -1;
     }
       ioctl(fd,state,NULL); 
       close(fd);
    return 0;
}
