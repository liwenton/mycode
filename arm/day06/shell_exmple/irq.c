/*
 * vim:ts=4:sw=4
 * =====================================================================================
 *       
 *       Filename:  irq.c
 *
 *    Description:  armboot irq 
 *
 *        Version:  1.0
 *        Created:  08/27/2012 10:17:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  FH (@), fenghua@tarena.com.cn
 *   Organization:   Copyright (c) 2012, tarena
 *
 * =====================================================================================
 */

#define __IRQ_C__

#include "uart.h"
#include "irq.h"
#include "gpio.h"

void c_swi_handler(unsigned int num, int *param)
{
    switch (num)
    {
        case 1:
            uart0_puts("\n c_swi_handler  1\n");
            break;
        case 2:
            uart0_puts("\n c_swi_handler  2\n");
            break;
        default:
            uart0_puts("\n num ERROR!!! \n");
            break;
    }
}


