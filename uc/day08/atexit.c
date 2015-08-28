#include <stdio.h>
#include <stdlib.h>

void at()
{
   printf("at is called\n");
}

int main()
{
   atexit(at); //注册了退出前调用的函数
   printf("begin\n");
//   exit(0);
   printf("end\n");
   return 0;
}
