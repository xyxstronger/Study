#include <THREAD_POOL_SERVER.h>

int thread_pool_destroy(thread_pool_t * p)
{
	//释放锁资源
	pthread_mutex_destroy(&p->lock);
	pthread_cond_destroy(&p->not_full);
	pthread_cond_destroy(&p->not_empty);
	free(p->task_list);
	free(p->customer_tids);
	free(p);
	return 0;
}
