#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/time.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/clk.h>
#include <linux/cpufreq.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/of_i2c.h>
#include <linux/of_gpio.h>
#include <plat/gpio-cfg.h>
#include <mach/regs-gpio.h>

#include <asm/irq.h>

#include <plat/regs-iic.h>
//#include <plat/iic.h>

//#define PRINTK printk
#define PRINTK(...) 

enum webee210_i2c_state {
	STATE_IDLE,
	STATE_START,
	STATE_READ,
	STATE_WRITE,
	STATE_STOP
};

struct webee210_i2c_regs {
	unsigned int iiccon;
	unsigned int iicstat;
	unsigned int iicadd;
	unsigned int iicds;
	unsigned int iiclc;
};

struct webee210_i2c_xfer_data {
	struct i2c_msg *msgs;
	int msn_num;
	int cur_msg;
	int cur_ptr;
	int state;
	int err;
	wait_queue_head_t wait;
};

static struct webee210_i2c_xfer_data webee210_i2c_xfer_data;
static struct webee210_i2c_regs *webee210_i2c_regs;
static unsigned long *gpd1con;
static unsigned long *gpd1pud;
static unsigned long *clk_gate_ip3;

static void webee210_i2c_start(void)
{
	webee210_i2c_xfer_data.state = STATE_START;
	
	if (webee210_i2c_xfer_data.msgs->flags & I2C_M_RD) /* �� */
	{
		webee210_i2c_regs->iicds		 = webee210_i2c_xfer_data.msgs->addr << 1;
	//	printk("slave = %x\n",webee210_i2c_xfer_data.msgs->addr);
		//webee210_i2c_regs->iicds		 = webee210_i2c_xfer_data.msgs->addr;
		webee210_i2c_regs->iicstat 	 = 0xb0;	// �������գ�����
	}
	else /* д */
	{
		webee210_i2c_regs->iicds		 = webee210_i2c_xfer_data.msgs->addr << 1;
		//webee210_i2c_regs->iicds		 = webee210_i2c_xfer_data.msgs->addr;
		webee210_i2c_regs->iicstat    = 0xf0; 		// �������ͣ�����
	}
}

static void webee210_i2c_stop(int err)
{
	webee210_i2c_xfer_data.state = STATE_STOP;
	webee210_i2c_xfer_data.err   = err;

	PRINTK("STATE_STOP, err = %d\n", err);


	if (webee210_i2c_xfer_data.msgs->flags & I2C_M_RD) /* �� */
	{
		// �������лָ�I2C����������P�ź�
		webee210_i2c_regs->iicstat = 0x90;
		webee210_i2c_regs->iiccon  = 0xaf;
		ndelay(50);  // �ȴ�һ��ʱ���Ա�P�ź��Ѿ�����
	}
	else /* д */
	{
		// �������������ָ�I2C����������P�ź�
		webee210_i2c_regs->iicstat = 0xd0;
		webee210_i2c_regs->iiccon  = 0xaf;
		ndelay(50);  // �ȴ�һ��ʱ���Ա�P�ź��Ѿ�����
	}

	/* ���� */
	wake_up(&webee210_i2c_xfer_data.wait);
	
}

static int webee210_i2c_xfer(struct i2c_adapter *adap,
			struct i2c_msg *msgs, int num)
{
	unsigned long timeout;
	
	/* ��num��msg��I2C���ݷ��ͳ�ȥ/������ */
	webee210_i2c_xfer_data.msgs    = msgs;
	webee210_i2c_xfer_data.msn_num = num;
	webee210_i2c_xfer_data.cur_msg = 0;
	webee210_i2c_xfer_data.cur_ptr = 0;
	webee210_i2c_xfer_data.err     = -ENODEV;
//	printk("...............................................\n");
	PRINTK("s3c2440_i2c_xfer \n");
	
	webee210_i2c_start();

