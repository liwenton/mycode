#include<linux/init.h>
#include<linux/module.h>
#include<asm/gpio.h>
#include<plat/gpio-cfg.h>

#define LED_ON  0
#define LED_OFF 1

static int io=0;

typedef struct{
   unsigned long gpio;
   char *name;
}led_resource;

led_resource led_info[]={
   [0]={
     .gpio=S5PV210_GPJ2(0),
     .name="GPJ2_0"
    },
   [1]={
     .gpio=S5PV210_GPJ2(1),
     .name="GPJ2_1"
    },
   [2]={
     .gpio=S5PV210_GPJ2(2),
     .name="GPJ2_2"
    },
   [3]={
     .gpio=S5PV210_GPJ2(3),
     .name="GPJ2_3"
    }
};

module_param(io,int,0);
module_param(state,int,0);

static int led_init(void){   
   printk("LED%d ON\n",io); 
   gpio_request(led_info[io].gpio,led_info[io].name);
   gpio_direction_output(led_info[io].gpio,LED_ON;
}

static void led_exit(void){
   printk("LED%d OFF\n",io);
   gpio_set_value(led_info[io].gpio,LED_OFF);
   gpio_free(led_info[io].gpio);
}


moduel_init(led_init);
moduel_exit(led_exit);


MODULE_LICENSE("GPL";
MODULE_AUTHOR("LWT");
MODULE_DESCRIPTION("LED device moudle");
