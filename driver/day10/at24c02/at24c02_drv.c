#include <linux/init.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
static struct i2c_device_id at24c02_id[] = {
	  	{"at24cxx", 0}
};

static int major;
static struct class *cls;
static struct i2c_client *g_client;

static ssize_t at24c02_read(struct file *file,
					char __user *buf,
					size_t count,
					loff_t *ppos)
{
	unsigned char addr;
	unsigned char data;

	/*1.获取用户要访问地址*/
	copy_from_user(&addr, buf, 1);

	/*2.查看内核SMBUS操作接口，在根据芯片
		读的操作时序，选择对应的函数来实现
		将数据信息发送给总线驱动来传输
	*/
	data = i2c_smbus_read_byte_data(g_client, addr);
	if (data < 0) {
		printk("read error!\n");
		return -EIO;
	}

	/*3.拷贝数据到用户空间*/
	copy_to_user(buf, &data, 1);
	return count;
}

static ssize_t at24c02_write(struct file *file,
					char __user *buf,
					size_t count,
					loff_t *ppos)
{
	unsigned char buffer[2];
	unsigned char addr;
	unsigned char data;

	/*1.获取用户要操作的地址和数据信息*/
	copy_from_user(buffer, buf, 2);
	addr = buffer[0];
	data = buffer[1];
	
	/*2.采用SMBUS接口将数据信息丢给总线驱动来实现
		最底层硬件操作，SMBUS具体的操作方法
		参看Documentation\i2c\smbus-protocol
		根据此文档然后再根据设备的芯片手册具体的操作
		时序，找到对应的操作接口函数使用即可
	*/
	if (i2c_smbus_write_byte_data(g_client, addr, data) < 0)
	{
		printk("write error!\n");
		return -EIO;
	}
	return count;
}

static struct file_operations at24c02_fops = {
	.owner = THIS_MODULE,
	.read = at24c02_read,
	.write = at24c02_write
};

//client指针指向内核创建好的i2c_client硬件信息
static int at24c02_probe(struct i2c_client *client, 
				const struct i2c_device_id *id)
{
      printk("in probe function\n");
	/*1.注册字符设备*/
	major = register_chrdev(major, "at24c02",
							&at24c02_fops);

	cls = class_create(THIS_MODULE, "at24c02");
	device_create(cls, NULL, 
			MKDEV(major, 0), NULL, "at24c02");

	g_client = client;

	return 0;
}
static int at24c02_remove(struct i2c_client *client)
{
	device_destroy(cls, MKDEV(major, 0));
	class_destroy(cls);
	unregister_chrdev(major, "at24c02");
	return 0;
}

//分配初始化i2c_driver
static struct i2c_driver at24c02_drv = {
	.driver = {
		.name = "tarena"
	},
	.probe = at24c02_probe,
	.remove = at24c02_remove,
	.id_table = at24c02_id
};

static int at24c02_init(void)
{
	i2c_add_driver(&at24c02_drv);
	return 0;
}

static void at24c02_exit(void)
{
	i2c_del_driver(&at24c02_drv);
}

module_init(at24c02_init);
module_exit(at24c02_exit);
MODULE_LICENSE("GPL v2");
