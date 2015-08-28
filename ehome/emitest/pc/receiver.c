#include "emi/emi.h"
#include <stdio.h>

int test_func(struct emi_msg *msg){
  printf("cmd=%d,size=%d,msg=%d,data=%s\n",msg->cmd,msg->size,msg->msg,msg->data);
  return emi_msg_prepare_return_data(msg,"aaa",4);
}

int main(){
  emi_init();
  emi_msg_register_exclusive(123456,test_func);
   while(1){
   sleep(1);
  }

  return 0;
}
