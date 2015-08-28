#include <linux/init.h>
#include <linux/module.h>

void test_module(void){
   printk("test_module\n");
}

EXPORT_SYMBOL_GPL(test_module);
MODULE_LICENSE("GPL");
