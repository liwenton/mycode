#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

/*int itox(char *str){
    int i,n=0;
   int data=0;
   int len=strlen(str);
   if(!(str[0]==0x30&&str[1]==0x78)){
     printf("not righit inout!\n");
      return -1;
   }
   for(i=len-1;i>1;i--,n++)
    data=data+(str[i]-48)*pow(16,n);

    return data;
}
*/
typedef struct {
  unsigned long add;
  unsigned long dat;
}reg;


int main (int argc,char *argv[]){
      int fd;
     reg led_dev;
     fd=open("/dev/leds",O_RDWR);
     if(fd<0){
      printf("open file failed\n");
      return -1;
    }

   if(!(argc>=3&&argc<=4)){
      printf("input format error!\n");
      close(fd);
      return -1;
   } 
    
    if(*argv[1]=='w'&&argc==4){
       led_dev.add=atoi(argv[2]);
       led_dev.dat=atoi(argv[3]);
      printf("wirte!\n");
      printf("add=0x%x\n",led_dev.add);
      printf("data=0x%x\n",led_dev.dat);
      ioctl(fd,1,&led_dev);
    }
    else if(*argv[1]=='r'&&argc==3){
       led_dev.add=atoi(argv[2]);
      printf("read!\n");
      ioctl(fd,0,&led_dev);
      printf("add=0x%x\n",led_dev.add);
    }
    else{
     printf("without this commond!\n");
    }
    
    close(fd);
    return 0;
}
