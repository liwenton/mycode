#include <linux/init.h>
#include <linux/module.h>

static int helloworld_init(void)
{
   printk("%s\n",__FUNCTION__);
//   printk("entry\n");
   return 0;
}

static void helloworld_exit(void)
{
   printk("%s\n",__FUNCTION__);
//    printk("exit\n");
}

module_init(helloworld_init);
module_exit(helloworld_exit);

//添加模块信息，必须加上
MODULE_LICENSE("GPL");

//附加信息
MODULE_AUTHOR("Lee <631407587@qq.com>");

MODULE_DESCRIPTION("This is test module");
MODULE_VERSION("1.0.0.0");




