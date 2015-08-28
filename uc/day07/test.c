#include <stdio.h>
#include <stdlib.h>

int add(int num){
  if(num==1)
   return 1;
  else return num*add(num-1);
}
int main(){
  int s=add(5);
  printf("%d\n",s);
  return 0;
}

