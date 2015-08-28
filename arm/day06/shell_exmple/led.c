
#include "led.h"

void led_init(void)
{
  //配置引脚
   //禁止上下拉
   //1 将GPC0 3 配置成输出引脚
   //0xe0200080 [15:12] 0001

    //volatile unsigned int *ptr;
    //ptr = (unsigned int *)0xe0200080;
    //*ptr = (*ptr & (~(0xF << 12))) | (0x01<<12);
    GPC1CON = (GPC1CON & (~(0xF << 12))) | (0x01<<12);

    //2 禁止GPC0 3的上下拉电阻
    //ptr = (unsigned int *)0xe0200088;
    //*ptr = (*ptr & (~(0x3 << 6)));
    GPC1PUD = (GPC1PUD & (~(0x3 << 6)));
}

void led_on(void)
{
    //volatile unsigned int *ptr;
    //ptr = (unsigned int *)0xe0200084;
    //*ptr |= 0x8;
    
    GPC1DAT |= 0x8;
}

void led_off(void)
{
    //volatile unsigned int *ptr;
    //ptr = (unsigned int *)0xe0200084;
    //*ptr &= ~0x8;
    GPC1DAT &= ~0x8;
}


