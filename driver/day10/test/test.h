kzalloc(sizeof(),GFP_KERNEL)
kzalloc(sizeof(),GFP_KERNEL)
kzalloc(sizeof(),GFP_KERNEL)
ioremap(gpio,4);
ioremap(gpio,4);
ioummap(gpio);
ioremap(gpio,4)

ioummap(gpio);
irqreturn_t (*irq_handler)(int,void *)
request_irq(EINT(16),button_isq,IRQF_TRIGGER_LOW,"BUT_IRQ",NULL);
request_irq(EINT(16),button_isq,IRQF_TRIGGER_RISING,"BUT_IRQ",NULL);
request_irq(EINT(16),button_irq,IRQF_TRIGGER_FALLING,"BUT_IRQ",NULL)
irqreturn_t button_iss(int arg,void *dev);
free_irq(EINT(16),NULL):
free_irq(EINT(16),NULL);
irqreturn_t button_isr(int data,void *dev):
free_irq(EINT(16),NULL):
ioremap(gpio,4);
ioummap(gpio);
free_irq(EINT(16),NULL);
request_irq(EINT(16),button_isr,IRQF_TRIGGER_FALLING,"BUT_IRQ",NULL);
request_irq(EINT(16),button_isr,IRQF_TRIGGER_RASING,"BUT_IRQ",NULL);
struct timer_list mytimer
struct timer_list mytimer
init_timer(&mytimer)
mytiemr.expires=jiffies+5*HZ
struct timer_list mytimer;
init_tiemr(&mytimer);
mytimer.expires=jiffies+5HZ;
mytiemr.function=mytimer_function
add_timer(&mytiemr):
