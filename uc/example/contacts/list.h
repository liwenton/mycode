#ifndef LIST_H
#define LIST_H

#include "contacts.h"

typedef struct LISTNODE{
  Contacts data;
  struct LISTNODE *next;
  struct LISTNODE *prev;
}ListNode;

typedef struct LIST{
  ListNode  *head;  //头节点
  ListNode  *tail;  //尾节点
  ListNode  *frwd;  //正向查询 迭代节点
  ListNode  *bkwd;
}List;


void list_init(List *list);
void list_delinit(List *node);
int  list_empty(List *node);
//前查插元素(pos之前)
int  list_insert(List *node, int pos , Contacts data);
//按位置删除
int  list_erase(List *node , int pos);
//按数据删除
void list_remove(List *node , Contacts data);
//
int  *list_at(List *list, int  pos);
void list_clear(List *list);
int  list_size(List *list);

#endif
