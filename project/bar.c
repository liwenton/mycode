#include <stdio.h>
#define TIMES 40
void bar(int x)
{ 
	int i,j; 
	printf("Mcu updating: ");
	printf("["); 
	for (j=0;j<x;j++)
	{	
		printf("*");
	}	
	for (; j<TIMES;j++) 
	{
		printf(" "); 
	}
	printf("]"); 
	printf("%3d%%", x * 100 / TIMES); 
	if(x == TIMES) 
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
	
	for(i = 1; i <= 40; i++)
	{
		bar(i);
	}
	
	bar(TIMES);
	printf("\n");
	return;
}
