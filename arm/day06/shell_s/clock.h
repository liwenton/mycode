#ifndef __CLOCK_H_
#define __CLOCK_H_

#define  APLL_LOCK (*(volatile unsigned int*)0xE0100000)
#define  MPLL_LOCK (*(volatile unsigned int*)0xE0100008)
#define  EPLL_LOCK (*(volatile unsigned int*)0xE0100010)
#define  VPLL_LOCK (*(volatile unsigned int*)0xE0100020)

#define  APLL_CON0 (*(volatile unsigned int*)0xE0100100)
#define  MPLL_CON  (*(volatile unsigned int*)0xE0100108)
#define  EPLL_CON  (*(volatile unsigned int*)0xE0100110)
#define  VPLL_CON  (*(volatile unsigned int*)0xE0100120)

#define  CLK_SRC0  (*(volatile unsigned int*)0xE0100200)
#define  CLK_DIV0  (*(volatile unsigned int*)0xE0100300)

void sys_clock_init(void);

#endif
