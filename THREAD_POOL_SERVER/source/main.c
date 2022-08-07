#include <THREAD_POOL_SERVER.h>
#include <SOCKET.h>

int main(void)
{
	//网络初始化
	int serverfd = thread_server_netinit();
	//epoll初始化
	thread_epoll_init(serverfd);
	//全局锁初始化
	pthread_mutex_init(&accept_lock,NULL);
	//线程池创建
	thread_pool_t * p = NULL;
	p = thread_pool_create(100,10,500);

	printf("Thread Pool Server(Epoll) Version 1.0 Starting...\n");


	//监听事件
	thread_epoll_listen(p,serverfd);

	//销毁锁
	pthread_mutex_destroy(&accept_lock);
	//销毁线程池
	thread_pool_destroy(p);

	return 0;
}
