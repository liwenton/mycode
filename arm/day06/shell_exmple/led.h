
#ifndef __LED_H__
#define __LED_H__

#define GPC1CON (*((volatile unsigned int*)0xe0200080))

#define GPC1DAT (*((volatile unsigned int*)0xe0200084))

#define GPC1PUD (*((volatile unsigned int*)0xe0200088))

extern void led_init(void);
extern void led_on(void);
extern void led_off(void);


#endif //__LED_H__
