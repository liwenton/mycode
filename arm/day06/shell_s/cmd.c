#include"nand.h"
#include"uart.h"
#include"led.h"
#include"string.h"
#include"shell.h"

void cmd_led_on(void){
   led_on();
}

void cmd_led_off(void){
   led_off();
}

void cmd_nand_readid(void){
    nand_readid();
}

void cmd_nandbad(void){
    int i;
    char itoa_buf[16];
    for(i=0;i<4096;i++){
    if(!nand_block_check(i)){
       uart_puts("bad block number:");
       itoa(itoa_buf,i,10);
       uart_puts(itoa_buf);
       uart_puts("\n");
      }
     }
}

void cmd_nand_page_read(void){
    unsigned int *nand_buf=(unsigned int*)0x30000000;
    nand_page_read(nand_buf,0);
    int i;
    char buf[10];
    for(i=0;i<64;i++){
       itoa(buf,nand_buf[i],16);
        uart_puts(buf);
        uart_puts("\n");
     }
}

//加载内存并运行，已经把内核写到NAND FLASH中
//   0X600000 大小0XC00000
// 把Image从闪存读出，内存0x20008000
//调用内核程序，使用函数指针

typedef void (*kernel_fun_t)(int r0,int r1,int r2);

void cmd_boot(void){

   uart_puts("load linux kernel Image ...\n");
   unsigned int *ptr=(unsigned int*)0x20008000;
//   nand_read(ptr,0X600000,0XC00000);
   uart_puts("load linux kernel\n");
   uart_puts("start linux kernel\n");

    kernel_fun_t  kernel_start=(kernel_fun_t)0x20008000;
    kernel_start(0,2456,0);
}

void cmd_erase(void){
  nand_erase(0X600000,0XC00000);
}

void cmd_help(void){
   int i;
   uart_puts("  All T-PAD shell\n");
   for(i=0;i<cmd_size;i++){
    uart_send('[');
    uart_send((unsigned char)i+'0');
    uart_send(']');
    uart_puts(fun[i].fname);
    uart_puts("\n");
  }
}
typedef void(*reboot_shell)(void);

void cmd_reboot_shell(void){
    reboot_shell reboot_start=(reboot_shell)0x23000000;
    reboot_start();
}

