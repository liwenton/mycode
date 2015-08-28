#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
typedef struct Msg{
   long mtype;      //数据类型
   char buf[256];   //数据区，存储消息数据
}MSG;

int main()
{
   key_t key = ftok("./", 50);
   int msgid = msgget(key, IPC_CREAT|0666);
   if(msgid == -1)
   {
     perror("msgget");
     exit(0);
   }
   MSG msg;
   int res = msgrcv(msgid, &msg, sizeof(msg.buf), 1, IPC_NOWAIT);
   if(res == -1)
   {
      perror("send");
      exit(0);
   }
   printf("%s\n", msg.buf);
   return 0;
} 
