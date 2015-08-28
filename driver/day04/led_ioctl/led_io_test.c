#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argcc,char* argv[]){
     int fd;
     char input[20];
     char* st;
     int which,state=0,i;
      fd=open("/dev/led",O_RDWR);
    if(fd<0){
      printf("open file failed!\n");
      return -1;
     }
      printf("please input which led state\n");
      gets(input);
       for(i=0;i<20;i++){
        if((input[i]>=0x30)&&(input[i]<=0x39)){
              which=(int)input[i]-0x30;
              st=input+i+2;
               break;
           }
       }
     if(strcmp(st,"on")==0)
        state=0;
     else if(strcmp(st,"off")==0)
        state=1;
     else {
      printf("input error!\n");
      return -1;
     }
       ioctl(fd,which,&state); 
       close(fd);
        printf("led%d,%d\n",which,state);
    return 0;
}
