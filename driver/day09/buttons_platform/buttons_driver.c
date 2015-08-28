#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/mm.h>
#include<linux/io.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/uaccess.h>
#include<linux/slab.h>
#include<linux/platform_device.h>

struct butn_pri{
  int major;
  struct class *cls;
  struct cdev butn_cdev;
  unsigned long *gpio_base;
  int pin;
};

int butn_probe(struct platform_device *dev){
}

int butn_remove(struct platform_device *dev){
}
struct platform_driver butn_drv={
    .driver={
      .name="BUTTONS",
     },
     .probe  =butn_probe,
     .remove =butn_remove
};

static int butn_drv_init(void){
  platform_driver_register(&butn_drv);  
  return 0;
}

static void butn_drv_exit(void){
  platform_driver_unregister(&butn_drv);
}

module_init(butn_drv_init);
module_exit(butn_drv_exit);
MODULE_LICENSE("GPL");
