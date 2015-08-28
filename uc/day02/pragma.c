#include <stdio.h>

#pragma GCC dependency "a.txt"
//比较a.txt和当前文件的最后修改时间，如果a.txt比当前文件新，则产生警告

//#pragma GCC poison goto //禁止是使用goto,会产生错误
int main(){
 // goto ok;
  printf("OK\n");
 // ok:printf("over\n");
  return 0;
} 
