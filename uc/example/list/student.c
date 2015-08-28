#include <linux/kernel.h>
#include "list.h"
#include <stdio.h>

#define MAX_NUM		2

typedef struct
{
	char *name;
	int   age;
	int	  sex;

	int   id;
	int   class;
	int   grade;
	struct list_head stu_node;
}Student;

struct list_head stu_head;

int main()
{
	Student stu[MAX_NUM];
	struct list_head *plist;
	Student *pstu;
	stu[0].name  = "liwentong";
	stu[0].age	 = 12;
	stu[0].sex   = 0;
	stu[0].id	 = 7223;
	stu[0].class = 6;
	stu[0].grade = 4;

	stu[1].name  = "mahaiyan";
	stu[1].age	 = 12;
	stu[1].sex   = 0;
	stu[1].id	 = 7223;
	stu[1].class = 6;
	stu[1].grade = 4;
	
	LIST_HEAD(stu_head);

	int index;
	for(index=0; index<MAX_NUM; index++)
	{
		INIT_LIST_HEAD(&stu[index].stu_node);
		list_add_tail(&stu[index].stu_node, &stu_head);
	}

	list_for_each(plist, &stu_head)
	{
		pstu = list_entry(plist, Student, stu_node);
		printf("%s\n", pstu->name);
	}

/*
	LIST_HEAD(stu_head);

	INIT_LIST_HEAD(&li.stu_node);
	list_add(&li.stu_node, &stu_head);

	struct list_head *plist;
	Student *pstu;

	list_for_each(plist, &stu_head) {
		pstu = list_entry(plist, Student, stu_node);
		printf("%s\n",pstu->name);
	}
*/
	return 0;
}

	

