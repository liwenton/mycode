#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/mm.h>
#include<linux/io.h>
#include<linux/uaccess.h>
#include<linux/slab.h>

#define GPIOCON   0x00
#define GPIODAT   0x04  
int cur;

struct led_private {
   int major;
   struct cdev led_cdev;
   struct class *cls;
    void *gpio_base;    //´æ·Å¼Ä´æÆ÷µÄÐéÄâµØÖ·
};

typedef struct {
  unsigned long add;
  unsigned long dat;
}reg;

static struct led_private *pled=NULL;


int led_open(struct inode*inode,struct file*file){
	 //unsigned long *gpiocon,*gpiodata;
	 struct led_private *pledp=container_of(inode->i_cdev,struct led_private,led_cdev);
	 file->private_data=pledp;
      /*	 gpiocon=(unsigned long*)pledp->gpio_base;
	 gpiodata=gpiocon+1;
	 
	 *gpiocon&=~((0xf)|(0xf<<4)|(0xf<<8)|(0xf<<12));
	 *gpiocon|=(1|1<<4|1<<8|1<<12);
	 
	 *gpiodata&=~0xf;
       
        //////////////////////////////////////////////
           cur=readl(pledp->gpio_base+GPIOCON);
           cur&=~((0xf)|(0xf<<4)|(0xf<<8)|(0xf<<12));
           cur|=(1|1<<4|1<<8|1<<12);
           writel(cur,pledp->gpio_base+GPIOCON);

           cur=readl(pledp->gpio_base+GPIODAT);
           cur&=~0xf;
           writel(cur,pledp->gpio_base+GPIODAT);
       */
	   return 0;
}

static long led_ioctl(struct file *file,unsigned int cmd,unsigned long arg){
        reg device;
         struct led_private *pledp=file->private_data;
         copy_from_user(&device,(reg *)arg,sizeof(device));   
            pled->gpio_base=ioremap(device.add,4);

      switch(cmd){
        case 1:
               cur=readl(pledp->gpio_base);
               cur|=device.dat;
               writel(cur,pledp->gpio_base); 
               break;
        case 0:
               cur=readl(pledp->gpio_base);
               device.dat=cur;
               copy_to_user((reg *)arg,&device,sizeof(device));
	       break;
        default:
	       printk("kernel without this cmd!\n");
	       break;
      } 
       return 0;
}
int led_close (struct inode *inode, struct file *file){
//	 unsigned long *gpiocon,*gpiodata;
	 struct led_private *pledp=file->private_data;
/*         gpiocon=(unsigned long*)pledp->gpio_base;
	 gpiodata=gpiocon+1;
	 *gpiodata|=0xf;
*/
	  iounmap(pledp->gpio_base);
          return 0;
}

struct file_operations led_fops={
	.owner=THIS_MODULE,
	.open=led_open,
        .unlocked_ioctl=led_ioctl, 
	.release=led_close
};

static int led_init(void){
	dev_t dev_id;
      pled=kzalloc(sizeof(struct led_private),GFP_KERNEL);
      alloc_chrdev_region(&dev_id,0,1,"leds");
      pled->major=MAJOR(dev_id);
      cdev_init(&pled->led_cdev,&led_fops);
      cdev_add(&pled->led_cdev,dev_id,1);
      pled->cls=class_create(THIS_MODULE,"LEDS");
      device_create(pled->cls,NULL,dev_id,NULL,"leds");
         return 0;
}

static void led_exit(void){  
	  dev_t dev_id=MKDEV(pled->major,0);
	  device_destroy(pled->cls,dev_id);
	  class_destroy(pled->cls);
	  cdev_del(&pled->led_cdev);
	  unregister_chrdev_region(dev_id,1);
	  kfree(pled);
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
