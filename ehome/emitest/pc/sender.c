#include "emi/emi.h"
#include <stdio.h>

int main(){
   char hello[20]="hello";
   char buf[20]={0};

   emi_msg_send_highlevel_blockreturn("192.168.1.6",123456,6,hello,4,buf,5);
   printf("%s\n",buf);
   return 0;
}
