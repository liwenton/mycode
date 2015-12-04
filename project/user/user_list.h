#ifndef __USER_LIST_H__
#define __USER_LIST_H__

#include "list.h"

#define 	MAX_USER_NAME_LEN		20
#define 	MAX_USER_PASSWD_LEN		20



typedef struct {
	char name[MAX_USER_NAME_LEN+1];
	char passwd[MAX_USER_PASSWD_LEN+1];
	struct list_head list;
}ListNode;

void user_list_init();
int  user_list_size();
int  user_list_empty();
int  user_list_find(char *user_name);
int  user_list_delete(char *user_name);
int  user_list_append(char *user_name, char *user_passwd);


#endif  
