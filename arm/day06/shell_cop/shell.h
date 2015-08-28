#ifndef  __SHELL_H_
#define __SHELL_H_

#include"cmd.h"

typedef struct {
  char fname[20];
  void (*func)(void);
}cmd;

cmd fun[]={
    "ledon"  ,cmd_led_on,
    "ledoff" ,cmd_led_off,
    "nandid", cmd_nand_readid,
    "nandpread",cmd_nand_page_read,
    "nandbad",cmd_nandbad,
};

static int cmd_size=sizeof(fun)/sizeof(fun[0]);

void shell_exe(void);
void shell_init(void);
cmd* shell_find(unsigned char *str);

#endif
