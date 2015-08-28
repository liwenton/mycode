#ifndef __NAND_H_
#define __NAND_H_


#define NFCONF   (*(volatile unsigned int*)0XB0E00000)
#define NFCONT   (*(volatile unsigned int*)0XB0E00004)
#define NFCMMD   (*(volatile unsigned int*)0XB0E00008)
#define NFADDR   (*(volatile unsigned int*)0XB0E0000C)
#define NFDATA   (*(volatile unsigned int*)0XB0E00010)
#define NFSTAT   (*(volatile unsigned int*)0XB0E00028)
#define NFDATAB  (*(volatile unsigned char*)0XB0E00010)

#define NF_PAGE_SIZE 2048
#define NF_BLOCK_SIZE 64

void nand_init(void);
void nand_ce_enable(void);
void nand_ce_disenable(void);
void nand_readid(void);
void nand_page_read(unsigned int *buf,unsigned int offset);
void nand_page_oob_read(char *buf,unsigned int page,int len);
int  nand_block_check(int blk);
void nand_stat_wait(void);
int  nand_state(void);
int  nand_block_erase(int blk);
int  nand_page_write(unsigned int *buf,int offset);
void nand_read(unsigned int* nbuf,int add,int size);
void nand_erase(int add,int size);
#endif
