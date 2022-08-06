#include <THREAD_POOL_SERVER.h>

int thread_if_alive(pthread_t tid)
{
	//通过信号判断线程是否存活，存活返回1，不存活返回0
	pthread_kill(tid,0); //不存在信号0，表示线程是否存活
	if(errno == ESRCH){
		return 0;
	}
	else{
		return 1;
	}
}
