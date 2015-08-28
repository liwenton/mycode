#ifndef SERVICE_H_
#define SERVICE_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>


#include "account.h"


struct Msg{
  key_t key;
  int   msgid;
};
struct Service{
  long    mtype;
  struct Account account;;
};


int service_init( struct Msg* msg, const char* pathname, int proid, int type);
int service_remove(struct Msg *msg);
int service_send(struct Account acc, const struct Msg *msg, int type);
struct Account* service_recv(const struct Msg *msg, int type);

#endif
