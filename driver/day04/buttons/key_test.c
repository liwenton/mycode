#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
typedef struct{
    int num;
    int state;
}key;

int main(void){
   int fd;
   int state;
   key k1;
   fd=open("/dev/key",O_RDWR);
    if(fd<0){
     printf("open file failed\n");

     return -1;
    }
   while(1){
    read(fd,&k1,sizeof(k1));
    sleep(1);
    printf("key%d  %d\n",k1.num,k1.state);
   }
    close(fd);
    return 0;
}

