#include<linux/init.h>
#include<linux/module.h>
#include<linux/timer.h>

static struct timer_list mytimer;

static void mytimer_function(unsigned long data){
	    printk("%s\n",__FUNCTION__);
	 
}

static int timer_init(void){
	int mydata=0x5555;
	init_timer(&mytimer);
	mytimer.expires=jiffies+2*HZ;
	mytimer.function=mytimer_function;
	mytimer.data=(unsigned long)&mydata;
	add_timer(&mytimer);
	printk("timer start counting!\n");
	return 0;
}

static void timer_exit(void){
	del_timer(&mytimer);
	printk("timer is over \n");
}

module_init(timer_init);
module_exit(timer_exit);
MODULE_LICENSE("GPL");
