#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/uaccess.h>
#include<linux/cdev.h>
#include<linux/types.h>
#include<asm/gpio.h>
#include<plat/gpio-cfg.h>

static int major=250;
static int state;
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

static ssize_t led_read(struct file *file, const char __user *buf, size_t size, loff_t *ppos)
{
    if(state>1)
     state=gpio_get_value(led_info[0].gpio);

     if(copy_to_user(buf,&state,sizeof(state))){
       printk("read buf failed!\n");
       return -1;
     }   
      return size;
}
static ssize_t led_write(struct file *file, const char __user *buf, size_t size, loff_t *ppos)
{
      int val;
      int i;
      if(copy_from_user(&val,buf,sizeof(val))){
       printk("write buf failed!\n");
       return -1;
       }
     if(val==0){
        for(i=0;i<(sizeof(led_info)/sizeof(led_info[1]));i++)
            gpio_set_value(led_info[i].gpio,val);
      }
      else if(val==1){
        for(i=0;i<(sizeof(led_info)/sizeof(led_info[1]));i++)
            gpio_set_value(led_info[i].gpio,val);
     }
      state=val;       
      return size;
}

//分配cdev
static struct cdev led_cdev;
static struct file_operations led_fops={
     .owner=THIS_MODULE,
     .read=led_read,
     .write=led_write
};
 
module_param(major,int,0);
static int led_init(void){
   //分配设备号
     dev_t dev_id;
     int retval;
     int i;
   if(major){
       dev_id=MKDEV(major,0);
       retval=register_chrdev_region(dev_id,1,"led");
   }
   else{
       retval= alloc_chrdev_region(&dev_id,0,1,"led");
       major=MAJOR(dev_id);
   }
    if(retval){
       printk("register led device failed\n");
       return -1;
    }
      //初始化cdev
      cdev_init(&led_cdev,&led_fops);
     //注册cdev
      cdev_add(&led_cdev,dev_id,1);
    //申请gpio资源
    for(i=0;i<(sizeof(led_info)/sizeof(led_info[1]));i++){
      gpio_request(led_info[i].gpio,led_info[i].name);
      gpio_direction_output(led_info[i].gpio,1);
    }
      printk("register led device successfully!\n");

     return 0;
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
