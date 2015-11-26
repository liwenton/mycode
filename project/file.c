#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME	"config.txt"
#define LINE_LEN	50

int main()
{
	int i;
	char LineBuffer[LINE_LEN]={0};
	FILE *FileConfig = fopen(FILE_NAME, "r");

	while(fgets(LineBuffer, LINE_LEN,FileConfig) != NULL)
	{	
   		//printf("%s",LineBuffer);	
   		//printf("%s\n",strtok(LineBuffer, "@"));	
   		//printf("%s\n",strtok(NULL, "\n"));	
		for(i = 0; i < LINE_LEN; i++)
		{
			if(LineBuffer[i] == '\n')
			{
				LineBuffer[i] = '\0';
			}

		}
   		printf("%s\n",LineBuffer);
	}
	return 0;	
}

