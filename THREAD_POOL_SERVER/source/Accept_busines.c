#include <THREAD_POOL_SERVER.h>
#include <SOCKET.h>

void * Accept_busines(void * arg)
{
	int serverfd = *(int *)arg;
	int clientfd;
	struct sockaddr_in clientaddr;
	socklen_t addrlen = sizeof(clientaddr);

	struct epoll_event node;

	printf("Customer tid <0x%x> exec Accept_busines...\n",(unsigned int)pthread_self());

	pthread_mutex_lock(&accept_lock);
	if((clientfd = ACCEPT(serverfd,(struct sockaddr *)&clientaddr,&addrlen))==-1){
		perror("Accept_busines >> accept call failed");
		pthread_mutex_unlock(&accept_lock);
		return NULL;
	}
	pthread_mutex_unlock(&accept_lock);

	node.data.fd = clientfd;
	node.events = EPOLLIN|EPOLLET;

	if((epoll_ctl(epfd,EPOLL_CTL_ADD,clientfd,&node))==-1){
		perror("Accept_business >> epoll_ctl call failed");
		return NULL;
	}


	return NULL;
}
