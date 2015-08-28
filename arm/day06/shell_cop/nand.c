#include"uart.h"
#include"delay.h"
#include"nand.h"
#include"string.h"

#define NF_PAGE_SIZE 2048
void nand_init(void){
   NFCONF=(0xF<<12)|(0XF<<8)|(0XF<<4);
   NFCONT=(3<<22)|3;
}

void nand_ce_enable(void){
   NFCONT&=~(1<<1);
}

void nand_ce_disenable(void){
   NFCONT|=1<<1;
}

void nand_readid(void){
   
   nand_ce_enable();

   NFCMMD=0x90;
   NFADDR=0;
   delay(256);

   uint id1,id2;
   id1=NFDATA;
   id2=NFDATA&0xFF;
   char itoa_buf[16];
   itoa(itoa_buf,id1,16);  
   uart_puts(itoa_buf);
   uart_puts("\n");

   itoa(itoa_buf,id2,16);  
   uart_puts(itoa_buf);
   uart_puts("\n");
   nand_ce_disenable();
}
   
void nand_write(int da){
}

void nand_stat_clear(void){
   NFSTAT|=(1<<4);
}

void nand_stat_wait(void){
  while(!(NFSTAT & (1<<4)));
}

void nand_page_read(unsigned int *buf,unsigned int offset){
    unsigned int page_nu;
    unsigned int page_offset;
    nand_ce_enable();
  //清除标志
    nand_stat_clear();
    NFCMMD=0x0;
  //计算地址
    page_nu     =offset/NF_PAGE_SIZE;
    page_offset =offset%NF_PAGE_SIZE;

    NFADDR=0; //page_offset&0xFF;
    NFADDR=0; //(page_offset>>8)&0xFF;
    
    NFADDR=page_nu&0xFF;
    NFADDR=(page_nu>>8)&0xFF;
    NFADDR=(page_nu>>16)&0xFF;
 
    NFCMMD=0x30;
    nand_stat_wait();
    int i;
    for(i=0;i<(NF_PAGE_SIZE/4);i++){
      *buf=NFDATA;
       buf++;
      }
     nand_ce_disenable();
}

void nand_page_oob_read(char *buf,unsigned int page,int len){
    //1、片选是能
    nand_ce_enable();

    //2、清楚标志
    nand_stat_clear();

    //4、写命令0、地址、命令0x30
    NFCMMD = 0x0;
    NFADDR = (2048 & 0xFF);

    NFADDR = ((2048>>8) & 0xF);

    NFADDR = (page & 0xFF);
    NFADDR = ((page >>8) & 0xFF);
    NFADDR = ((page >>16) & 0x7);

    NFCMMD = 0x30;

    //等待ready
    nand_stat_wait();

    //循环读取数据
    int i;

    for (i = 0; i < len; i++)
    {
        buf[i] = NFDATAB;
    }

    // 片选禁止
    nand_ce_disenable();

}

int nand_block_check(int blk){
    unsigned char flag;
    nand_page_oob_read(&flag, blk * 64, 1);
    if (flag != (unsigned char)0xFF)
    {
        return 0;
    }

    nand_page_oob_read(&flag, blk * 64 + 1, 1);
    if (flag != (unsigned char)0xFF)
    {
        return 0;
    }
    return 1;

}   
