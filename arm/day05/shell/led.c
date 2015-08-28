#include"led.h"

void led_init(void){
   GPJ2CON=0x00001111;
}

void led_on(void){
   GPJ2DAT=0;
}

void led_off(void){
   GPJ2DAT=0xf;
}

   
