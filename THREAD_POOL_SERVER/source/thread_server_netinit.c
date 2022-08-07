#include <THREAD_POOL_SERVER.h>
#include <SOCKET.h>

int thread_server_netinit(void)
{
	int sockfd;
	struct sockaddr_in serveraddr;
	bzero(&serveraddr,sizeof(serveraddr));

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(_PORT);
	inet_pton(AF_INET,_IP,&serveraddr.sin_addr.s_addr);

	sockfd = SOCKET(AF_INET,SOCK_STREAM,0);
	BIND(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	LISTEN(sockfd,_BACKLOG);

	return sockfd;

}
