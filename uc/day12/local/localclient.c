#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

int main()
{
	char buf[100];
	int sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if(sockfd == -1)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_un addr;
	addr.sun_family = AF_LOCAL;
	strcpy(addr.sun_path, "a.sock");	//本地通信需要文件

	int res = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if( res == -1)
	{
		perror("connet");
		return -1;
	}
	printf("connect成功\n");

	int len = write(sockfd, "hello", 5);
	close(sockfd);
}

