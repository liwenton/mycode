#ifndef __LED_H_
#define __LED_H_

#define GPJ2CON (*(volatile unsigned int*)0xE0200280)
#define GPJ2DAT (*(volatile unsigned int*)0xE0200284)
#define GPJ2PUD (*(volatile unsigned int*)0xE0200288)

void led_on(void);
void led_off(void);
void led_init(void);
#endif
