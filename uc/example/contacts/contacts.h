#ifndef __CONTACTS_H__
#define __CONTACTS_H__

typedef struct{
	char name[30];
	char phone[20];
	char email[20];
}Contacts;

int LoadContacts(char *path);
int	SaveContacts(char *path);
int CheckContacts();
int AddContacts();
int ModifyContacts();
int DeleteContacts();
int ShowContacts();

#endif
