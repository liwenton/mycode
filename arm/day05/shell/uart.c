#include"uart.h"

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
  GPA0CON=(GPA0CON & ~0xFFFF) | 0x2222;
  GPA0PUD&=~0xFF;
 //设置数据格式 
  ULCON0=3;
  UCON0=5;
  UFCON0=0;
  UMCON0=0;
  
  //设置波特率 PCLK=66.5MHz
  UBRDIV0=35;
  UDIVSLOT0=0x80;
 }
}

void uart_send(uchar data){
   while(!(UTRSTAT0 & (0x02)));
    UTHXH0=data;
}

uchar uart_reciv(void){
   while(!(UTRSTAT0 & 1));
    return URXH0;
}

void delay(int num){
  int i;
 for(i=0;i<num;i++){
  ;
 }
}

void uart_puts(uchar *str){
  while(*str!='\0'){
    uart_send(*str);

    if(*str=='\n'){
     uart_send('\r');
    }
     str++;
  }
} 

void uart_gets(uchar *buf,int len){
    int i=0;
   for(i=0;i<len-1;i++){
    buf[i]=uart_reciv();
    if(buf[i]=='\r'){
       break;
     }
     uart_send(buf[i]);
   }
    buf[i]='\0';
}     
