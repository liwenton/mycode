#include <stdio.h>

int main(){
  int t=200;
//  int c=300;
  //int *pi=(int*)0xbfef112c;
  int *pi=&t+1;
  printf("*pi=%d\n",*pi);
}
