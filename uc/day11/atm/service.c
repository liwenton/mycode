#include "service.h"
#include "account.h"

int service_init( struct Msg* msg, const char* pathname, int proid, int type)
{
   msg->key = ftok(pathname, proid);
   if(type  == 0)
   msg->msgid = msgget(msg->key, IPC_CREAT|0666);
   else
   msg->msgid = msgget(msg->key, 0);
   
   if(msg->msgid == -1)
   {
     perror("消息队列创建失败\n");
     return -1;
   }
   printf("消息队列创建成功\n");
     return 0;
}

int service_remove(struct Msg *msg)
{
    int ret = msgctl(msg->msgid, IPC_RMID, NULL);
    if(ret == -1)
     return -1;
    else
     return 0;
}
int service_send(struct Account acc, const struct Msg *msg, int type)
{
   struct Service send;
   send.mtype    = type;
   send.account = acc;
   int ret =  msgsnd(msg->msgid, &send, sizeof(send.account), 0);
   if(ret == -1)
   {
     perror("消息发送失败\n");
   } 
   else
   {
     printf("消息发送成功\n");
     ret = 0;
   }
     return ret;
}  

struct Account* service_recv(const struct Msg *msg, int type)
{
   struct Account *acc=(struct Account*)malloc(sizeof(struct Account));
   struct Service recv;
   int ret = msgrcv(msg->msgid, &recv, sizeof(recv.account), type, 0);
   if(ret == -1)
   {
      perror("消息接收失败\n");
      free(acc);
      acc=NULL;
   } 
   else
   {
     printf("消息发送成功\n");
     *acc = recv.account;
   }
     return acc;
}


