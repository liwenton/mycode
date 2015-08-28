#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argcc,char* argv[]){
     int fd;
     char input[20];
     char* st;
     int which,state,i,len;
      printf("please input which led state\n");
      gets(input);
      len=strlen(input);
       if(len<=1){
        if(input[0]='q')
          return 0;
       }
      else{
       for(i=0;i<len;i++){
        if((input[i]>=0x30)&&(input[i]<=0x39)){
              which=input[i]-0x30;
              st=input+i+2;
               break;
           }
       }
      }
     if(strcmp(st,"on")==0)
       state=0;
     else if(strcmp(st,"off")==0)
        state=1;
//       ioctl(fd,which,&state); 
        printf("led%d,%d",which,state);
    return 0;
}
