#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

int main()
{
	char buf[100]={0};
	int sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if(sockfd == -1)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_un addr;
	addr.sun_family = AF_LOCAL;
	strcpy(addr.sun_path, "a.sock");	//本地通信需要文件

	int res = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if( res == -1)
	{
		perror("bind");
		return -1;
	}
	printf("绑定成功\n");

	int len = read(sockfd, buf, sizeof(buf));
	if( len == -1)
	{
		perror("read");
		return -1;
	}
	buf[len]='\0';
	printf("%s\n", buf);
	close(sockfd);
}

