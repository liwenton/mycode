#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc , char *argv[])
{
   int fd;
   if (argc != 2)
   {
     printf("without the pathname!\n");
     return -1;
   }
   /*
     int access(const char *pathname, int mode)
     mode:
      	R_OK  测试是否可读
	W_OK  测试是否可写
	X_OK  测试是否可执行
	F_OK  测试是否存在
   */
   if (access(argv[1],W_OK)<0)
   {
      perror("access"); 
      return -1;
   }
   else if((fd=open(argv[1],O_WRONLY)<0))
   {
      perror("Open");
      return -1;
   }
   printf("open for reading OK\n");
   return 0;
}

