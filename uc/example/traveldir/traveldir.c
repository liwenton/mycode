#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

int straveldir(char *pathname)
{	
   DIR *pdir = opendir(pathname);
   struct stat statbuf;
   char path[50]={0};
   struct dirent *dir =NULL;

	while((dir = readdir(pdir)) != NULL)
   {
		if(!strcmp("." , dir->d_name) || !strcmp("..", dir->d_name))
		{
			continue;
		}
		snprintf(path, 50, "%s/%s", pathname, dir->d_name);

		stat(path, &statbuf);
		if(S_ISDIR(statbuf.st_mode))
		{
			printf("[%s]\n",dir->d_name);
			straveldir(path);
		}
		else
			printf(" %s\n",dir->d_name);
   	}
   closedir(pdir);
}

int main(int argc, char *argv[])
{
   if(argc < 2)
	{
		perror("argc");
		return 0;
	}
   straveldir(argv[1]);
   return 0;
}
