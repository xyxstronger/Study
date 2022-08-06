#include <THREAD_POOL_SERVER.h>

int thread_pool_error(const char * strerr,long int exitcode,int flag)
{
	//flag == 0 系统函数出错
	if(!flag){
		perror(strerr);
		exit(exitcode);
	}
	//flag > 0 线程出错
	printf("%s: %s\n",strerr,strerror(flag));
	pthread_exit((void *)exitcode);
	return 0;
}
