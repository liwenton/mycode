#include"uart.h"
#include"delay.h"
void uart_test(void){
  uchar c;
  uchar temp[50]={0};
  uart_init(1,115200);
  uart_puts("uart test!");
  delay(0x100000);
  while(1){
   uart_gets(temp,50);
   uart_send('\r');
   uart_send('\n');
  }
}
void uart_init(uint chann,uint buadrate){

  if(chann==1){
 //引脚配置
  GPA1CON=(GPA1CON & ~0xFFFF) | 0x2222;
  GPA1PUD&=~0xFF;
 //设置数据格式 
  ULCON2=3;
  UCON2=5;
  UFCON2=0;
  UMCON2=0;
  
  //设置波特率 PCLK=66.5MHz
  UBRDIV2=35;
  UDIVSLOT2=0x80;
 }
}

void uart_send(uchar data){
   while(!(UTRSTAT2 & (0x02)));
    UTHXH2=data;
}

uchar uart_reciv(void){
   while(!(UTRSTAT2 & 1));
    return URXH2;
}


void uart_puts(uchar *str){
  while(*str!='\0'){
    if(*str=='\n'){
     uart_send('\r');
     uart_send('\n');
      break;
     }
     uart_send(*str);
     str++;
    }
   
} 

void uart_gets(uchar *buf,int len){
    int i=0;
   for(i=0;i<len-1;i++){
    buf[i]=uart_reciv();
    if(buf[i]=='\r'){
       uart_send('\r');
       uart_send('\n');
       break;
     }
      uart_send(buf[i]);
   }
     buf[i]='\0';
}     
