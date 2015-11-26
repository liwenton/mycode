#include <stdio.h>
#include "contracts.h"

struct list_head ContactsHead;

int LoadContactsInfo(char *path, char *ContactsInfo)
{
	FILE *pFile;
	long FileSize;
	int Ret;
	char *Buff
	if(path == NULL)
	{
		printf("warn path name!\n");
		return -1;
	}

	pFile = fopen(path, "rb");
	if(pFile == NULL)
	{
		printf("open contacts file fail!\n"):
		return -1;
	}

	fseek(pFile, 0, SEEK_END);
	FileSize = ftell(pFile);

	fseek(pFile, 0, SEEK_SET);
	Buff = malloc(Filesize);
	memset(Buff, 0, Filesize);
	Ret = fread(ListBuff, ContactsNum, ContactsSize, pFile);
	if(Ret == -1)
	{
		free(Filesize);
		fclose(pFile);
		ContactsInof = NULL;
		Buff = NULL;
		return -1;
	}
	
	ContactsInof = Buff;
	fclose(pFile);
	return 0;
}

int SaveContactsInfo(char *Path, const char *ContactsInfo, int Lenth)
{
	pFile = fopen(Path, "w");
	if(pFile == NULL)
	{
		printf("open contacts file fail!\n"):
		return -1;
	}

	Ret = pwirte(ContactsInfo, Lenth, 1, pFile);
	fclose(pFile);
	return 0;
	
}
int CheckContacts();
int AddContacts();
int ModifyContacts();
int DeleteContacts();
int ShowContacts();

