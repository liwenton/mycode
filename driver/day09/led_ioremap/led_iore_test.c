#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

int main(int argc ,char *argv[]){
     int val;
     int state;
     int fd;
   fd=open("/dev/leds",O_RDWR);

    if(fd<0){
    printf("open file failed\n");
    return -1;
    }
   sleep(20);
    close(fd);
    return 0;
}
