
#ifndef __NAND_H__
#define __NAND_H__

//定义寄存器
#define NFCONF (*((volatile unsigned int*)0xB0E00000))

#define NFCONT (*((volatile unsigned int*)0xB0E00004))

#define NFCMMD (*((volatile unsigned int*)0xB0E00008))

#define NFADDR (*((volatile unsigned int*)0xB0E0000C))

#define NFDATA (*((volatile unsigned int*)0xB0E00010))
#define NFDATAB (*((volatile unsigned char*)0xB0E00010))

#define NFSTAT (*((volatile unsigned int*)0xB0E00028))


#define NF_PAGE_SIZE (2048)

//函数声明 
extern void nand_init(void);
extern void nand_read_id(void);

extern void nand_page_read(unsigned int *buf,
        unsigned int offset);

extern int nand_block_check(int blk);

#endif //__NAND_H__






