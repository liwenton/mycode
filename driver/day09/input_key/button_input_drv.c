#include <linux/init.h>
#include <linux/module.h>
#include <linux/input.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <asm/gpio.h>
#include <plat/gpio-cfg.h>

//����Ӳ��˽�нṹ��
struct button_resource {
	char *name;
	unsigned int gpio;
	int irq;
	int code;
};

//��ʼ���忨������Դ��Ϣ
static struct button_resource btn_info[] = {
	[0] = {
		.name = "KEY_L",
		.gpio = S5PV210_GPH2(0),
		.irq = IRQ_EINT(0),
		.code = KEY_L
	},
	[1] = {
		.name = "KEY_S",
		.gpio = S5PV210_GPH2(1),
		.irq = IRQ_EINT(1),
		.code = KEY_S
	},
	[2] = {
		.name = "KEY_ENTER",
		.gpio = S5PV210_GPH2(2),
		.irq = IRQ_EINT(2),
		.code = KEY_ENTER
	},
};

static struct input_dev *btn_dev;

static irqreturn_t button_isr(int irq,
								void *data)
{
	/*1.��ȡ������Ӧ��˽��Ӳ����Ϣ*/
	struct button_resource *p = 
			(struct button_resource *)data;

	/*2.�жϰ���״̬*/
	unsigned int  pinstate = 
				gpio_get_value(p->gpio);

	/*3.�ϱ�������Ϣ*/
	if (pinstate) { //�ɿ�
		input_event(btn_dev, 
					EV_KEY, p->code, 0);
		input_sync(btn_dev);
	} else { //����
		input_event(btn_dev, 
					EV_KEY, p->code, 1);
		input_sync(btn_dev);
	}
	return IRQ_HANDLED;
}

static int button_init(void)
{
	int i;
	
	/*1.����input_dev*/
	btn_dev = input_allocate_device();
	
	/*2.��ʼ��input_dev*/
	/*2.1ָ���ϱ���Щ�¼�*/
	set_bit(EV_KEY, btn_dev->evbit);//�ϱ��������¼�
	set_bit(EV_REP, btn_dev->evbit);//�ظ����¼�

	/*2.2�ϱ��������¼��е���Щ�¼�*/
	for(i = 0; i < ARRAY_SIZE(btn_info); i++) {
		set_bit(btn_info[i].code,
					btn_dev->keybit);
	}

	/*2.3������ʼ��*/
	btn_dev->name = "tarena_button";
	
	/*3.ע��input_dev*/
	input_register_device(btn_dev);
	
	/*4.����GPIO��Դ��ע���ж�*/
	for (i = 0; i < ARRAY_SIZE(btn_info); i++) {
		gpio_request(btn_info[i].gpio, 
						btn_info[i].name);
		request_irq(btn_info[i].irq, 
					button_isr,
		IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,	
		btn_info[i].name, &btn_info[i]);
	}
	return 0;
}

static void button_exit(void)
{
	int i;
	
	/*1.�ͷ��жϺ�GPIO��Դ*/
	for (i = 0; i < ARRAY_SIZE(btn_info); i++) {
		free_irq(btn_info[i].irq,
					&btn_info[i]);
		gpio_free(btn_info[i].gpio);
	}
	
	/*2.ж��input_dev*/
	input_unregister_device(btn_dev);
	
	/*3.�ͷ�input_dev*/
	input_free_device(btn_dev);
}
module_init(button_init);
module_exit(button_exit);
MODULE_LICENSE("GPL v2");
