#include <stdio.h>
#include <unistd.h>

int main(){
  printf("size=%d\n",getpagesize());
  return 0;
}
