#include<linux/init.h>
#include<linux/module.h>   //module_init
#include<linux/fs.h>          //file,inode,file_operations
#include<linux/device.h>  //class create   deviece create
#include<linux/uaccess.h>   //copy_to_user
#include<linux/cdev.h>     //cdev
#include<linux/types.h>
#include<linux/slab.h>    //kmalloc
#include<asm/gpio.h>
#include<plat/gpio-cfg.h>

#define LED_MAJOR   250;
#define LED_ON    0
#define LED_OFF   1

//定义一个硬件私有结构体
typedef struct {
  unsigned long gpio;
  char *name;
}led_resource;

typedef struct{
  int led_num;
  led_resource *press;
}led_info;

struct led_priv{
      int major;
      struct class *cls; 
      struct cdev led_cdev; 
      led_info *info; 
};

led_resource led_dev[]={
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
     .name="GPJ2_3"
  }
};

led_info leds={
  .led_num=4,
  .press=led_dev
};

static struct led_priv *pled=NULL;

static int led_open(struct inode *inode,struct file *file){
         int i;
	 struct led_priv *ptr=container_of(inode->i_cdev,struct led_priv,led_cdev);
	 led_info *p=ptr->info;
         led_resource *l=p->press; 
	 file->private_data =ptr;
        for(i=0;i<p->led_num;i++){
         gpio_request(l[i].gpio,l[i].name);
	 gpio_direction_output(l[i].gpio,1);
         }
	 return 0;
}

static int led_close(struct inode *inode,struct file *file){
         int i;
	struct led_priv *ptr=file->private_data;
	 led_info *p=ptr->info;
         led_resource *l=p->press; 
       for(i=0;i<p->led_num;i++)
	gpio_free(l[i].gpio);
	return 0;
}

long led_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
          int i;
	struct led_priv *ptr=file->private_data;
	 led_info *p=ptr->info;
         led_resource *l=p->press; 
	switch(cmd){
	case LED_ON:
                                for(i=0;i<p->led_num;i++)
				gpio_set_value(l[i].gpio,0);
				break;
	case LED_OFF:
                                for(i=0;i<p->led_num;i++)
				gpio_set_value(l[i].gpio,1);
				break;
	default :
		     printk("without this led cmd!\n");
	             return -1;
	}
	return 0;
	
}

static struct file_operations led_fops={
     .owner=THIS_MODULE,
     .open= led_open,
      .release =led_close,
      .unlocked_ioctl=led_ioctl
};

static int led_init(void){
	dev_t  dev_id;
    pled=kmalloc(sizeof(struct led_priv),GFP_KERNEL);
    memset(pled,0,sizeof(struct led_priv));
      pled->major=LED_MAJOR;
     if(pled->major){
	 dev_id=MKDEV(pled->major, 0);
	 register_chrdev_region(dev_id,1,"led_inode");
      }
      else{
	  alloc_chrdev_region(&dev_id,0,1,"led_inode");
	  pled->major=MAJOR(dev_id);
      	}
        cdev_init(&(pled->led_cdev),&led_fops);
        cdev_add(&(pled->led_cdev),dev_id,1);
        pled->cls=class_create(THIS_MODULE,"leds");
        device_create(pled->cls,NULL,dev_id,NULL,"led_inode");
        pled->info=&leds;
        printk("register led_device successfully!\n");
	return 0;
    
}

static void led_exit(void){
	dev_t dev_id=MKDEV(pled->major,0);
    //删除设备节点
        device_destroy(pled->cls,dev_id);
    //删除设备类
        class_destroy(pled->cls);
    //卸载cdev
       cdev_del(&pled->led_cdev);
    //释放设备号
      unregister_chrdev_region(dev_id,1);
    //释放内存
      kfree(pled);
      pled=NULL;
     printk("remove led_device successfully!\n");
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
