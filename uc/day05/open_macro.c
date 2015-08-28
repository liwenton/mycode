#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){
  printf("O_RDONLY=%d,O_WRONLY=%d,O_RDWR=%d\n",O_RDONLY,O_WRONLY,O_RDWR);
  printf("O_CREAT=%d,O_APPEND=%d,O_TRUNC=%d\n",O_CREAT,O_APPEND,O_TRUNC);
  return 0;
}
