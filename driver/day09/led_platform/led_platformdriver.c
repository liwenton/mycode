#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/slab.h>
#include<linux/cdev.h>
#include<linux/mm.h>
#include<linux/io.h>
#include<linux/uaccess.h>
#include<linux/platform_device.h>

#define GPIOCON 0x00
#define GPIODAT 0X04

struct led_priv{
    int major;
    struct cdev led_cdev;
    struct class *cls;
    unsigned long *gpio_base;
    int pin;
};

int led_open(struct inode *inode,struct file *file){
           unsigned int cur;
  struct led_priv *pled=container_of(inode->i_cdev,struct led_priv,led_cdev);

            file->private_data=pled; 
                                
           cur=readl(pled->gpio_base+GPIOCON);
           cur&=~((0xf)|(0xf<<4)|(0xf<<8)|(0xf<<12));
           cur|=(1|1<<4|1<<8|1<<12);
           writel(cur,pled->gpio_base+GPIOCON);
/*

           cur=readl(pled->gpio_base+GPIODAT);
           cur|=0xf;
           writel(cur,pled->gpio_base+GPIODAT);
*/
           printk("led_int\n");
           return 0;
}

int led_close(struct inode *inode,struct file *file){
           unsigned int cur;
           struct led_priv *pled=file->private_data;
  
 /*        cur&=~0xf;
           writel(cur,pled->gpio_base+GPIODAT);
 */
           printk("led_exit\n");
           return 0;
}
struct file_operations led_fops={
    .owner=THIS_MODULE,
    .open=led_open,
//    .ioctl=led_ioctl,
    .release=led_close
};

static int led_probe(struct platform_device *pdev){
    struct led_priv *pled;
    struct resource *reg_res;
    struct resource *pin_res;
    int size;
    dev_t dev_id;
    pled=kzalloc(sizeof(struct led_priv),GFP_KERNEL);
    
    reg_res=platform_get_resource(pdev,IORESOURCE_MEM,0);
    pin_res=platform_get_resource(pdev,IORESOURCE_IRQ,0);

    size=reg_res->end-reg_res->start+1;
    pled->gpio_base=ioremap(reg_res->start,size);
    pled->pin=pin_res->start;

    alloc_chrdev_region(&dev_id,0,1,"leds");
    pled->major=MAJOR(dev_id);

    cdev_init(&pled->led_cdev,&led_fops);
    cdev_add(&pled->led_cdev,dev_id,1);

    pled->cls=class_create(THIS_MODULE,"LED");
    device_create(pled->cls,NULL,dev_id,NULL,"leds");

    dev_set_drvdata(&pdev->dev,pled);
    printk("led_probe\n");
        return 0;
		
}

static int led_remove(struct platform_device *pdev){
     struct led_priv *pled=dev_get_drvdata(&pdev->dev);
      dev_t dev_id=MKDEV(pled->major,0);

      device_destroy(pled->cls,dev_id);
      class_destroy(pled->cls);
    
      cdev_del(&pled->led_cdev);

      unregister_chrdev_region(dev_id,1);
   
      iounmap(pled->gpio_base);
    
      kfree(pled);
    printk("led_remove\n");
    
	return 0;
}

struct platform_driver led_drv={
    .driver={
	.name="leds"
     },
    .probe=led_probe,
    .remove=led_remove
};

static int led_drv_init(void){

     platform_driver_register(&led_drv);   
                   return 0;
}

static void led_drv_exit(void){
     platform_driver_unregister(&led_drv);
}

module_init(led_drv_init);
module_exit(led_drv_exit);

MODULE_LICENSE("GPL");
