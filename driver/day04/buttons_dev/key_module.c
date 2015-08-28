#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/uaccess.h>
#include<linux/cdev.h>
#include<linux/types.h>
#include<asm/gpio.h>
#include<plat/gpio-cfg.h>

static int major=200;

typedef struct{
    int num;
    int state;
}key;
 
typedef struct {
  unsigned long gpio;
  char *name;
}key_resource;

key_resource key_info[]={
  [0]={
     .gpio=S5PV210_GPH2(0),
     .name="GPH2_0",
  },
  [1]={
     .gpio=S5PV210_GPH2(1),
     .name="GPH2_1",
  },
  [2]={
     .gpio=S5PV210_GPH2(2),
     .name="GPH2_2",
  },
  [3]={
     .gpio=S5PV210_GPH2(3),
     .name="GPH2_3",
  }
};
static ssize_t key_read(struct file *file,  char __user *buf, size_t size, loff_t *ppos)
{
         key k1={0};
//       state=gpio_get_value(key_info[0].gpio);
         k1.state=gpio_get_value(key_info[k1.num].gpio);

//     if(copy_to_user(buf,&state,sizeof(state))){
     if(copy_to_user(buf,&k1,sizeof(k1))){
       printk("read buf failed!\n");
       return -1;
     }   
      return size;
}

//分配cdev
static struct cdev key_cdev;
static struct class *cls;
static struct file_operations key_fops={
     .owner=THIS_MODULE,
     .read=key_read,
};
 
module_param(major,int,0);

static int key_init(void){
   //分配设备号
     dev_t dev_id;
     int retval;
     int i;
   if(major){
       dev_id=MKDEV(major,0);
       retval=register_chrdev_region(dev_id,1,"key");
   }
   else{
       retval= alloc_chrdev_region(&dev_id,0,1,"key");
       major=MAJOR(dev_id);
   }
    if(retval){
       printk("register led device failed\n");
       return -1;
    }
      //初始化cdev
      cdev_init(&key_cdev,&key_fops);
     //注册cdev
      cdev_add(&key_cdev,dev_id,1);
      
      cls=class_create(THIS_MODULE,"key");
      device_create(cls,NULL,dev_id,NULL,"key");
    //申请gpio资源
    for(i=0;i<(sizeof(key_info)/sizeof(key_info[1]));i++){
      gpio_request(key_info[i].gpio,key_info[i].name);
      gpio_direction_input(key_info[i].gpio);
    }
      printk("register key device successfully!\n");

     return 0;
}

static void key_exit(void){
     dev_t dev_id;
     int i;
     dev_id=MKDEV(major,0);
     device_destroy(cls,dev_id);
     class_destroy(cls);
     unregister_chrdev_region(dev_id,1);

    for(i=0;i<(sizeof(key_info)/sizeof(key_info[1]));i++)
        gpio_free(key_info[i].gpio);

     printk("remove led_device successfully!\n");        
}

module_init(key_init);
module_exit(key_exit);

MODULE_LICENSE("GPL");
