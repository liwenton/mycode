#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "service.h"
#include "account.h"

int main()
{
  struct Msg msg1, msg2;
  struct Account acc;
  strcpy(acc.name, "李文通");
  strcpy(acc.passwd, "aa2235236");
  service_init(&msg1, "./", 10, 1);
  service_init(&msg2, "./", 15, 1);
  service_send(acc, &msg1 ,5);
  return 0;
}
