#include <stdio.h>
#include <stdlib.h>

int read_line(int filefd, char *buf, int len)
{
	if((buf == NULL) && (len == 0))
	{
		printf("##param errer!##\n");
		return 0;
	}
	fread((void*)buf, 
}
		
int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("##main input param errer!##\n");
		return -1;
	}
}	
