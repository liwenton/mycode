
#include "uart.h"
void uart_test(void){
  uart0_init();
  while(1){
   uart0_puts("uart0 testing!");
   delay(0x100000);
  }
}

void uart0_init(void)
{
    //0. GPA0CON,GPA0PUD  配置GPIO
    GPA0CON = ((GPA0CON & (~(0xf<<12))) | 1<<12);
    GPA0PUD = GPA0PUD & (~3<<6);

    //1. ULCON0
    ULCON0 = 3;

    //2. UCON0
    UCON0 = 5;

    //3. UFCON0
    UFCON0 = 0;

    //4. UMCON0
    UMCON0 = 0;

    //5. UBRDIV0
    UBRDIV0 =(unsigned int)(PCLK/115200/16 - 1);

    //6. UDIVSLOT0
    UDIVSLOT0 = 0x80;
}

void uart0_putc(char ch)
{
    //   读取UTRSTAT0，判断BIT1
    //   如果等于0，则等待--1
    //   如果等于1，写UTXH0
    // UTRSTAT0
    while(!(UTRSTAT0 & 0x02));

    UTXH0 = (unsigned int)ch;
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
        }
        str++;
    }
}

unsigned char uart0_getc(void)
{
    //   读取UTRSTAT0，判断BIT0
    //   如果等于0，则等待--1
	while(!(UTRSTAT0 & 0x01));
    //   如果等于1，读URXH0
    // UTRSTAT0
    
    return (unsigned char)(URXH0 & 0xff);
}

void uart0_gets(char *buf, int len)
{
    int i;
    if (buf == 0)
    {
        return ;
    }

    for (i = 0; i < len - 1; i++)
    {
        buf[i] = uart0_getc();
        if (buf[i] == '\r')
        {
	    buf[i]='\n';
//输出能换行了，呵呵...
            break;
        }
    }
    buf[++i] = 0;
}

void delay(int num){
  int i;
  for(i=0;i<num;i++){
   ;
  }
}





