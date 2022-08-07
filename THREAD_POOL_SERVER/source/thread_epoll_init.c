#include <THREAD_POOL_SERVER.h>
#include <SOCKET.h>

int thread_epoll_init(int sockfd)
{

	struct epoll_event node;
	
	node.data.fd = sockfd;
	node.events = EPOLLIN|EPOLLET;

	if((epfd = epoll_create(_EPOLLSIZE))==-1){
		thread_pool_error("thread_epoll_init call failed, epoll_create error.",-1,0);
	}

	if((epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&node))==-1){
		thread_pool_error("thread_epoll_init call failed, epoll_ctl error.",-1,0);	
	}

	return 0;
}
