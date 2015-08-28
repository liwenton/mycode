#include"shell.h"
#include"cmd.h"

cmd fun[]={
    "ledon"    ,cmd_led_on,
    "ledoff"   ,cmd_led_off,
    "nandid"   ,cmd_nand_readid,
    "nandpread",cmd_nand_page_read,
    "nandbad"  ,cmd_nandbad,
    "boot"     ,cmd_boot,
    "help"     ,cmd_help,
    "reboot"   ,cmd_reboot_shell,
    "erase"    ,cmd_erase
};

int cmd_size=sizeof(fun)/sizeof(fun[0]);

void shell_exe(void){
   int i=0,a;
   char itoa_buf[20];
   cmd *fcmd=0;
   char temp[50]={0};
   shell_init();
   a=255;
   itoa(itoa_buf,a,10);
   uart_puts(itoa_buf);
   uart_puts("\n");
   a=10;
   itoa(itoa_buf,a,10);
   uart_puts(itoa_buf);
   uart_puts("\n");
   while(1){
   uart_puts("M-PAD:");
   uart_gets(temp,50);
   fcmd=shell_find(temp);
    if(fcmd)
     fcmd->func();
    else{
     uart_puts("M-PAD:");
     uart_puts("no this cmd!\n");
     }
    }
}

void shell_init(void){
  uart_init(1,115200);
  led_init();
  led_off();
}

cmd* shell_find(unsigned char* str){
     int i;
     for(i=0;i<cmd_size;i++)
   {
    if(str_cmp(str,fun[i].fname)==1)
         return &fun[i];
   }
    return 0;
}  
  
