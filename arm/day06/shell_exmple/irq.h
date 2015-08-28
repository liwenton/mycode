/*
 * vim:ts=4:sw=4
 * ==========================================================================
 *
 *       Filename:  irq.h
 *
 *    Description:  irq.h
 *
 *        Version:  1.0
 *        Created:  08/27/2012 11:51:42 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  FH (@), fenghua@tarena.com.cn
 *   Organization:   Copyright (c) 2012, tarena
 *
 * ==========================================================================
 */


#ifndef  __IRQ_H__
#define  __IRQ_H__

#ifdef __IRQ_C__
#define IRQ_EXTERN
#else
#define IRQ_EXTERN extern
#endif

IRQ_EXTERN void swi_test1(void);
IRQ_EXTERN void swi_test2(void);


#endif  //__IRQ_H__





