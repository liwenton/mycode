#include <stdio.h>

int progress_bar(char *progress_info, int cur_progress, int total_progress)
{
	int index = 0;
	int diff = 0;

	if(total_progress == 0)
	{
		printf("total_progess can't 0\n");
		return -1;
	}
	else if(progress_info == NULL)
	{
		printf("progress_info is NULL\n");
		return -1;
	}

	printf("%s: ", progress_info);
	printf("[");
	for(index = 0; index < cur_progress; index++)
	{
		printf("*");
	}

	for(; index < total_progress; index++)
	{
		printf(" ");
	}
	printf("]"); 
	printf("%3d%%", cur_progress * 100 / total_progress);  //打印百分比
	if(cur_progress == total_progress) 
	{ 
		printf(" [COMPLETED]");
	}
	printf("\r"); //此句是关键，只回车不换	
	fflush(stdout);
	usleep(5000); 
}


int main()
{
	int i = 0;
	
	for(i = 0; i < 100; i++)
	{
		progress_bar("update", i+1, 100);
		sleep(1);
	}
	printf("\n");
	return;
}
	



