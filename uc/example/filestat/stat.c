#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
  	struct stat buf;
  	char *ptr=NULL;
  	if(argc !=2)
  	{
    	printf("witout pathname\n");
    	return -1;
 	 }

  	if(lstat(argv[1], &buf))
  	{
    	printf("lstat error\n");
    	return -1;
  	}

  	if (S_ISREG(buf.st_mode))
    	ptr="regular";
  	else if (S_ISDIR(buf.st_mode))
    	ptr="directory";
  	else if (S_ISCHR(buf.st_mode))
    	ptr="character specical";
  	else if (S_ISBLK(buf.st_mode))
    	ptr="block specical";
  	else if (S_ISFIFO(buf.st_mode))
    	ptr="fifo";
  	else if (S_ISLNK(buf.st_mode))
    	ptr="symbolic link";
  	else if (S_ISSOCK(buf.st_mode))
    	ptr="socket";
  	else 
    	ptr="** unknown mode**";


	printf("%s\n",ptr);
    printf("inode=%ld\n",buf.st_ino); 
    printf("dev=%ld\n",buf.st_dev); 
}
