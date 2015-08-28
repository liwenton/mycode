#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/miscdevice.h>
#include<linux/device.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<asm/gpio.h>
#include<plat/gpio-cfg.h>

struct led_dev{
	unsigned long gpio;
	char *name;
};

static struct led_dev led_info[]={
   [0]={
	.gpio=S5PV210_GPJ2(0),
     	.name="GPJ2_0",
    }
};

static long led_ioctl (struct file *file, unsigned int cmd, unsigned long arg){
	int i;
	switch(cmd){
	case 0:
		     for(i=0;i<ARRAY_SIZE(led_info);i++)
		     gpio_set_value(led_info[i].gpio,0);
		     break;
	case 1:
		     for(i=0;i<ARRAY_SIZE(led_info);i++)
		     gpio_set_value(led_info[i].gpio,1);
		     break;
	default:printk("error command!\n");break;
	}
	return 0;  
};

struct file_operations led_fops={
	.owner=THIS_MODULE,
	.unlocked_ioctl=led_ioctl
};

struct miscdevice led_misc;

static int led_init(void){
	int i;
	led_misc.minor=MISC_DYNAMIC_MINOR;
	led_misc.name="led";
	led_misc.fops=&led_fops;
	misc_register(&led_misc);
	for(i=0;i<ARRAY_SIZE(led_info);i++){
	gpio_request(led_info[i].gpio,led_info[i].name);
	gpio_direction_output(led_info[i].gpio, 0);
	}
	return 0;
}

static void led_exit(void){
	int i;
	for(i=0;i<ARRAY_SIZE(led_info);i++)
	gpio_free(led_info[i].gpio);
	misc_deregister(&led_misc);
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");

