#include<linux/init.h>
#include<linux/module.h>
#include<asm/gpio.h>
#include<plat/gpio-cfg.h>

#define LED_ON  0
#define LED_OFF 1
typedef struct led{
    unsigned long gpio; //描述GPIO的软件编号
    char *name; //描述GPIO的名称
} led_resource;

static led_resource led_info[]={
    //标记初始化
     [0]={
        .gpio=S5PV210_GPJ2(0),
        .name="GPJ2_0"
      },
     [1]={
        .gpio=S5PV210_GPJ2(1),
        .name="GPJ2_1"
      }, 
     [2]={
        .gpio=S5PV210_GPJ2(2),
        .name="GPJ2_2"
      },
     [3]={
        .gpio=S5PV210_GPJ2(3),
        .name="GPJ2_3"
     },
};
static int led_init(void){
   /*1、申请GPIO资源
     2、配置GPIO为输出口	
     3、输出为1，点亮*/
      int i=0;
      for(i=0;i<(sizeof(led_info)/sizeof(led_info[0]));i++){
        gpio_request(led_info[i].gpio,led_info[i].name);
        gpio_direction_output(led_info[i].gpio,LED_ON);
      }
      return 0;
}

static void led_exit(void){
     int i=0;
      for(i=0;i<(sizeof(led_info)/sizeof(led_info[0]));i++){
//         led_cmd(led_info[i].gpio,LED_OFF);
//         gpio_direction_output(led_info[i].gpio,LED_OFF);
         gpio_set_value(led_info[i],LED_OFF);
	 gpio_free(led_info[i].gpio);
     }
        
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");

