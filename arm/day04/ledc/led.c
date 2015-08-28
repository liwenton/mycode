#include"led.h"


void led_test(){
   led_init();
   while(1){
    led_on();
    delay(0xfff0);
    led_off();
    delay(0xfff0);
   }
}

void led_init(void){
   GPJ2CON=0x00001111;
}

void led_on(void){
   GPJ2DAT=0;
}

void led_off(void){
   GPJ2DAT=0xf;
}

void delay(int num){
  int i;
 for(i=0;i<num;i++){
  ;
 }
}     
   
