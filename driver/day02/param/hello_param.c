#include<linux/init.h>
#include<linux/module.h>

static int  myint=10;
static char *mychar="lwt";
static int  myarray[]={100,200};

module_param(myint,int,0);
module_param(mychar,charp,0664);
static int hello_param_init(void){
  printk("%d\n",myint);
  printk("%s\n",mychar);
  printk("%d\n",myarray[0]);
  printk("%d\n",myarray[1]);
   return 0;
}

static void hello_param_exit(void){
  printk("%d\n",myint);
  printk("%s\n",mychar);
  printk("%d\n",myarray[0]);
  printk("%d\n",myarray[1]);
}

module_init(hello_param_init);
module_exit(hello_param_exit);
MODULE_LICENSE("GPL");
