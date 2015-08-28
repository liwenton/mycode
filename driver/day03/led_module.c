#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/kernel.h>
#include<linux/device.h>
#include<linux/cdev.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<asm/gpio.h>
#include<plat/gpio-cfg.h>

static int major=250;

typedef struct led{
    unsigned long gpio;
    char* name;
}led_resource;

led_resource led_info[]={
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
   },
};

static struct cdev led_cdev;

static int led_open(struct inode *inode,struct file *file){
   //配置GPIO为输出口
   //输出为0;
     int i;
    for(i=0;i<(sizeof(led_info)/sizeof(led_info[1]));i++)
      gpio_direction_output(led_info[i].gpio,0);

     return 0;
}

static int led_close(struct inode *inode,struct file *file){
      int i;
    for(i=0;i<(sizeof(led_info)/sizeof(led_info[1]));i++)
      gpio_set_value(led_info[i].gpio,1);

     return 0;
}

static struct file_operations led_fops={
    .owner=THIS_MODULE,
    .open=led_open,
    .release=led_close
};

module_param(major,int,0);

static int led_init(void){
     int retval,i;
     dev_t dev_id;
     if(major){
        dev_id=MKDEV(major,0);
        retval=register_chrdev_region(dev_id,1,"led");
     }
     else{
        retval=alloc_chrdev_region(&dev_id,0,1,"led");
        major=MAJOR(dev_id);
     }
     if(retval){
       printk("register led device error!\n");
       return -1;
     }
     //分配cdev
     //初始化cdev
        cdev_init(&led_cdev,&led_fops);
     //注册cdev
        cdev_add(&led_cdev,dev_id,1);
     //申请gpio资源
     for(i=0;i<(sizeof(led_info)/sizeof(led_info[1]));i++)
       gpio_request(led_info[i].gpio,led_info[i].name);
              
       printk("register led device successfully!\n");

      return 0;
}

static void led_exit(void){
    int i;
   dev_t dev_id=MKDEV(major,0);
   unregister_chrdev_region(dev_id,1);
     for(i=0;i<(sizeof(led_info)/sizeof(led_info[1]));i++)
       gpio_free(led_info[i].gpio);
}


module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
