#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "user_list.h"
#include "list.h"

struct list_head user_head;

void user_list_init()
{
	INIT_LIST_HEAD(&user_head);
}

void user_list_delinit()
{
	list_del_init(&user_head);
}

int  user_list_size()
{
	int size = 0;
	struct list_head *temp_list = NULL;

	list_for_each(temp_list, &user_head)
	{
		size++;
	}

	return size;
}

int  user_list_empty()
{
	if(!list_empty(&user_head))
	{
		return -1;
	}

	return 0;
}

int  user_list_find(char *user_name)
{
	int ret = -1;

	ListNode *puser; 


	list_for_each_entry(puser, &user_head, list)
	{
		if(!strcmp(puser->name, user_name))
		{
			ret = 0;
		}
	}

	return ret;
}

int  user_list_delete(char *user_name)
{
	int ret = -1;
	int pos = 0 ;

	ListNode *puser, *_puser;

	if(user_list_empty())
	{
		return -1;
	}

	list_for_each_entry_safe(puser, _puser, &user_head, list)
	{
		if(!strcmp(puser->name, user_name))
		{
			list_del(&(puser->list));
			free(puser);
		}
	}

	return 0;
}

int  user_list_append(char *user_name, char *user_passwd)
{
	
	if(user_list_empty())
	{
		if( !user_list_find(user_name) )
		{
			return -1;
		}
	}

	ListNode *puser = (ListNode *)malloc(sizeof(ListNode));
	strcpy(puser->name, user_name);
	strcpy(puser->passwd, user_passwd);
	INIT_LIST_HEAD(&(puser->list));
	list_add_tail(&puser->list, &user_head);

	return 0;
}	


