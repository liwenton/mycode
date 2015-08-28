moduel_param(delay,int,0)
module_param_array(name,type,NULL,0);
module_param_array(name,type,NULL,0);
container
container(inode->i_cdev,struct led_priv,led_cdev);
container(inode->i_cdev,struct led_priv,led_cdev);
container(inode->i_cdev,struct led_priv,led_cdev);
container(inode->i_cdev,struct led_priv,led_cdev);
struct timer_list
struct timer_list
struct timer_list
struct timer_list
linux/timer.h
init_timer(&mytimer)
mytimer.expries=jiffies+2*HZ;
mytimer.expries=jiffies+2*HZ
mytimer.expries=jiffies+5*HZ
mytimer.expries=jiffies+6*HZ
add_timer(&mytimer);
mod_timer(&mytimer);
mod_timer(&mytiemr,jiffies+2*HZ);
mod_timer(msec
usec_to_jiffies
msecs_to_jiffies
usecs_to_jiffies'
msecs_to_jiffies
usecs_to_jiffies
irqreturn_t (int irq,void *dev)
irqreturn_t (int irq,void *dev)
irqreturn_t (int irq,void *dev)
IRQF_TRIGGER_NONE
IRQF_TRIGGER_RISING
IRQF_TRIGGER_RISING
IRQF_TRIGGER_FALLING
IRQF_TRIGGER_MAST
request_irq(IRQ_EINT(16),buttons_isr,IRQF_TRIGGER_FALLING,"led",NULL);
requset_irq(IRQ_EINT(16),BUTTON_isr,IRQF_TRIGGER_FALLING
free_irq
free_irq
free_irq
free_rq
