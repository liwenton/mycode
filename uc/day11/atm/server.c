#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "service.h"
#include "account.h"

struct Msg msg1, msg2;
void sig_exit(int signo)
{
   service_remove(&msg1); 
   service_remove(&msg2); 
   exit(0);
}

int main()
{
  struct Account *acc;
  service_init(&msg1, "./" , 10, 0);
  service_init(&msg2, "./" , 15, 0);
  signal(SIGINT, sig_exit);
  acc = service_recv(&msg1, 5);
  printf("name   :%s\n",acc->name);
  printf("passwd :%s\n",acc->passwd);
  while(1);
  return 0;
}
   
