#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/kernel.h>
#include<linux/device.h>
#include<linux/cdev.h>
#include<linux/kdev_t.h>
#include<linux/types.h>

static int major=200;
static int count=1;
module_param(major,int,0);
module_param(count,int,0);

static int char_register_init(void){
         int ret;
         dev_t   dev_id;
	
         if(major){
		printk("static device number\n");
		dev_id=MKDEV(major,0);
                ret=register_chrdev_region(dev_id , count , "hello");	
		printk("%d\n",major);
         }
	 else{
	 	printk("alloc device number\n");
	        ret=alloc_chrdev_region(&dev_id  , 0  , count , "hello");
		major=MAJOR(dev_id);
		printk("%d\n",major);
	 }
	    if(ret){
	 	printk("device error\n");
                return -1;
             }
             return 0;
}

static void char_register_exit(void){
       	 dev_t dev_id=MKDEV(major,0);
         unregister_chrdev_region(dev_id,count);
}

module_init(char_register_init);
module_exit(char_register_exit);


MODULE_LICENSE("GPL");

