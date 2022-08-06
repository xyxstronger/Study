#include <THREAD_POOL_SERVER.h>

int main(void)
{
	thread_pool_t * p = NULL;
	p = thread_pool_create(100,10,500);

	task_t test;
	test.work = business;
	test.arg = NULL;

	for(int i=0;i<10;i++){
		thread_producer_add(p,test);
	}

	if(!p->thread_shutdown){
		thread_pool_destroy(p);
	}

	while(1)
		sleep(1);

	return 0;
}
