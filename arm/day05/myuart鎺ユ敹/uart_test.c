
#include "uart.h"

//写一个在开发板运行的程序
//通过S5PV210的串口0向PC机发送
//一个字符串
//
#define MAX_NUM   64
static unsigned char buf[MAX_NUM];

void uart_test(void)
{
    uart0_init();
    while(1)
    {
	uart0_puts("INPUT STRING :\n");
        uart0_gets(buf, MAX_NUM);
        uart0_puts(buf);

        delay(0x1000);
    }
}
