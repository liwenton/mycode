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
   char buf[100]={};
   int res = msgrcv(msgid, buf, sizeof(buf), 0, 0);
   if(res == -1)
   {
     perror("msgrcv");
     exit(0);
   }
   printf("读到了%d字节,内容：%s\n", res, buf);
   return 0;
}
