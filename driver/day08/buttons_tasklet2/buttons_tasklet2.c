#include<linux/init.h>        //
#include<linux/module.h>      //module_init
#include<linux/fs.h>          //inode,file,file_operations
#include<linux/device.h>      //class,class_creat
#include<linux/cdev.h>        //cdev
#include<linux/uaccess.h>     //copy_to_user,copy_from_user
#include<linux/types.h>       //  
#include<linux/slab.h>    //kmalloc
#include<linux/irq.h>         //IRQ_EINT(n)
#include<linux/interrupt.h>   //request_irq,free_irq,tasklet
#include<asm/gpio.h>          //
#include<plat/gpio-cfg.h>     //

typedef struct{
  int irq;
  int irq_flags;
  irqreturn_t (*func)(int,void*);
}butn_irq;

typedef struct{
  unsigned long gpio;
  butn_irq *pirq;  
  char *name;  
}butn_resource;

typedef struct{
  int butn_num;
  butn_resource *pres;
}butn_device;

typedef struct{
  int major;
  struct cdev butn_cdev;
  struct class *cls;
  butn_device *pdev;
}butn_info;

butn_info *pb_info=NULL;

/////////////////////////////////////////

int butn_open(struct inode *inode,struct file *file){
    return 0;
}

int butn_close(struct inode *inode,struct file *file){
    return 0;
}

static struct file_operations butn_fops={
   .owner=THIS_MODULE,
   .open=butn_open,
   .release=butn_close,
};

void tasklet_handler1(unsigned long data){
     printk("occur tasklet1 handler!\n");
}

void tasklet_handler2(unsigned long data){
     printk("occur tasklet2 handler!\n");
}

static DECLARE_TASKLET(butn_tasklet1 , tasklet_handler1, 10);
static DECLARE_TASKLET(butn_tasklet2 , tasklet_handler2, 10);

irqreturn_t butn_irq_handler1(int irq,void *dev_id){
   printk("buttons1 irq occur!\n");
   tasklet_schedule(&butn_tasklet1);
   return IRQ_HANDLED;
};

irqreturn_t butn_irq_handler2(int irq,void *dev_id){
   printk("buttons2 irq occur!\n");
   tasklet_schedule(&butn_tasklet2);
   return IRQ_HANDLED;
};

irqreturn_t butn_irq_handler3(int irq,void *dev_id){
   printk("buttons3 irq occur!\n");
   return IRQ_HANDLED;
};

irqreturn_t butn_irq_handler4(int irq,void *dev_id){
   printk("buttons4 irq occur!\n");
   return IRQ_HANDLED;
}; 




butn_irq birq[]={
  [0]={
  .irq=IRQ_EINT(16),
  .irq_flags=IRQF_TRIGGER_FALLING,
  .func=butn_irq_handler1
  },
  [1]={
  .irq=IRQ_EINT(17),
  .irq_flags=IRQF_TRIGGER_FALLING,
  .func=butn_irq_handler2
  },
  [2]={
  .irq=IRQ_EINT(18),
  .irq_flags=IRQF_TRIGGER_FALLING,
  .func=butn_irq_handler3
  },
  [3]={
  .irq=IRQ_EINT(19),
  .irq_flags=IRQF_TRIGGER_FALLING,
  .func=butn_irq_handler4
  }
};


butn_resource bres[]={
    [0]={
    .gpio=S5PV210_GPH2(0),
    .pirq=birq,
    .name="BUTTONS1_IRQ"
    }, 
    [1]={
    .gpio=S5PV210_GPH2(1),
    .pirq=birq+1,
    .name="BUTTONS2_IRQ"
    },    
    [2]={
    .gpio=S5PV210_GPH2(2),
    .pirq=birq+2,
    .name="BUTTONS3_IRQ"
    },
    [3]={
    .gpio=S5PV210_GPH2(3),
    .pirq=birq+3,
    .name="BUTTONS4_IRQ"
    }
};

butn_device bdev={
  .butn_num=sizeof(bres)/sizeof(bres[0]),
  .pres=bres
};

//////////////////////////////////////////////////

static int buttons_init(void){
      dev_t dev_id;
      int i;
      butn_device *p=NULL;
      butn_resource *pr=NULL;
      butn_irq *pi=NULL;
      //分配私有内存
      pb_info=kmalloc(sizeof(butn_info),GFP_KERNEL);
      memset(pb_info,0,sizeof(butn_info));
      //自动分配设备号
      alloc_chrdev_region(&dev_id,0,1,"BUTTON_IRQ");
      pb_info->major=MAJOR(dev_id);
      //描述字符设备的相关特性
      cdev_init(&(pb_info->butn_cdev),&butn_fops);
      cdev_add(&(pb_info->butn_cdev),dev_id,1);
      //自动创建设备节点 
      pb_info->cls=class_create(THIS_MODULE,"BUTTONS");
      device_create(pb_info->cls,NULL,dev_id,NULL,"BUTTON_IRQ");
      pb_info->pdev=&bdev;

       p=pb_info->pdev;
       pr=p->pres;
   for(i=0;i<p->butn_num;i++){
       pi=pr[i].pirq;
      gpio_request(pr[i].gpio,pr[i].name);
    if(request_irq(pi->irq,pi->func,pi->irq_flags,pr[i].name,pb_info)){
       printk("buttons request irq failed!\n");
       return -1;
      }
    }
      printk("register buttons device successfully!\n");
      return 0;
}

static void buttons_exit(void){
      butn_device *p=pb_info->pdev;
      butn_resource *pr=p->pres;
      butn_irq *pi=NULL;
      int i;
    dev_t dev_id=MKDEV(pb_info->major,0);
    //删除设备节点
    device_destroy(pb_info->cls,dev_id);
    class_destroy(pb_info->cls);
    //删除cdev
    cdev_del(&pb_info->butn_cdev);
    //删除设备号
    unregister_chrdev_region(dev_id,1);
   for(i=0;i<p->butn_num;i++){
    pi=pr[i].pirq;
    free_irq(pi->irq,pb_info);     
    gpio_free(pr[i].gpio);
    }
    //释放似有内存
    kfree(pb_info);
    pb_info=NULL;
    printk("remove buttons device successfully!\n");    
}

module_init(buttons_init);
module_exit(buttons_exit);

MODULE_LICENSE("GPL");
