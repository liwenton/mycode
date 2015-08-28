#include"nand.h"
#include"uart.h"
#include"led.h"
#include"string.h"

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

