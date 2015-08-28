#include"uart.h"
#include"delay.h"
#include"nand.h"
#include"string.h"

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
   

int nand_state(void){
     int sta;
    NFCMMD=0X70;
    sta=NFDATA;

    return sta;
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
    nand_ce_enable();
  //清除标志
    nand_stat_clear();
    NFCMMD=0x0;
  //计算地址

    NFADDR=(2048&(0XFF));
    NFADDR=((2048>>8)&(0XF));
    
    NFADDR=page&0xFF;
    NFADDR=(page>>8)&0xFF;
    NFADDR=(page>>16)&0xFF;
 
    NFCMMD=0x30;
    nand_stat_wait();
    int i;
    for(i=0;i<len;i++){
      *buf=NFDATA;
       buf++;
    }
    nand_ce_disenable();
}


int nand_block_check(int blk){
    unsigned char flag;
    nand_page_oob_read(&flag,blk*64,1);
    if(flag!=(unsigned char)0XFF)
      return 0;
    
    nand_page_oob_read(&flag,blk*64+1,1);
    if(flag!=(unsigned char)0XFF)
      return 0;    
 
      return 1;
}

int nand_block_erase(int blk){
    blk*=NF_BLOCK_SIZE;
    nand_ce_enable();
    nand_stat_clear();
    NFCMMD=0X60;
    NFADDR=blk & 0XFF;   
    NFADDR=(blk>>8) & 0XFF;   
    NFADDR=(blk>>16) & 0XFF;   
    NFCMMD=0XD0;
    nand_stat_wait();

    if(nand_state() & 0x01){
      nand_ce_disenable();
      return -1;
    }

    else{
      nand_ce_disenable();
      return 0;
   }
}

int nand_page_write(unsigned int *buf,int offset){
    unsigned int page_nu;
    unsigned int page_offset;
    nand_ce_enable();
  //清除标志
    nand_stat_clear();
    NFCMMD=0x80;
  //计算地址
    page_nu     =offset/NF_PAGE_SIZE;
    page_offset =offset%NF_PAGE_SIZE;

    NFADDR=page_offset&0xFF;
    NFADDR=(page_offset>>8)&0xFF;

    NFADDR=page_nu&0xFF;
    NFADDR=(page_nu>>8)&0xFF;
    NFADDR=(page_nu>>16)&0xFF;
    NFCMMD=0x10;
    nand_stat_wait();
     int i;
    for(i=0;i<(NF_PAGE_SIZE/4);i++){
       NFDATA=*buf;
       buf++;
      }
     nand_ce_disenable();

    if(nand_state() & 0x01){
      nand_ce_disenable();
      return -1;
    }

    else{
      nand_ce_disenable();
      return 0;
   }
}

void nand_read(unsigned int* nbuf,int add,int size){
      int i;
     int page   =size/NF_PAGE_SIZE;
     int offset =size%NF_PAGE_SIZE;
      if(offset)
        page+=1;
     for(i=0;i<page;i++){
        nand_page_read(nbuf,add+i*NF_PAGE_SIZE);
        uart_puts(".");
        nbuf+=512;
     }
}

void nand_erase(int add,int size){
      int i,count=0;
     int block   =size/(NF_PAGE_SIZE*NF_BLOCK_SIZE);
     int offset  =size%(NF_PAGE_SIZE*NF_BLOCK_SIZE);
            add  =add/(NF_PAGE_SIZE*NF_BLOCK_SIZE);

      if(offset)
        block+=1;
     for(i=0;i<block;i++){
        uart_puts(".");
       if(!nand_block_erase(add+i))
          count++;
      }

      if(count==i)
       uart_puts("Sucess to erase\n");
      else
       uart_puts("fail to erase\n");
       
}        
         
