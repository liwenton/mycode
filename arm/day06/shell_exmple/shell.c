#include "uart.h"
#include "led.h"
#include "a_strcmp.h"
#include "cmd.h"
#include "itoa.h"
#include "nand.h"

//写一个在开发板运行的程序
//通过S5PV210的串口0向PC机发送
//一个字符串
//
#define MAX_NUM   64

static unsigned char buf[MAX_NUM];

static char itoa_buf[16];

void main(void)
{
    uart0_init();
    led_init();
    nand_init();

    uart0_puts("\nTarena Shell V1.0 \n");

    uart0_puts("Date:");
    uart0_puts(__DATE__);

    uart0_puts("\n");

    uart0_puts("Time:");
    uart0_puts(__TIME__);

    int a = 100;
    itoa(itoa_buf, a);
    uart0_puts("\n");
    uart0_puts(itoa_buf);
    uart0_puts("\n");

    a = 256;
    itoa(itoa_buf, a);
    uart0_puts("\n");
    uart0_puts(itoa_buf);
    uart0_puts("\n");

    a = -1;
    itoa(itoa_buf, a);
    uart0_puts("\n");
    uart0_puts(itoa_buf);
    uart0_puts("\n");

    while(1)
    {
        cmd_t *cmd_ptr;

        //输出提示符
        uart0_puts("\nShell :");

        //获得字符串
        uart0_gets(buf, MAX_NUM);

        //获取命令的结构体指针
        cmd_ptr = cmd_find(buf);
        if (0 == cmd_ptr)
        {
            uart0_puts("\nnot cmd");
        }
        else
        {
            //调用对应的命令函数
            cmd_ptr->cmd();
        }
    }
}
