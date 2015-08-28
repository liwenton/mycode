#include <stdio.h>
#include <signal.h>

int main()
{
   printf("size=%d\n", sizeof(sigset_t));
   sigset_t set;
   printf("set=%d\n", set);
   sigemptyset(&set);
   printf("set=%d\n", set);
   sigaddset(&set, 2);
   sigaddset(&set, 3);
   printf("set=%d\n", set);  //2+4
   return 0;
}
   
