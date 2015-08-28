#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
//   int fd=open("./a.pipe",O_RDWR);   既有读管道、又有写管道
   int fd=open("./a.pipe",O_RDONLY);
   if(fd==-1)
   {
      perror("open");
      exit(-1);
   }
   int i;
   for(i=0; i<100; i++)
   {
      read(fd, &i, 4);
      printf("read:%d\n", i);
      usleep(100000);
   }
   close(fd);
   return 0;
}
