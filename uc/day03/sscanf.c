#include <stdio.h>
#include <unistd.h>

int main(){
  char s1[]="1234";
  char buf[100]={};
  int i;
  sscanf(s1,"%d",&i);
  sprintf(buf,"%d",i);
  printf("%s\n",buf);
  return 0;
}
