#include"uart.h"
#include"string.h"
#include"led.h"
#include"shell.h"

int main(){
   led_init();  
   shell_init();
   led_off();
   uart_puts("hello");
   while(1){
   shell_exe();
   }
    return 1;
}
