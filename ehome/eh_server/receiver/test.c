#include <stdio.h>
#include "emi/emi.h"

int test_func(struct emi_msg *msg){
  printf("msg->cmd:%d,msg->data%s\n",msg->cmd,msg->data);
  return emi_msg_prepare_return_data(msg,"hel",4);
}

int __receiver_plugin_register_init(void){
     return emi_msg_register_exclusive(123456,test_func);
}
