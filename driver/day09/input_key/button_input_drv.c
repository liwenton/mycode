#include <linux/init.h>
#include <linux/module.h>
#include <linux/input.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <asm/gpio.h>
#include <plat/gpio-cfg.h>

//定义硬件私有结构体
struct button_resource {
	char *name;
	unsigned int gpio;
	int irq;
	int code;
};

//初始化板卡按键资源信息
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
	/*1.获取按键对应的私有硬件信息*/
	struct button_resource *p = 
			(struct button_resource *)data;

	/*2.判断按键状态*/
	unsigned int  pinstate = 
				gpio_get_value(p->gpio);

	/*3.上报按键信息*/
	if (pinstate) { //松开
		input_event(btn_dev, 
					EV_KEY, p->code, 0);
		input_sync(btn_dev);
	} else { //按下
		input_event(btn_dev, 
					EV_KEY, p->code, 1);
		input_sync(btn_dev);
	}
	return IRQ_HANDLED;
}

static int button_init(void)
{
	int i;
	
	/*1.分配input_dev*/
	btn_dev = input_allocate_device();
	
	/*2.初始化input_dev*/
	/*2.1指定上报哪些事件*/
	set_bit(EV_KEY, btn_dev->evbit);//上报按键类事件
	set_bit(EV_REP, btn_dev->evbit);//重复类事件

	/*2.2上报按键类事件中的哪些事件*/
	for(i = 0; i < ARRAY_SIZE(btn_info); i++) {
		set_bit(btn_info[i].code,
					btn_dev->keybit);
	}

	/*2.3其它初始化*/
	btn_dev->name = "tarena_button";
	
	/*3.注册input_dev*/
	input_register_device(btn_dev);
	
	/*4.申请GPIO资源和注册中断*/
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
	
	/*1.释放中断和GPIO资源*/
	for (i = 0; i < ARRAY_SIZE(btn_info); i++) {
		free_irq(btn_info[i].irq,
					&btn_info[i]);
		gpio_free(btn_info[i].gpio);
	}
	
	/*2.卸载input_dev*/
	input_unregister_device(btn_dev);
	
	/*3.释放input_dev*/
	input_free_device(btn_dev);
}
module_init(button_init);
module_exit(button_exit);
MODULE_LICENSE("GPL v2");
