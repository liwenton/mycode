#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_LEN 30

int main()
{
	int sockfd = 0;
	int connfd = 0;
	struct sockaddr_in servaddr;
	struct sockaddr_in clientaddr;
	char buff[MAX_LEN];
	time_t  ticks;
	int addrlen = sizeof(clientaddr);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(13);

	bind(sockfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr_in));
	listen(sockfd, 10);

	while(1)
	{
		memset((void *)&clientaddr, 0 , sizeof(struct sockaddr_in));
		connfd = accept(sockfd,(struct sockaddr *)&clientaddr, &addrlen); 
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\n",ctime(ticks));
		write(connfd, buff,strlen(buff));
		close(connfd);
	}
}
