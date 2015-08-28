#include<linux/init.h>
#include<linux/module.h>
#include<linux/platform_device.h>

typedef struct{
   char * name;
   int version;
}led_pridata;


led_pridata led_info={
   .name="TPAD",
   .version=1
};

struct resource led_res[]={
      [0]={	
      .start=0xe0200280,
      .end=  0xe0200280+ 8-1,
      .flags=IORESOURCE_MEM
      },
      
      [1]={
      .start=1,
       .end=1,
       .flags=IORESOURCE_IRQ
      }
};

static void led_release(struct device *dev){
}

struct platform_device led_dev={
        .name="leds",
	.id      =-1,
	.dev={
            .platform_data=&led_info,
            .release=led_release 
        },
        .num_resources=ARRAY_SIZE(led_res),
	.resource=led_res
		
};

static int led_dev_init(void){
	 platform_device_register(&led_dev);
         return 0;
}

static void led_dev_exit(void){
	 platform_device_unregister(&led_dev);
}

module_init(led_dev_init);
module_exit(led_dev_exit);

MODULE_LICENSE("GPL");

