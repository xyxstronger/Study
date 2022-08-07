#include <THREAD_POOL_SERVER.h>
#include <SOCKET.h>

int thread_epoll_listen(thread_pool_t * p,int sockfd)
{
	//启动监听
	int readycode;
	struct epoll_event ready_array[_EPOLLSIZE];
	int flag;
	task_t tmp_task;

	while(p->thread_shutdown){
		
		flag = 0;

		if((readycode = epoll_wait(epfd,ready_array,_EPOLLSIZE,-1))==-1){
			thread_pool_error("thread_epoll_listen call failed, epoll_wait error.",-1,0);
		}

		while(readycode){
			//就绪判断
			if(ready_array[flag].data.fd == sockfd){
				//根据就绪添加对应的业务（生产者任务）
				tmp_task.work = Accept_busines;
				tmp_task.arg = (void *)&ready_array[flag].data.fd;
				thread_producer_add(p,tmp_task);
			}
			else{
				tmp_task.work = Response_busines;
				tmp_task.arg = (void *)&ready_array[flag].data.fd;
				thread_producer_add(p,tmp_task);
			}

			readycode--;
			flag++;
		}		

	}
	return 0;
}
