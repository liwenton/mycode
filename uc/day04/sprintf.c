#include <stdio.h>
#include <string.h>

int main()
{
  char buf[20]={};
  sprintf(buf,"%d:%d:%d",10,20,30);
  printf("%s\n",buf);
}
