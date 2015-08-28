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

	/*1.��ȡ�û�Ҫ���ʵ�ַ*/
	copy_from_user(&addr, buf, 1);

	/*2.�鿴�ں�SMBUS�����ӿڣ��ڸ���оƬ
		���Ĳ���ʱ��ѡ���Ӧ�ĺ�����ʵ��
		��������Ϣ���͸���������������
	*/
	data = i2c_smbus_read_byte_data(g_client, addr);
	if (data < 0) {
		printk("read error!\n");
		return -EIO;
	}

	/*3.�������ݵ��û��ռ�*/
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

	/*1.��ȡ�û�Ҫ�����ĵ�ַ��������Ϣ*/
	copy_from_user(buffer, buf, 2);
	addr = buffer[0];
	data = buffer[1];
	
	/*2.����SMBUS�ӿڽ�������Ϣ��������������ʵ��
		��ײ�Ӳ��������SMBUS����Ĳ�������
		�ο�Documentation\i2c\smbus-protocol
		���ݴ��ĵ�Ȼ���ٸ����豸��оƬ�ֲ����Ĳ���
		ʱ���ҵ���Ӧ�Ĳ����ӿں���ʹ�ü���
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

//clientָ��ָ���ں˴����õ�i2c_clientӲ����Ϣ
static int at24c02_probe(struct i2c_client *client, 
				const struct i2c_device_id *id)
{
      printk("in probe function\n");
	/*1.ע���ַ��豸*/
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

//�����ʼ��i2c_driver
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
