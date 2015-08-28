#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

int main(int argc ,char *argv[]){
    int fd;
    fd=open("/dev/led",O_RDWR);
      if(fd<0){
        printf("open led failed\n");
        return -1;
      }
    sleep(3);
    close(fd);
    return 0;
}
