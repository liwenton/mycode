#ifndef __UART_H__
#define __UART_H__
//定义寄存器
#define GPA0CON (*((volatile unsigned int*)0xe0200000))
#define GPA0PUD (*((volatile unsigned int*)0xe0200008))

#define ULCON0 (*((volatile unsigned int*)0xe2900000))

#define UCON0 (*((volatile unsigned int*)0xe2900004))

#define UFCON0 (*((volatile unsigned int*)0xe2900008))

#define UMCON0 (*((volatile unsigned int*)0xe290000C))

#define UTRSTAT0 (*((volatile unsigned int*)0xe2900010))

#define UTXH0 (*((volatile unsigned int*)0xe2900020))
#define URXH0 (*((volatile unsigned int*)0xe2900024))

#define UBRDIV0 (*((volatile unsigned int*)0xe2900028))

#define UDIVSLOT0 (*((volatile unsigned int*)0xe290002c))

#define PCLK  66500000

//声明函数
extern void uart0_init(void);
extern void uart0_puts(char *str);

extern void delay(int num);
extern void uart0_test(void);
#endif //__UART_H__
