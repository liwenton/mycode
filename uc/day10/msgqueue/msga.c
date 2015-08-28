#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
   key_t key = ftok("./", 100);
   int msgid = msgget(key, IPC_CREAT|0666);
   if(msgid == -1)
   {
      perror("msgget");
      exit(0);
   }
   int res= msgsnd(msgid, "hello msg", 9, 0);//最后的参数也可以是IPC_NOWAIT，就是队列满了不等待，0就是等待。
   if(res == -1)
   {
      perror("msgsnd");
      exit(0);
   }
   printf("发送成功\n");
   
   return 0;
}
