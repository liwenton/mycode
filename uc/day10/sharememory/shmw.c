/*
新建共享内存，并写入整数100
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
  //获取Key
  key_t shmkey=ftok("./", 50);
  //创建/获取内部ID
  int shmid=shmget(shmkey, 4,  IPC_CREAT|IPC_EXCL|0666);
  if(shmid==-1)
  {
    perror("shmget");
    exit(0);
  }
  //挂接共享内存
  int* num=shmat(shmid, NULL, 0);
  if(num == (void*)-1)
  {
    perror("shmat");
    exit(0);
  }
   int i;
  for(i=0; i<1024; i++)
    *(num+i)=i;
  printf("共享内存已经写入\n");
  shmdt(num);
  return 0;
}
