#include<linux/init.h>
#include<linux/module.h>
#include<linux/timer.h>
#include<asm/gpio.h>
#include<plat/gpio-cfg.h>

int num;
int state;
int count=20;
int fre=200;
 
static struct timer_list mytimer;

typedef struct{
   unsigned long gpio;
   char *name;
}led_resource;

led_resource led_dev[]={
  [0]={
     .gpio=S5PV210_GPJ2(0),
     .name="GPJ2_0",
  },
  [1]={
     .gpio=S5PV210_GPJ2(1),
     .name="GPJ2_1",
  },
  [2]={
     .gpio=S5PV210_GPJ2(2),
     .name="GPJ2_2",
  },
  [3]={
     .gpio=S5PV210_GPJ2(3),
     .name="GPJ2_3",
  }
};
 
typedef struct{
   int led_num;
   led_resource *press;
}led_info;

led_info leds={
   .led_num=4,
   .press=led_dev
};

module_param(fre,int,0664);
module_param(count,int,0664);

static void mytimer_function(unsigned long data){
             int i;
        led_resource *p=leds.press;
              num++;
          state=~state;
          for(i=0;i<leds.led_num;i++)
          gpio_set_value(p[i].gpio,state&1);

          if(num>=count)
	  printk("timer over\n");
          else{
          mod_timer(&mytimer,jiffies+msecs_to_jiffies(fre));
	  printk("%s\n",__FUNCTION__);
	  }
}

static int timer_init(void){
        int i;
	int mydata=0x5555;
        led_resource *p=leds.press;
	init_timer(&mytimer);
	mytimer.expires=jiffies+msecs_to_jiffies(200);
	mytimer.function=mytimer_function;
	mytimer.data=(unsigned long)&mydata;
        for(i=0;i<leds.led_num;i++){
          gpio_request(p[i].gpio,p[i].name);
          gpio_direction_output(p[i].gpio,1);
        }
	add_timer(&mytimer);
	printk("timer start counting!\n");
	return 0;
}

static void timer_exit(void){
        int i;
        led_resource *p=leds.press;
	del_timer(&mytimer);
        for(i=0;i<leds.led_num;i++)
           gpio_free(p[i].gpio);
	printk("timer is over \n");
}

module_init(timer_init);
module_exit(timer_exit);
MODULE_LICENSE("GPL");