	/* ���� */
	timeout = wait_event_timeout(webee210_i2c_xfer_data.wait, (webee210_i2c_xfer_data.state == STATE_STOP), HZ * 5);
	if (0 == timeout)
	{
	
		printk("webee210_i2c_xfer time out\n");
		return -ETIMEDOUT;
		//return webee210_i2c_xfer_data.err;
	}
	else
	{
		return webee210_i2c_xfer_data.err;
	}
}

static u32 webee210_i2c_func(struct i2c_adapter *adap)
{
	return I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL | I2C_FUNC_PROTOCOL_MANGLING;
}


static const struct i2c_algorithm webee210_i2c_algo = {
//	.smbus_xfer     = ,
	.master_xfer	= webee210_i2c_xfer,
	.functionality	= webee210_i2c_func,
};

/* 1. ����/����i2c_adapter
 */
static struct i2c_adapter webee210_i2c_adapter = {
 .name			 = "webee210_100ask",
 .algo			 = &webee210_i2c_algo,
 .owner 		 = THIS_MODULE,
};

static int isLastMsg(void)
{
	return (webee210_i2c_xfer_data.cur_msg == webee210_i2c_xfer_data.msn_num - 1);
}

static int isEndData(void)
{
	return (webee210_i2c_xfer_data.cur_ptr >= webee210_i2c_xfer_data.msgs->len);
}

static int isLastData(void)
{
	return (webee210_i2c_xfer_data.cur_ptr == webee210_i2c_xfer_data.msgs->len - 1);
}

static irqreturn_t webee210_i2c_xfer_irq(int irq, void *dev_id)
{
	unsigned int iicSt;
	iicSt  = webee210_i2c_regs->iicstat; 

	if(iicSt & 0x8){ printk("Bus arbitration failed\n\r"); }

	PRINTK("webee210_i2c_xfer_irq \n");

	switch (webee210_i2c_xfer_data.state)
	{
		case STATE_START : /* ����S���豸��ַ��,�����ж� */
		{
			PRINTK("Start\n");
			/* ���û��ACK, ���ش��� */
			if (iicSt & S3C2410_IICSTAT_LASTBIT)
			{
				webee210_i2c_stop(-ENODEV);
				break;
			}

			if (isLastMsg() && isEndData())
			{
				webee210_i2c_stop(0);
				break;
			}

			/* ������һ��״̬ */
			if (webee210_i2c_xfer_data.msgs->flags & I2C_M_RD) /* �� */
			{
				webee210_i2c_xfer_data.state = STATE_READ;
				goto next_read;
			}
			else
			{
				webee210_i2c_xfer_data.state = STATE_WRITE;
			}	
		}

		case STATE_WRITE:
		{
			PRINTK("STATE_WRITE\n");
			/* ���û��ACK, ���ش��� */
			if (iicSt & S3C2410_IICSTAT_LASTBIT)
			{
				webee210_i2c_stop(-ENODEV);
				break;
			}

			if (!isEndData())  /* �����ǰmsg��������Ҫ���� */
			{
				webee210_i2c_regs->iicds = webee210_i2c_xfer_data.msgs->buf[webee210_i2c_xfer_data.cur_ptr];
				webee210_i2c_xfer_data.cur_ptr++;
				
				// ������д��IICDS����Ҫһ��ʱ����ܳ�����SDA����
				ndelay(50);	
				
				webee210_i2c_regs->iiccon = 0xaf;		// �ָ�I2C����
				break;				
			}
			else if (!isLastMsg())
			{
				/* ��ʼ������һ����Ϣ */
				webee210_i2c_xfer_data.msgs++;
				webee210_i2c_xfer_data.cur_msg++;
				webee210_i2c_xfer_data.cur_ptr = 0;
				webee210_i2c_xfer_data.state = STATE_START;
				/* ����START�źźͷ����豸��ַ */
				webee210_i2c_start();
				break;
			}
			else
			{
				/* �����һ����Ϣ�����һ������ */
				webee210_i2c_stop(0);
				break;				
			}

			break;
		}

		case STATE_READ:
		{
			PRINTK("STATE_READ\n");
			/* �������� */
			webee210_i2c_xfer_data.msgs->buf[webee210_i2c_xfer_data.cur_ptr] = webee210_i2c_regs->iicds;			
			webee210_i2c_xfer_data.cur_ptr++;
next_read:
			if (!isEndData()) /* �������û��д, ������������� */
			{
				if (isLastData())  /* ��������������������һ��, ����ack */
				{
					webee210_i2c_regs->iiccon = 0x2f;   // �ָ�I2C���䣬���յ���һ����ʱ��ACK
				}
				else
				{
					webee210_i2c_regs->iiccon = 0xaf;   // �ָ�I2C���䣬���յ���һ����ʱ����ACK
				}				
				break;
			}
			else if (!isLastMsg())
			{
				/* ��ʼ������һ����Ϣ */
				webee210_i2c_xfer_data.msgs++;
				webee210_i2c_xfer_data.cur_msg++;
				webee210_i2c_xfer_data.cur_ptr = 0;
				webee210_i2c_xfer_data.state = STATE_START;
				/* ����START�źźͷ����豸��ַ */
				webee210_i2c_start();
				break;
			}
			else
			{
				/* �����һ����Ϣ�����һ������ */
				webee210_i2c_stop(0);
				break;								
			}
			break;
		}

		default: break;
	}

	/* ���ж� */
	webee210_i2c_regs->iiccon &= ~(S3C2410_IICCON_IRQPEND);

	return IRQ_HANDLED;	
}

