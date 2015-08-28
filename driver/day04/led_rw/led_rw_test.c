#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

int main(int argc ,char *argv[]){
     int val;
     int state;
     int fd;
   fd=open("/dev/led",O_RDWR);

    if(fd<0){
    printf("open file failed\n");
    return -1;
    }
   if(strcmp(argv[1],"on")==0)
      val=0;
   else if(strcmp(argv[1],"off")==0)
      val=1;
    write(fd,&val,sizeof(val));
    read(fd,&state,sizeof(state));
    printf("led is %s\n",state?("off"):("on"));
    close(fd);
    return 0;
}
