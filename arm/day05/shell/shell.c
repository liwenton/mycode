#include"uart.h"
#include"string.h"
#include"led.h"
#include"shell.h"
typedef struct {
  char fname[20];
  void (*func)(void);
}cmd;

cmd fun[FNUM]={
    "ledon"  ,led_on,
    "ledoff" ,led_off
};

void shell_exe(void){

    int i=0;
  uchar temp[50]={0};
   shell_init();
   while(1){
   uart_gets(temp,50);
   uart_send('\r');
   uart_send('\n');
   
    for(i=0;i<FNUM;i++){
  if(str_cmp(temp,fun[i].fname)==1)
      fun[i].func();
     }
  }
}

void shell_init(void){
  uart_init(1,115200);
  led_init();
  led_off();
  uart_puts("leeshell");
  uart_send('\r');
  uart_send('\n');
}
  
