#ifndef LIST_H
#define LIST_H

typedef struct LISTNODE{
  int data;
  struct LISTNODE *next;
  struct LISTNODE *prev;
}ListNode;

typedef struct LIST{
  ListNode  *head;  //头节点
  ListNode  *tail;  //尾节点
  ListNode  *frwd;  //正向查询 迭代节点
  ListNode  *bkwd;
}List;


void list_init(ListNode *node);
void list_delinit(ListNode *node);
int  list_empty(ListNode *node);
//前查插元素(pos之前)
int  list_insert(ListNode *node, int pos , int data);
//按位置删除
int  list_erase(ListNode *node , int pos);
//按数据删除
void list_remove(ListNode *node , int data);
//
int  *list_at(List *list, int  pos);
void list_clear(List *list);
int  list_size(List *list);

#endiff
