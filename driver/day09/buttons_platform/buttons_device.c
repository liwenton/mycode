#include<linux/init.h>
#include<linux/module.h>
#include<linux/platform_device.h>

struct butn_pridata {
  char *name;
  int version;
};

struct butn_pridata butn_info={
  .name="LWT",
  .version=1
};

struct resource butn_res[]={
   [1]={
    .start=0Xe0200c40,
    .end  =0xe0200c40+8-1,
    .flags=IORESOURCE_MEM
   },
   [2]={
    .start=0,
    .end  =0,
    .flags=IORESOURCE_IRQ
   }
};

struct platform_device butn_dev={
  .name="buttons",
  .id=-1,
  .dev={
    .platform_data=&butn_info,
    .release=butn_release
   },
  .num_resources=ARRAY_SIZE(butn_res),
  .resource=butn_res
};

static int butn_dev_init(void){
    platform_device_register(&butn_dev);
    return 0;
}

static void butn_dev_exit(void){
    platform_device_unregister(&butn_dev);
}

module_init(butn_dev_init);
module_exit(butn_dev_exit);

MODULE_LICENSE("GPL");
