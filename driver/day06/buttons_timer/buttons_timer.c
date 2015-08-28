#include<linux/init.h>
#include<linux/module.h> // module_init
#include<linux/irq.h>
#include<linux/interrupt.h>
#include<asm/gpio.h>
#include<plat/gpio-cfg.h>
#include<linux/timer.h>

int tdelay=35;
typedef struct {
    unsigned long gpio;
    char *name;
}buttons_res;

buttons_res key_dev={	
    .gpio=S5PV210_GPH2(0),
    .name="GPH2_0"
};

typedef struct{
    int irq;
    int flags;
    irqreturn_t (*func)(int, void *);
    buttons_res*press;
}buttons_info;

buttons_info keys={
     .irq=IRQ_EINT(16),
     .flags=IRQF_TRIGGER_FALLING,
     .press=&key_dev,
};

void buttons_timer_func(unsigned long data){
       int state=0;
      state=gpio_get_value(key_dev.gpio);
     if(state==0)
      printk("KEY0 :%d\n",state);
};

struct timer_list buttons_timer={
   .function=buttons_timer_func
};

module_param(tdelay,int,0);
static irqreturn_t buttons_irq(int irq ,void*data){
//        printk("occur key interrupt!\n");
        mod_timer(&buttons_timer,msecs_to_jiffies(tdelay));
        return IRQ_HANDLED;
}

static int buttons_init(void){
      if(gpio_request(key_dev.gpio,key_dev.name)){
         printk("gpio request failed\n");
          return -1;
        }
        	
   if(request_irq(keys.irq, buttons_irq, keys.flags, key_dev.name, keys.press)){
          printk("irq request failed!\n");
          return -1;
      }
//     buttons_timer.expires=jiffies+usecs_to_jiffies(20);
     init_timer(&buttons_timer);
     add_timer(&buttons_timer);
         printk("key irq request sucessfully!\n");
      return 0;
}

static void buttons_exit(void){
       free_irq(keys.irq, keys.press);
       gpio_free(key_dev.gpio );
       del_timer(&buttons_timer);
}

module_init(buttons_init);
module_exit(buttons_exit);

MODULE_LICENSE("GPL");
