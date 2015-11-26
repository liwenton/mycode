#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <sys/types.h>

static ListNode *create_node(Contacts data , ListNode *next , ListNode *prev)
{
   ListNode *node=malloc(sizeof(ListNode));
   node->data=data;
   node->prev=prev;
   node->next=next;
   return node;
} 

static ListNode *destroy_node(ListNode *node , ListNode **prev)
{
   ListNode *next=node->next;
   if(prev)
    *prev=node->prev;   //prev不为空带出节点
   return next;
}

void list_init(List *list)
{
   list->head=NULL;
   list->tail=NULL;
}

void list_delinit(List *list)
{
   while(list->head)
   list->head=destroy_node(list->head,NULL);
   list->tail=NULL;
}

int  list_empty(List *list)
{
  return (!list->head) && (!list->tail);
}

void list_apped(List *list , Contacts data)
{
  	ListNode *new=creat_node(data , list->tail , NULL);
   	if(list->tail)	   //判断是否有没有节点
	{
		list->tail->next=new;
	}
	else			       //给空节点增加头结点
	{
     	list->head=new;           //给head节点添加指针
	}

   	list->tail=new;
}

//前查插元素(pos之前)
int  list_insert(List *list, int pos , Contacts data)
{
   ListNode *find=NULL;
   for(find=list->head;find;find=find->next)
   {
     if(!pos--){    //会寻找pos+1的次数
       ListNode *node=creat_node(data ,find->prev , find);
       if(node->prev)            //不是插入第一个位置
          node->prev->next=node;
       else
          list->head=node;       //前节点要改成插入节点 
          node->next->prev=node; 
       return 1;
     }
   }
   return 0;
}

//按位置删除
int  list_erase(List *list , int pos)
{
   ListNode *erase=NULL;
   for(erase=list->head; erase; erase=erase->next)
   {
     if(!pos--)
     {
       ListNode *prev=NULL;
       ListNode *next=destroy_node(erase, &prev);
       if(prev)               //判断前节点是否头结点
          prev->next=next;
       else
          list->head=next;
       if(next)               //判断后节点是否为尾节点
          next->prev=prev;
       else
          list->tail=prev;
       return 1;
     }
    return 0;
   }
}

//按数据删除
void list_remove(List *list , Contacts data)
{
	/*
   ListNode *find=NULL, *findnext=NULL;
   for(find=list->head;find;find=findnext)
   {
       findnext=find->next;//先保存next,当find节点被销毁了以后，for循环的next就找不到了
     if(find->data==data)
     {
       ListNode *prev=NULL;
       ListNode *next=destroy_node(find, &prev);
       if(prev)
          prev->next=next;
       else
          list->head=next;
       if(next)
          next->prev=prev;
       else
          list->tail=prev;  
     }
   }
   */
}

//
int  *list_at(List *list, int  pos)
{
   ListNode *find=NULL;
   for(find=list->head;find;find=find->next)
   {
     if(!pos--)
       return &(find->data);
   } 
    return NULL;
}

void list_clear(List *list)
{
}
int  list_size(List *list)
{
}



