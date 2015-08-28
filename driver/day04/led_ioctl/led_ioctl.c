#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/types.h>
#include<linux/uaccess.h>
#include<asm/gpio.h>
#include<plat/gpio-cfg.h>
#include<linux/slab.h>
static int major=250;

typedef struct {
  unsigned long gpio;
  char *name;
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
  }
};

static long led_ioctl(struct file *file,unsigned int cmd,unsigned long arg)
{
          int index;
     if(copy_from_user(&index, (int *)arg, 4)){
         printk("copy failed\n");
         return -1;
     }
      printk("led%d %d\n",cmd,index);
      gpio_set_value(led_info[cmd].gpio,index);
     return 0;
}

static struct cdev led_cdev;
static struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .unlocked_ioctl = led_ioctl
};

static int led_init(void){
    dev_t dev_id;
    int retval,i;
   if(major){
       dev_id=MKDEV(major,0);
       retval=register_chrdev_region(dev_id,1,"led");
   }
   else{
       retval=alloc_chrdev_region(&dev_id,0,1,"led");
       major=MAJOR(dev_id);
   }
     if(retval){
     printk("register led device failed\n");
     return -1;
     }
     cdev_init(&led_cdev,&led_fops);
     cdev_add(&led_cdev,dev_id,1);

    for(i=0;i<(sizeof(led_info)/sizeof(led_info[1]));i++){
      gpio_request(led_info[i].gpio,led_info[i].name);
      gpio_direction_output(led_info[i].gpio,1);
    }
      printk("register led device successfully!\n");

     return  0;
  }

static void led_exit(void){
     dev_t dev_id;
     int i;
     dev_id=MKDEV(major,0);
     unregister_chrdev_region(dev_id,1);

    for(i=0;i<(sizeof(led_info)/sizeof(led_info[1]));i++)
        gpio_free(led_info[i].gpio);

     printk("remove led_device successfully!\n");
}

module_init(led_init);
module_exit(led_exit);


MODULE_LICENSE("GPL");
