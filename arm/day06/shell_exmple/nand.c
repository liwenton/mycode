
#include "uart.h"
#include "nand.h"
#include "delay.h"

void nand_init(void)
{
    //1 GPIO 
    //2 NAND REG 
    //  NFCONF
    //  NFCONT
    NFCONF = (0xF<<12) | (0xF<<8) | 
             (0xF<<4) | (1<<1);

    NFCONT = (3<<22) | (3<<0);
}

void nand_ce_enable(void)
{
    NFCONT &= ~(1<<1);
}

void nand_ce_disable(void)
{
    NFCONT |= (1<<1);
}

void nand_read_id(void)
{
    //1. read nand id
    nand_ce_enable();
    NFCMMD = 0x90;
    NFADDR = 0x0;
#if 0
    int i;
    for(i = 0; i < 256; i++)
    {
        ;
    }
#else
    delay(256);
#endif
    unsigned int id1;
    unsigned int id2;

    id1 = NFDATA;  //读取4个字节
    id2 = (NFDATA) & 0xFF;  //保留第一个字节

    nand_ce_disable();

    //2. display
    //  id-->string
    //  uart0_puts(strging);
    
    char buf[16];
    itoa(buf, id1);
    uart0_puts("\n ID1 = ");
    uart0_puts(buf);

    itoa(buf, id2);
    uart0_puts("\n ID2 = ");
    uart0_puts(buf);

    uart0_puts("\n");
}

//清楚标志位
void nand_stat_clear(void)
{
    NFSTAT |= (1<<4);
}

//等待ready
void nand_stat_wait(void)
{
    while(!(NFSTAT & (1<<4)))
    {
        ;
    }
}

void nand_page_read(unsigned int *buf,
        unsigned int offset)
{
    //1、片选是能
    nand_ce_enable();

    //2、清楚标志
    nand_stat_clear();

    //3、计算地址
    unsigned int page_no;
    unsigned int page_offset;

    page_no = offset / NF_PAGE_SIZE;
    page_offset = offset % NF_PAGE_SIZE;

    //4、写命令0、地址、命令0x30
    NFCMMD = 0x0;
    NFADDR = (page_offset & 0xFF);
    NFADDR = ((page_offset>>8) & 0xFF);

    NFADDR = (page_no & 0xFF);
    NFADDR = ((page_no >>8) & 0xFF);
    NFADDR = ((page_no >>16) & 0xFF);

    NFCMMD = 0x30;

    //等待ready
    nand_stat_wait();

    //循环读取数据
    int i;

    for (i = 0; i < NF_PAGE_SIZE / 4; i++)
    {
        buf[i] = NFDATA;
    }

    // 片选禁止
    nand_ce_disable();
}



void nand_page_oob_read(char *buf, int page, int len)
{

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
    nand_ce_disable();
}

//检测一个块是好还是坏的
//参数：blk->块号
//输出：0 表示坏，1表示好
//读取相应的块的第一页和第二页的
//2048位置的数据(0xFF)
int nand_block_check(int blk)
{
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





