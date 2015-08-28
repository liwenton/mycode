#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/mm.h>
#include<linux/uaccess.h>
#include<linux/io.h>
#include<linux/slab.h>
struct reg_dev{
   unsigned int gpio;
   unsigned int data;
};

struct reg_info{
	int major;
	void *gpio_base;
	struct cdev reg_cdev;
	struct class *cls;
	struct reg_dev regs;
};


static struct reg_info *regp;

long reg_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
         struct reg_dev dreg;
         dreg.gpio=cmd;
         copy_from_user(&dreg.data,(unsigned int*)arg,4);
         printk("gpio:%u\n",dreg.gpio);
         printk("data:%u\n",dreg.data);

         regp->gpio_base=ioremap(dreg.gpio,4);
         writel(dreg.data,regp->gpio_base);
         iounmap(regp->gpio_base);
          return 0;
}
static struct file_operations reg_fops={
	.owner=THIS_MODULE,
	.unlocked_ioctl=reg_ioctl
};

static int reg_init(void){
	dev_t  dev_id;
	
	regp=kzalloc(sizeof(struct reg_info),GFP_KERNEL);
	
	alloc_chrdev_region(&dev_id, 0, 1 , "register_editor");
	regp->major=MAJOR(dev_id);
	
	cdev_init(&regp->reg_cdev,&reg_fops);
	cdev_add(&regp->reg_cdev, dev_id, 1);
	
	regp->cls=class_create(THIS_MODULE, "REGS");
	
	device_create(regp->cls, NULL,dev_id,NULL,"register_editor");
		
	return 0;
	
}

static void reg_exit(void){
	dev_t dev_id=MKDEV(regp->major,0);
	device_destroy(regp->cls, dev_id);
	class_destroy(regp->cls);
	cdev_del(&regp->reg_cdev);
	unregister_chrdev_region(dev_id, 1);
	kfree(regp);
}

module_init(reg_init);
module_exit(reg_exit);

MODULE_LICENSE("GPL");

