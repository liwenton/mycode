#include<linux/init.h>
#include<linux/module.h> // module_init
#include<linux/irq.h>
#include<linux/interrupt.h>
#include<asm/gpio.h>
#include<plat/gpio-cfg.h>


typedef struct {
    unsigned long gpio;
    char *name;
}key_resource;

key_resource key_dev={	
    .gpio=S5PV210_GPH2(0),
    .name="GPH2_0"
};

typedef struct{
    int irq;
    int flags;
    irqreturn_t (*func)(int, void *);
    key_resource *press;
}key_info;


static irqreturn_t buttons_irq(int irq ,void*data){
        //key_resource *p =(key_resource *)data;
//	printk("%s: irq=%d\n",p->name,irq);
	printk("occur key interrupt!\n");
        return IRQ_HANDLED;
}

key_info keys={
     .irq=IRQ_EINT(16),
     .flags=IRQF_TRIGGER_FALLING,
     .press=&key_dev,
};
    
static int buttons_init(void){
	if(gpio_request(key_dev.gpio,key_dev.name)){
           printk("gpio request failed\n");
           return -1;
        }	
   if(request_irq(keys.irq, buttons_irq, keys.flags, key_dev.name, keys.press)){
          printk("irq request failed!\n");
          return -1;
      }
         printk("key irq request sucessfully!\n");
      return 0;
}

static void buttons_exit(void){
       free_irq(keys.irq, keys.press);
       gpio_free(key_dev.gpio );
}

module_init(buttons_init);
module_exit(buttons_exit);

MODULE_LICENSE("GPL");
