#include<linux/init.h>
#include<linux/module.h> // module_init
#include<linux/irq.h>
#include<linux/interrupt.h>
#include<asm/gpio.h>
#include<plat/gpio-cfg.h>
#include<linux/workqueue.h>

typedef struct {
    unsigned long gpio;
    char *name;
}key_resource;

int tdelay=230;

key_resource key_dev={	
    .gpio=S5PV210_GPH2(0),
    .name="KEY0_IRQ"
};

typedef struct{
    int irq;
    int flags;
    irqreturn_t (*func)(int, void *);
    key_resource *press;
}key_info;


//static struct work_struct key_work;
static struct delayed_work key_delay;
static struct workqueue_struct *key_wq;
module_param(tdelay,int,0664);

void key_work_handler(struct work_struct *work){
      printk("key_work_handler\n");
}

static irqreturn_t buttons_irq(int irq ,void*dev_id){
//      printk("key irq occur!\n");    
//      schedule_delayed_work(&key_delay,msecs_to_jiffies(tdelay));
        queue_delayed_work(key_wq,&key_delay,msecs_to_jiffies(tdelay));
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
       //INIT_WORK(&key_work,key_work_handler);
         key_wq=create_workqueue("Key_irq");
         INIT_DELAYED_WORK(&key_delay,key_work_handler);
         printk("key irq request sucessfully!\n");
      return 0;
}

static void buttons_exit(void){
       free_irq(keys.irq, keys.press);
       gpio_free(key_dev.gpio );
       destroy_workqueue(key_wq);
}

module_init(buttons_init);
module_exit(buttons_exit);

MODULE_LICENSE("GPL");
