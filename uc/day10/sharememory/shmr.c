#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
  key_t shmkey=ftok("./", 50);
  //不需要设置大小
  int shmid=shmget(shmkey, 0, 0);
  int* num=shmat(shmid, NULL, 0);
  if(num == (void*)-1)
  {
    perror("shmat");
    exit(0);
  }
  int i;
  for(i=0; i<1024; i++)
  {
  printf("共享内存已经读出=%d\n",*(num+i));
  }
  return 0;
}
