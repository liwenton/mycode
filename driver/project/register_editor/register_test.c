#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

typedef struct {
  unsigned  int gpio;
  unsigned  int data;
}regs;

char *led_info[]={
  "        LED         ",
  "led register address",
  "GPJ2CON : 0xE020 0280", 
  "GPJ2DAT : 0xE020 0284",
  "--------------------",
  "led register value", 
  "GPJ2CON = 0x0000 1111",
  "LED ON  : GPJ2DAT=0",
  "LED OFF : GPJ2DAT=0xf",
   NULL,
};

char *beep_info[]={
  "       BEEP         ",
  "beep register address",
  "GPD0CON : 0xE020 00A0",
  "GPD0DAT : 0xE020 00A4",
  "--------------------",
  "beep register value",
  "GPD0CON = 0x1",
  "LED ON  : GPD0DAT=0X1",
  "LED OFF : GPD0DAT=0x0",
   NULL,
};

char *reg_select[]={
  "1.LED",
  "2.BEEP",
  "3.UART",
   NULL,
};
char **reg_ptr[]={led_info,beep_info,NULL};

void print_reginfo(char **ptr){
           int i;
   printf("\n");
  for(i=0;ptr[i]!=NULL;i++){
     printf("%s\n",ptr[i]);
  }
   printf("\n");
}

int main(){
     int i;
  regs reg;
  int fd=open("/dev/register_editor",O_RDWR);
  if(fd<0){
    printf("open register_editor device failed!\n");
    return 0;
  }
  //打印寄存器的信息  
  //for(i=0;reg_ptr[i]!=NULL;i++)
    print_reginfo(reg_select);
    scanf("%d",&i);
    print_reginfo(reg_ptr[i-1]);

 while(1){
  
  printf("please input register gpio address!\n");
  scanf("%x",&reg.gpio);
  printf("please input register gpio data\n");
  scanf("%x",&reg.data);
  ioctl(fd,reg.gpio,&reg.data);
 }
  close(fd);
  return 0;
}
