#include "uart.h"

void uart0_test(void){
    uart0_init();
   while(1){
    uart0_puts("uart0 testing!");
    delay(0x100000);
   }
}
void uart0_init(void)
{
    //0. GPA0CON,GPA0PUD  配置GPIO
    GPA0CON = (GPA0CON &  ~0xffff | 0x2222);
    GPA0PUD&=~0xff;
    //1. ULCON0
    ULCON0 = 3;
    //2. UCON0
    UCON0 = 5;
    //3. UFCON0
    UFCON0 = 0;
    //4. UMCON0
    UMCON0 = 0;
    //5. UBRDIV0
    UBRDIV0 = 35;
	//或：(unsigned int)(PCLK/115200/16 - 1);
    //6. UDIVSLOT0
    UDIVSLOT0 = 0x0080;
//上公式的小数部分*16，得到的结果再比对一个表，得到最终数值
}

void uart0_putc(char ch)
{
    //   读取UTRSTAT0，判断BIT1
    //   如果等于0，则等待--1
    while(!(UTRSTAT0 & 0x02));
    //   如果等于1，写UTXH0
    //   UTRSTAT0
    UTXH0=(unsigned int)ch;
    return ;
}

void uart0_puts(char *str)
{
    while(*str)
    {
        //如果字符串没结束，发送一个字符
        uart0_putc(*str);
        if (*str == '\n')
        {
            uart0_putc('\r');
	//没有C语言头文件，但是能用C的‘\r’?
        }
        str++;
    }
}

void delay(int num)
{
    int i;
    for (i = 0; i < num; i++);
}
