#ifndef __USER_H
#define __USER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
struct User{
  char name[20];
  char passwd[20];
  char email[30];
};

struct Cmd{
  int num;
  int (*func)(char *);
};
#endif
