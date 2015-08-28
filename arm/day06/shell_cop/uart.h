#ifndef __UART_H_
#define __UART_H_

#define uint  unsigned int
#define uchar unsigned char

#define ULCON0     (*(volatile unsigned int*)0xE2900000)
#define UCON0      (*(volatile unsigned int*)0xE2900004)
#define UFCON0     (*(volatile unsigned int*)0xE2900008)
#define UMCON0     (*(volatile unsigned int*)0xE290000c)
#define UTRSTAT0   (*(volatile unsigned int*)0xE2900010)
#define UTHXH0     (*(volatile unsigned char*)0xE2900020)
#define URXH0      (*(volatile unsigned char*)0xE2900024)
#define UBRDIV0    (*(volatile unsigned int*)0xE2900028)
#define UDIVSLOT0  (*(volatile unsigned int*)0xE290002C)
#define GPA0CON    (*(volatile unsigned int*)0xE0200000)
#define GPA0PUD    (*(volatile unsigned int*)0xE0200008)


void uart_init(uint chann,uint baudrate);
void uart_test(void);
void uart_send(uchar data);
uchar uart_reciv(void);
void delay(int num);
void uart_puts(uchar *str);
void uart_gets(uchar *buf,int len);
#endif
