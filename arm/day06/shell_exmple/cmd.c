
#include "cmd.h"
#include "led.h"
#include "a_strcmp.h"
#include "irq.h"
#include "nand.h"

static void cmd_led_on(void)
{
    led_on();
}

static void cmd_led_off(void)
{
    led_off();
}

void cmd_nandid(void)
{
    nand_read_id();
}


void cmd_nread(void)
{
    unsigned int *buf = 
           (unsigned int *)0x30000000;

    uart0_puts("nand page read ....\n");

    nand_page_read(buf, 0);


    uart0_puts("nand page read  DATA \n");
    char itoa_buf[16];
    int i; 
    for (i = 0; i < 64; i++)
    {
        if (!(i % 4))
        {
            uart0_puts("\n");
        }

        itoa(itoa_buf, buf[i]);
        uart0_puts(itoa_buf);
        uart0_puts(" ");
    }
}
//加载内核并运行
//1、已经把内核写到nand flash中
//   0x600000  大小0xC00000
//2、把Image从闪存读出，内存0x20008000
//3、调用内核程序
//   使用函数指针

typedef void (*kernel_func_t)(int r0, int r1, int r2);

void cmd_boot(void)
{
    uart0_puts("load Linux kernel Image ...\n");

    unsigned char *ptr=(unsigned char*)0x20008000;
    unsigned int offset = 0x600000;

    int i;
    for (i = 0; 
         i < 0xC00000 / NF_PAGE_SIZE;
         i++)
    {
        uart0_puts(".");
        nand_page_read((unsigned int *)ptr, 
                offset);
        ptr += NF_PAGE_SIZE;
        offset += NF_PAGE_SIZE;
    }

    uart0_puts("load Linux kernel Image End\n");

    uart0_puts("Start kernel ...\n");

    kernel_func_t  kernel_start = 
                    (kernel_func_t)0x20008000;

    //启动程序和Linux内核传递参数问题
    //传递参数的途径有两个：
    //函数传参数（三个）
    //其他信息通过内存传递
    //    启动程序和内核要约定
    //    内存地址，约定参数格式
    //函数的三个参数:
    // 第一个参数：没意义，一般不用
    // 第二个参数：内核我开发板上运行
    //             没类开发板定义个
    //             专有的数字（号）
    //             引导程序通过
    //             函数第二个参数
    //             给定一个数字
    //             内核检测这个参数
    //             和内核定义的是否一样
    //             如果一样内核继续运行
    //             否则终止运行.
    //第三个参数：传递其他参数的物理地址
    //            我们例子里面
    //            没有给内核传递其他参数
    //            本质上我们个Image（内核）
    //            跟本没去去其他从参数。
    //            因为内核支持默认参数
    //            其他参数用默认的。
    kernel_start(0, 2456, 0);

    uart0_puts("Start kernel end\n");
}

void cmd_nandbad(void)
{
    int i;
    for (i = 0; i < 8192; i++)
    {
        if (!nand_block_check(i))
        {
            char buf[16];
            itoa(buf, i);
            uart0_puts("\n");
            uart0_puts("Bad Block Num=");
            uart0_puts(buf);
        }
    }
    uart0_puts("\n");
}

void cmd_swi1(void)
{
    swi_test1();
}

void cmd_swi2(void)
{
    swi_test2();
}


static const cmd_t cmd_tbl[] =
{
    {"ledon", cmd_led_on},
    {"ledoff", cmd_led_off},
    {"nandid", cmd_nandid},
    {"nread", cmd_nread},
    {"boot", cmd_boot},
    {"nandbad", cmd_nandbad},
    {"swi1", cmd_swi1},
    {"swi2", cmd_swi2},
};

static int cmd_tbl_size = sizeof(cmd_tbl)/
                          sizeof(cmd_tbl[0]);

cmd_t *cmd_find(const char *str)
{
    int i;
    for (i = 0; i < cmd_tbl_size; i++)
    {
        if (!a_strcmp(str, cmd_tbl[i].name))
        {
            return &(cmd_tbl[i]);
        }
    }
    return 0;
}





