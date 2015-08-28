#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
int main(int argc, char *argv[])
{
   if(argc < 2)
	{
		perror("argc");
		return 0;
	}
   DIR *pdir = opendir(argv[1]);
   struct dirent *dir =NULL;
   while((dir = readdir(pdir)) != NULL){
	 if(!strcmp("." , dir->d_name) || !strcmp("..", dir->d_name))
	{
		continue;
	}
     printf("%s\n",dir->d_name);
   }
   closedir(pdir);
   return 0;
}
