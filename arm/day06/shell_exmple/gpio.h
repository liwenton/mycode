
#ifndef __GPIO_H__
#define __GPIO_H__

#define GPH0CFG   (*((volatile unsigned int*)0xE0200C00))
#define GPH0DAT   (*((volatile unsigned int*)0xE0200C04))
#define GPH0PUD   (*((volatile unsigned int*)0xE0200C08))

#endif
