#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
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
   MSG msg1, msg2;
   msg1.mtype = 1;
   strcpy(msg1.buf, "zhangfei");
   msg2.mtype = 2;
   strcpy(msg2.buf, "guanyu");
   int res1 = msgsnd(msgid, &msg1, sizeof(msg1.buf),0);
   int res2 = msgsnd(msgid, &msg2, sizeof(msg2.buf),0);
   if((res1 == -1) || (res2 == -1))
   {
      perror("send");
      exit(0);
   }
   printf("发送成功\n");
   return 0;
} 