/*
 * I2C��ʼ��
 */
static void webee210_i2c_init(void)
{
	/*ʹ��ʱ��*/
	*clk_gate_ip3 = 0xffffffff;

	// ѡ�����Ź��ܣ�GPE15:IICSDA, GPE14:IICSCL
	*gpd1con |= 0x22<<16;
	*gpd1pud |= 0x5<<8;
	
//	GPH1CON |= 0xf<<24;//EINT14 ENABLE


	/* bit[7] = 1, ʹ��ACK
	* bit[6] = 0, IICCLK = PCLK/16
	* bit[5] = 1, ʹ���ж�
	* bit[3:0] = 0xf, Tx clock = IICCLK/16
	* PCLK = 50MHz, IICCLK = 3.125MHz, Tx Clock = 0.195MHz
	*/
	webee210_i2c_regs->iiccon = (1<<7) | (0<<6) | (1<<5) | (0xf);  // 0xaf

	webee210_i2c_regs->iicadd = 0x10;     // S3C24xx slave address = [7:1]
	webee210_i2c_regs->iicstat = 0x10;     // I2C�������ʹ��(Rx/Tx)
}

static int i2c_bus_webee210_init(void)
{
	/* 2. Ӳ����ص����� */
	webee210_i2c_regs = ioremap(0xE1A00000, sizeof(struct webee210_i2c_regs));
	gpd1con = ioremap(0xE02000C0,4); 
	gpd1pud = ioremap(0xE02000C8,4);
	clk_gate_ip3 = ioremap(0xE010046C,4);
	
	webee210_i2c_init();

	if(request_irq(IRQ_IIC2, webee210_i2c_xfer_irq, 0, "webee210-i2c", NULL))
	{
		printk("request_irq failed");
		return -EAGAIN;
	}

	init_waitqueue_head(&webee210_i2c_xfer_data.wait);
	
	/* 3. ע��i2c_adapter */
	i2c_add_adapter(&webee210_i2c_adapter);
	
	return 0;
}

static void i2c_bus_webee210_exit(void)
{
	i2c_del_adapter(&webee210_i2c_adapter);	
	free_irq(IRQ_IIC, NULL);
	iounmap(webee210_i2c_regs);
}

module_init(i2c_bus_webee210_init);
module_exit(i2c_bus_webee210_exit);
MODULE_LICENSE("GPL");


