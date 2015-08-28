#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/device.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include<linux/i2c.h>

static struct i2c_device_id at24cxx_id[]={
		{"at24cxx",0},
		{}
};

struct at24cxx_info{
	int major;
	struct cdev dev;
	struct class *cls;
	struct i2c_client *client;
};

struct at24cxx_info *at24cxx_devp;

ssize_t at24cxx_read (struct file *file, char __user *buf, size_t size, loff_t *offset){
	unsigned char add;
	unsigned char data;
	int retval=0;
	struct i2c_msg msg[2];

	retval=copy_from_user(&add,buf,sizeof(add));
	
	msg[0].addr=at24cxx_devp->client->addr;
	msg[0].flags=0;
	msg[0].len=sizeof(add);
	msg[0].buf=&add;

	msg[1].addr=at24cxx_devp->client->addr;
	msg[1].flags=1; //¶Á
	msg[1].len=sizeof(data);
	msg[1].buf=&data;

	i2c_transfer(at24cxx_devp->client->adapter,msg,ARRAY_SIZE(msg));

	retval=copy_to_user(buf,&data,sizeof(data));

	return 0;
}
	

ssize_t  at24cxx_write (struct file *file, const char __user *buf, size_t size, loff_t *offset){
	
	unsigned char val[2];
	int retval=0;
	struct i2c_msg msg;
	
	if(size!=2){
		return EINVAL;
	}
	
	retval=copy_from_user(val,buf,sizeof(val));
	 msg.addr=at24cxx_devp->client->addr;
	 msg.flags=0;
         msg.len=sizeof(val);
	 msg.buf=val;
	  

      i2c_transfer(at24cxx_devp->client->adapter,&msg,1);

	  return 0;
	  
}

static struct file_operations at24cxx_fops={
	.owner=THIS_MODULE,
	.read=at24cxx_read,
	.write=at24cxx_write 
};

static int at24cxx_probe (struct i2c_client *client, const struct i2c_device_id *id){
	dev_t dev_id;
	printk("probe init\n");
	at24cxx_devp=kzalloc(sizeof(struct at24cxx_info),GFP_KERNEL);
	at24cxx_devp->client=client;
	
	alloc_chrdev_region(&dev_id, 0, 1, "at24cxx");
	at24cxx_devp->major=MAJOR(dev_id);
	
	cdev_init(&at24cxx_devp->dev,&at24cxx_fops);
	cdev_add(&at24cxx_devp->dev, dev_id, 1);
	
	at24cxx_devp->cls=class_create(THIS_MODULE, "I2C");
	device_create(at24cxx_devp->cls, NULL, dev_id, NULL,"at24cxx");

	return 0;
}


static int at24cxx_remove (struct i2c_client *client){
	dev_t dev_id=MKDEV(at24cxx_devp->major,0);
	device_destroy(at24cxx_devp->cls,dev_id);
	class_destroy(at24cxx_devp->cls);
	cdev_del(&at24cxx_devp->dev);
	unregister_chrdev_region(dev_id, 1);
	kfree(at24cxx_devp);
	return 0;
}

static struct i2c_driver at24cxx_drv={
	.driver={
	    .name="at24cxx",
	    .owner=THIS_MODULE
	},
	.probe=at24cxx_probe,
	.remove=at24cxx_remove,
	.id_table=at24cxx_id
};

static int at24cxx_init(void){
	i2c_add_driver(&at24cxx_drv);
 	return 0;
}

static void at24cxx_exit(void){
	i2c_del_driver(&at24cxx_drv);
}


module_init(at24cxx_init);
module_exit(at24cxx_exit);

MODULE_LICENSE("GPL");
